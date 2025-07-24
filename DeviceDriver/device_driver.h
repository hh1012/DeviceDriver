#pragma once
#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
<<<<<<< HEAD
=======
};

class ReadFailException : public std::exception {
public:
};

class WriteFailException : public std::exception {
public:
>>>>>>> 5894726 ([feature] write)
};