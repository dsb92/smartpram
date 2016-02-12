echo 0x2 > /sys/class/cplddrv/cpld/spi_route_reg
echo 0x1 > /sys/class/cplddrv/cpld/ext_serial_if_route_reg
insmod hotplug_zigbee_SPI_device.ko
insmod zigbee_mod.ko
