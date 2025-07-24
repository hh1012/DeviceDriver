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

private:
    void writePreconditionCheck(long address);
    void readPostConditionCheck(long address, int read);
};

class Application {
public:
    Application(DeviceDriver* dd) : dd{ dd } {}

    void readAndprint(long startAddr, long endAddr) {
        for (long addr = startAddr; addr <= endAddr; addr++) {
            dd->read(addr);
        }
    }

    void writeAll(unsigned char value) {
        for (long addr = 0x00; addr <= 0x04; addr++) {
            dd->write(addr, value);
        }
    }

private:
    DeviceDriver* dd;
};