#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <QProcess>



class GpioController
{
public:
    GpioController() = delete;
    static bool switchGpio(uint8_t number, bool value);
};

#endif // GPIOCONTROLLER_H
