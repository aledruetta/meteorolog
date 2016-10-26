/*** MeteoroLog: just another mini weather station ***
 *
 * ## Deek-Robot Data Logging Shield V1.0
 *    SD-Card Reader (Arduino SD-Library compatible, chipSelect=10)
 *    https://www.arduino.cc/en/Reference/SD
 *    RTC DS1307 IC with battery (DS1307RTC Library compatible)
 *    http://playground.arduino.cc/code/time
 *
 * ## DHT22 Basic Temperature-Humidity Sensor
 *    https://github.com/adafruit/Adafruit_Sensor
 *    https://github.com/adafruit/Adafruit_DHT_Unified
 *    https://github.com/adafruit/DHT-sensor-library
 *
 * ## BMP180 Barometric Pressure/Temperature/Altitude Sensor
 *    https://github.com/adafruit/Adafruit\_BMP085\_Unified
 *        SDA --> analog 4
 *        SCL --> analog 5
 *        VIN --> 3.3V DC      Warning!!!
 *        GND --> Ground
 *
 * ## BH1750 Light Intensity Sensor GY-30
 *    https://github.com/claws/BH1750
 *        GND --> Ground
 *        ADD --> Ground
 *        SDA --> analog 4
 *        SCL --> analog 5
 *        VCC --> 3.3V DC      Warning!!!
 *
 * ## Testing Serial (Python 2.x)
 *
 *    $ sudo apt install python-pip
 *    $ pip install pyserial
 *    $ python
 *
 *    >>> from serial import Serial
 *    >>> with Serial('/dev/ttyUSB0', 9600) as ser:
 *    >>>     while(True):
 *    >>>         print ser.readline().rstrip()
 */

/*** Include Libraries ***/

#include <DHT_U.h>
#include <Adafruit_BMP085_U.h>
#include <BH1750.h>
#include <Wire.h>       // I2C library

/*** Define constants ***/

#define DHTPIN 2
#define DHTTYPE DHT22

/*** Initialize objects and variables ***/

// Initialize DHT11 sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

// Initialize BMP180 sensor
Adafruit_BMP085_Unified bmp= Adafruit_BMP085_Unified(10085);

// Initialize BH1750 sensor
BH1750 bh;

void setup(void) {

  // Start Serial
  Serial.begin(9600);
  while(!Serial);
  delay(1000);

  // Start DHT22 sensor
  dht.begin();

  // Start BMP180 sensor
  bmp.begin();

  // Start BH1750 sensor
  bh.begin();
}

void loop(void) {
  read_DHT22();
  read_BMP180();
  read_BH1750();
  Serial.println("--> END <--");

  delay(5000);      // read frequency
}

/*** DHT11 Humidity & Temperature ***/

void read_DHT22(void) {
  float humidity = 0.0;
  float temperature = 0.0;
  sensors_event_t event;

  dht.humidity().getEvent(&event);
  humidity = event.relative_humidity;
  if (isnan(humidity)) {
    Serial.println("Error:DHT22_H_Sensor");
  }
  else {
    Serial.print("DHT22_H:");
    Serial.println(humidity);           // in %
  }

  dht.temperature().getEvent(&event);
  temperature = event.temperature;
  if (isnan(temperature)) {
    Serial.println("Error:DHT22_T_Sensor");
  }
  else {
    Serial.print("DHT22_T:");
    Serial.println(temperature);        // in ºC
  }
}

/*** BMP180 Temperature & Atmospheric Pressure ***/

void read_BMP180(void) {
  float temperature = 0.0;
  float pressure = 0.0;

  sensors_event_t eventBMP;
  bmp.getEvent(&eventBMP);
  pressure = eventBMP.pressure;
  bmp.getTemperature(&temperature);

  if (isnan(temperature)) {
    Serial.println("Error:BMP180_T_Sensor");
  }
  else {
    Serial.print("BMP180_T:");
    Serial.println(temperature);        // in Celsius
  }

  if (isnan(pressure)) {
    Serial.println("Error:BMP180_P_Sensor");
  }
  else {
    Serial.print("BMP180_P:");
    Serial.println(pressure);           // in hPa
  }
}

/*** BH1750 Luminosity ***/

void read_BH1750(void) {
  uint16_t lux = bh.readLightLevel();

  if (isnan(lux)) {
    Serial.println("Error:BH1750_Sensor");
  }
  else {
    Serial.print("BH1750:");
    Serial.println(lux);                // in lux
  }
}
