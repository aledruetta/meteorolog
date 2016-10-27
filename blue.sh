#!/bin/bash

BLUMAC=`hcitool dev | awk '/[[:xdigit:]]{2}(:[[:xdigit:]]{2}){5}/ { print $2 }'`

if [ -n "$BLUMAC" ] ; then

	echo "Dispositivo Bluetooth: $BLUMAC"

	if [ -n "$1" ] ; then
		REMAC=$1
	else
		echo "Scanning..."
		REMAC=`hcitool scan | awk '/[[:xdigit:]]{2}(:[[:xdigit:]]{2}){5}/ { print $1 }'`
	fi
else
	echo "Erro: Dispositivo Bluetooth não detectado!"
	exit 1
fi

if [ -n "$REMAC" ] ; then
	RENAME=`hcitool name $REMAC`
	if [ -n "$RENAME" ] ; then
		echo "Dispositivo Remoto: $RENAME ($REMAC)"
	else
		echo "Erro: Dispositivo Remoto não detectado!"
		exit 1
	fi
else
	echo "Erro: Dispositivo Remoto não detectado!"
	exit 1
fi

echo "Estabelecer conexão com $RENAME (y/n)?"
read RESP

if [ ! "$RESP" == "y" ] ; then
	exit 0
fi

echo
echo "Conectando ..."

RFCOMM="/dev/rfcomm0"

if [ -c "$RFCOMM" ] ; then
	echo "$RFCOMM bound"
else
	echo "Binding $RFCOMM ..."
	sudo rfcomm bind $RFCOMM $REMAC 1
fi

BLUTXT="blue.txt"
DATE=`date`

echo "Escrevendo em $BLUTXT"
printf "\n%s\n\n" "$DATE" | tee -a $BLUTXT
cat $RFCOMM | tee -a $BLUTXT

