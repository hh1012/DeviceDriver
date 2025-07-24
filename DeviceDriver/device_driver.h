#pragma once
#include "flash_memory_device.h"
#include <stdexcept>
class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};

class ReadFailException : public std::exception {
public:
};

class WriteFailException : public std::exception {
public:

};