/** Digital Temperature Sensor Module Keyes DS18B20
 *  Terminals:
 *      G --> Ground
 *      R --> 5 Vcc
 *      Y --> Signal (pin 10)
 *      Connect a 4.7K resistor from pin R to pin Y of the sensor
 ** DHT11 basic temperature-humidity sensor
 *      GND  --> Ground
 *      DATA --> Signal (pin 9)
 *      VCC  --> 5 Vcc
 *      Connect a 10K resistor from pin DATA to pin VCC of the sensor
 */

#include <OneWire.h>
#include <DallasTemperature.h>
// #include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 9
#define DHTTYPE DHT11

#define DS18B20PIN 10
// How many bits to use for temperature values: 9, 10, 11 or 12
#define DS18B20_RESOLUTION 9
// Index of sensors connected to data pin, default: 0
#define DS18B20_INDEX 0

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

// DS18S20 Temperature chip i/o on pin 10
OneWire oneWire(DS18B20PIN);

// Tell Dallas Temperature Library to use oneWire library
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

void setup(void) {
  Serial.begin(9600);
  while(!Serial);
  delay(1000);

  // Start up DallasTemperature library
  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, DS18B20_INDEX);
  sensors.setResolution(sensorDeviceAddress, DS18B20_RESOLUTION);
  // Start DHT11 sensor
  dht.begin();
}

void loop(void) {
  temp_DS18B20();
  temp_hum_DHT11();
  Serial.println("--> END <--");
  delay(2000);      // Read frequency
}

void temp_DS18B20(void) {
  sensors.requestTemperatures();
  Serial.print("DS18B20:");
  Serial.println(sensors.getTempCByIndex(DS18B20_INDEX));
}

void temp_hum_DHT11(void) {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  // The heat index (HI) or humiture or humidex is an index that combines air
  // temperature and relative humidity in an attempt to determine the
  // human-perceived equivalent temperature—how hot it would feel if the
  // humidity were some other value.
  float hi = dht.computeHeatIndex(t, h, false);

  Serial.print("DHT11_T:");
  Serial.println(t);
  Serial.print("DHT11_H:");
  Serial.println(h);
  Serial.print("DHT11_HI:");
  Serial.println(hi);
}
