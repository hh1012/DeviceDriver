#include "device_driver.h"
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

class ReadFiveFail : public std::exception {
};

int DeviceDriver::read(long address) {
    int result = (int)(m_hardware->read(address));
    readPostConditionCheck(address, result);
    return result;
}

void DeviceDriver::readPostConditionCheck(long address, int read)
{
    for (int i = 0; i < 4; i++) {
        int testValue = (int)(m_hardware->read(address));
        if (read != testValue) {
            throw ReadFiveFail();
        }
    }
}

void DeviceDriver::write(long address, int data) {
    writePreconditionCheck(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::writePreconditionCheck(long address) {
    int testValue = (int)(m_hardware->read(address));
    if (testValue != 0xFF) {
        throw std::exception();
    }
}