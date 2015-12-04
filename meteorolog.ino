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

#define ONE_WIRE_BUS 10

// DS18S20 Temperature chip i/o on pin 10
OneWire oneWire(ONE_WIRE_BUS);

// Tell Dallas Temperature Library to use oneWire library
DallasTemperature sensors(&oneWire);

void setup(void) {
  Serial.begin(9600);
  while(!Serial);

  Serial.println("Temperature Sensor DS18B20");
  delay(1000);

  // Start up DallasTemperature library
  sensors.begin();
}

void loop(void) {
  temp_ds18b20();
}

void temp_ds18b20(void) {
  Serial.println();
  Serial.print("Requesting temperature...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  Serial.print("Device 1 (index 0) = ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" Degrees C");
}
