/*** MeteoroLog: just another mini weather station ***
 *
 *  DS18B20 Digital Temperature Sensor Module Keyes
 *      G --> Ground
 *      R --> 5 Vcc
 *      Y --> Signal (pin 10)
 *      Connect a 4.7K resistor from pin R to pin Y of the sensor
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
 *      VDD --> 3.3V DC     *** Warning!!! ***
 *      GND --> Ground
 */

/*** Include Libraries ***/

#include <DallasTemperature.h>
#include <DHT_U.h>
#include <Adafruit_BMP085_U.h>

/*** Define constants ***/

#define DHTPIN 9
#define DHTTYPE DHT11

#define DS18B20PIN 10
// How many bits to use for temperature values: 9, 10, 11 or 12
#define DS18B20_RESOLUTION 9
// Index of sensors connected to data pin, default: 0
#define DS18B20_INDEX 0

/*** Initialize objects and variables ***/

// Initialize DHT sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

// DS18S20 Temperature chip i/o on pin 10
OneWire oneWire(DS18B20PIN);

// Tell Dallas Temperature Library to use oneWire library
DallasTemperature ds18b20(&oneWire);
DeviceAddress sensorDeviceAddress;

// Initialize BMP180 sensor
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup(void) {
  Serial.begin(9600);
  while(!Serial);
  delay(1000);

  // Start DS18B20 sensor
  ds18b20.begin();
  ds18b20.getAddress(sensorDeviceAddress, DS18B20_INDEX);
  ds18b20.setResolution(sensorDeviceAddress, DS18B20_RESOLUTION);
  // Start DHT11 sensor
  dht.begin();

  // Start BMP180 sensor
  if(!bmp.begin())
  {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}

void loop(void) {
  read_DS18B20();
  read_DHT11();
  read_BMP180();
  Serial.println("--> END <--");
}

void read_DS18B20(void) {
  ds18b20.requestTemperatures();
  Serial.print("DS18B20:");
  Serial.println(ds18b20.getTempCByIndex(DS18B20_INDEX));
}

void read_DHT11(void) {
  float temperature = 0.0, humidity = 0.0;
  sensors_event_t dht11;

  dht.temperature().getEvent(&dht11);
  temperature = dht11.temperature;
  if (isnan(temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("DHT11_T:");
    Serial.println(temperature);
  }

  dht.humidity().getEvent(&dht11);
  humidity = dht11.relative_humidity;
  if (isnan(humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("DHT11_H:");
    Serial.println(humidity);
  }
}

void read_BMP180(void) {
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    /* Display atmospheric pressue in hPa */
    Serial.print("BMP180_P:");
    Serial.println(event.pressure);

    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("BMP180_T:");
    Serial.println(temperature);
  }
  else {
    Serial.println("Sensor error");
  }
}
