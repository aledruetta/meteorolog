/** Digital Temperature Sensor Module Keyes DS18B20
 *
 *  Terminals:
 *
 *      G --> Ground
 *      R --> 5 Vcc
 *      Y --> Signal (pin 10)
 */

#include <OneWire.h>
#include <DallasTemperature.h>

// Sensor input pin
#define DATA_PIN 10
// How many bits to use for temperature values: 9, 10, 11 or 12
#define SENSOR_RESOLUTION 9
// Index of sensors connected to data pin, default: 0
#define SENSOR_INDEX 0

// DS18S20 Temperature chip i/o on pin 10
OneWire oneWire(DATA_PIN);

// Tell Dallas Temperature Library to use oneWire library
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

void setup(void) {
  Serial.begin(9600);
  while(!Serial);

  Serial.println("Temperature Sensor DS18B20");
  delay(1000);

  // Start up DallasTemperature library
  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, 0);
  sensors.setResolution(sensorDeviceAddress, SENSOR_RESOLUTION);
}

void loop(void) {
  temp_ds18b20();
  delay(5000);      // Read frequency
}

void temp_ds18b20(void) {
  Serial.println();
  Serial.print("Requesting temperature...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  Serial.print("Device 1 (index 0) = ");
  Serial.print(sensors.getTempCByIndex(SENSOR_INDEX));
  Serial.println(" Degrees C");
}
