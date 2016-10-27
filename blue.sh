#!/bin/bash

if [ ! $1 ]; then
	echo "Scanning..."
	REMDEV=`hcitool scan | awk '/[[:xdigit:]]{2}(:[[:xdigit:]]{2}){5}/ { print $1 }'`
else
	REMDEV=$1
fi

BLUDEV=`hcitool dev | awk '/[[:xdigit:]]{2}(:[[:xdigit:]]{2}){5}/ { print $2 }'`

echo "Dispositivo Bluetooth: $BLUDEV"
echo "Dispositivo Remoto: $REMDEV"
echo
echo "Conectando ..."

RFCOMM="/dev/rfcomm0"

if [ -c "$RFCOMM" ] ; then
	echo "$RFCOMM bound"
else
	echo "Binding $RFCOMM ..."
	sudo rfcomm bind $RFCOMM $REMDEV 1
fi

BLUTXT="blue.txt"

echo "Escrevendo em $BLUTXT"
echo "---"
echo
cat $RFCOMM | tee -a $BLUTXT
