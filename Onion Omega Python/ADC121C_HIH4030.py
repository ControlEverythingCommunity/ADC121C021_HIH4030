# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# ADC121C_HIH4030
# This code is designed to work with the ADC121C_I2CS_HIH4030 I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# ADC121C_HIH4030 address, 0x50(80)
# Select configuration register, 0x02(02)
#		0x20(32)	Automatic conversion mode enabled
i2c.writeByte(0x50, 0x02, 0x20)

time.sleep(0.5)

# ADC121C_HIH4030 address, 0x50(80)
# Read data back from 0x00(0), 2 bytes
# raw_adc MSB, raw_adc LSB
data = i2c.readBytes(0x50, 0x00, 2)

# Convert the data to 12-bits
raw_adc = ((data[0] & 0x0F) * 256) + data[1]
humidity = (100.0 / 4095.0) * raw_adc

# Output data to screen
print "Relative Humidity : %.2f %%RH" %humidity
