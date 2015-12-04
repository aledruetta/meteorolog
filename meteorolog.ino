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
#define ds18b20 10
// How many bits to use for temperature values: 9, 10, 11 or 12
#define SENSOR_RESOLUTION 9
// Index of sensors connected to data pin, default: 0
#define SENSOR_INDEX 0

// DS18S20 Temperature chip i/o on pin 10
OneWire oneWire(ds18b20);

// Tell Dallas Temperature Library to use oneWire library
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

void setup(void) {
  Serial.begin(9600);
  while(!Serial);
  delay(1000);

  // Start up DallasTemperature library
  sensors.begin();
  sensors.getAddress(sensorDeviceAddress, SENSOR_INDEX);
  sensors.setResolution(sensorDeviceAddress, SENSOR_RESOLUTION);
}

void loop(void) {
  temp_ds18b20();
  delay(1000);      // Read frequency
}

void temp_ds18b20(void) {
  sensors.requestTemperatures();
  Serial.print("DS18B20:");
  Serial.println(sensors.getTempCByIndex(SENSOR_INDEX));
}
