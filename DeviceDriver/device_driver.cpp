#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}


int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    int testValue = (int)(m_hardware->read(address));
    if (testValue != 0xFF) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);
}