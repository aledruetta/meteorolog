#MeteoroLog: just another mini weather station

## Deek-Robot Data Logging Shield V1.0

   SD-Card Reader (Arduino SD-Library compatible, chipSelect=10)

   https://www.arduino.cc/en/Reference/SD

   RTC DS1307 IC with battery (DS1307RTC Library compatible)

   http://playground.arduino.cc/code/time

   The circuit:

     * SD card attached to SPI bus as follows:
     * MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
     * MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
     * CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
     * CS - depends on your SD card shield or module (chipSelect=10).

## DHT22 Basic Temperature-Humidity Sensor

   https://github.com/adafruit/DHT-sensor-library

## BMP180 Barometric Pressure/Temperature/Altitude Sensor

   https://github.com/adafruit/Adafruit\_BMP085\_Unified

       SDA --> analog 4
       SCL --> analog 5
       VIN --> 3.3V DC      Warning!!!
       GND --> Ground

## BH1750 Light Intensity Sensor GY-30

       GND --> Ground
       ADD --> Ground
       SDA --> analog 4
       SCL --> analog 5
       VCC --> 3.3V DC      Warning!!!

## Install

	 - Install dependencies:

	 $ sudo apt install python-pip
	 $ pip install pyserial

	 $ chmod u+x meteorolog.py
	 $ ./meteorolog.py

