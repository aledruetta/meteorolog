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
#include <SoftwareSerial.h>

// Sensor input pin
#define DS18B20 10
// How many bits to use for temperature values: 9, 10, 11 or 12
#define DS18B20_RESOLUTION 9
// Index of sensors connected to data pin, default: 0
#define DS18B20_INDEX 0

// DS18S20 Temperature chip i/o on pin 10
OneWire oneWire(DS18B20);

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
}

void loop(void) {
  temp_DS18B20();
  Serial.println("::END READS::");
  delay(1000);      // Read frequency
}

void temp_DS18B20(void) {
  sensors.requestTemperatures();
  Serial.print("DS18B20:");
  Serial.println(sensors.getTempCByIndex(DS18B20_INDEX));
}
