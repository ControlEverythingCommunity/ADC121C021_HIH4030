// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C_HIH4030
// This code is designed to work with the ADC121C_I2CS_HIH4030 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADC121C021_I2CADC#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// ADC121C_HIH4030 I2C address is 0x50(80)
#define Addr 0x50

double humidity = 0.0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "ADC121C_HIH4030");
  Particle.variable("humidity", humidity);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[2];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data to 12 bits
  int raw_adc = ((data[0] & 0x0F) * 256) + data[1];
  humidity = (100.0 / 4095.0) * raw_adc;

  // Output data to dashboard
  Particle.publish("Relative Humidity : ", String(humidity));
  delay(1000);
}
