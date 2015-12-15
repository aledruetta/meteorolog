#! /usr/bin/env python
# coding: utf-8

from serial import Serial, SerialException
from time import localtime, strftime
import sys


class Arduino:

    def __init__(self, port):
        self.port = port
        self.serial = self.get_serial()
        self.sensors = [
            {
                "ID": "DS18B20",
                "name": "DS18B20",
                "tag": "Temp 1",
                "unit": "deg C",
                "value": 0.0
            },
            {
                "ID": "DHT11_T",
                "name": "DHT11",
                "tag": "Temp 2",
                "unit": "deg C",
                "value": 0.0
            },
            {
                "ID": "BMP180_T",
                "name": "BMP180",
                "tag": "Temp 3",
                "unit": "deg C",
                "value": 0.0
            },
            {
                "ID": "DHT11_H",
                "name": "DHT11",
                "tag": "Humidity",
                "unit": "%",
                "value": 0.0
            },
            {
                "ID": "BMP180_P",
                "name": "BMP180",
                "tag": "Pressure",
                "unit": "hPa",
                "value": 0.0
            },
            {
                "ID": "BH1750",
                "name": "BH1750",
                "tag": "Luminosity",
                "unit": "",
                "value": 0.0
            }
        ]

    def get_serial(self):
        # Serial begin and start up
        try:
            return Serial(self.port, 9600, timeout=2)
        except SerialException as err:
            print str(err)
            sys.exit(2)

    def read_sensors(self):
        while True:
            try:
                line = self.serial.readline()
            except SerialException as err:
                debug(str(err))
                sys.exit(2)

            line = line.strip()
            if line == "--> END <--":
                break
            try:
                sensor, value = line.split(":", 1)
                for ssor in self.sensors:
                    if ssor["ID"] == sensor:
                        ssor["value"] = float(value)
            except ValueError:
                continue


def debug(text):
    str_f_time = strftime("%d/%m/%y %H:%M:%S ", localtime())
    with open("log.txt", "a") as log:
        log.write("{} {}\n".format(str_f_time, text))