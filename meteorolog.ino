/*** MeteoroLog: just another mini weather station ***
 *
 *  DHT11 Basic Temperature-Humidity Sensor
 *      GND  --> Ground
 *      DATA --> Signal (pin 9)
 *      VCC  --> 5 Vcc
 *      Connect a 10K resistor from pin DATA to pin VCC of the sensor
 *
 *  BMP180 Barometric Pressure/Temperature/Altitude Sensor
 *      SCL --> analog 5
 *      SDA --> analog 4
 *      VIN --> 3.3V DC     *** Warning!!! ***
 *      GND --> Ground
 *
 *  BH1750 Light Intensity Sensor GY-30
 *      GND --> Ground
 *      ADD --> Ground
 *      SDA --> analog 4
 *      SCL --> analog 5
 *      VCC --> 3.3V DC     *** Warning!!! ***
 */

/*** Include Libraries ***/

#include <DHT_U.h>
#include <Adafruit_BMP085_U.h>
#include <BH1750.h>
#include <Wire.h>       // I2C library

/*** Define constants ***/

#define DHTPIN 9
#define DHTTYPE DHT11

/*** Initialize objects and variables ***/

// Initialize DHT11 sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

// Initialize BMP180 sensor
Adafruit_BMP085_Unified bmp= Adafruit_BMP085_Unified(10085);

// Initialize BH1750 sensor
BH1750 bh;

void setup(void) {
  Serial.begin(9600);
  while(!Serial);
  delay(1000);

  // Start DHT11 sensor
  dht.begin();

  // Start BMP180 sensor
  bmp.begin();

  // Start BH1750 sensor
  bh.begin();
}

void loop(void) {
  read_DHT11();
  read_BMP180();
  read_BH1750();
  Serial.println("--> END <--");
}

/* DHT11 Humidity */
void read_DHT11(void) {
  float humidity = 0.0;
  sensors_event_t event;

  dht.humidity().getEvent(&event);
  humidity = event.relative_humidity;
  if (isnan(humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("DHT11_H:");
    Serial.println(humidity);           // in %
  }
}

/* BMP180 Temperature & Atmospheric Pressure */
void read_BMP180(void) {
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    Serial.print("BMP180_P:");
    Serial.println(event.pressure);     // in hPa

    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("BMP180_T:");
    Serial.println(temperature);        // in Celsius
  }
  else {
    Serial.println("Sensor error");
  }
}

/* BH1750 Luminosity */
void read_BH1750(void) {
  uint16_t lux = bh.readLightLevel();
  Serial.print("BH1750:");
  Serial.println(lux);                  // in lux
}
