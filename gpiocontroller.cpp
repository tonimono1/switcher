#include "gpiocontroller.h"
#include <QDebug>
#include <QFile>


bool GpioController::switchGpio(uint8_t number, bool value)
{
    QFile file(QStringLiteral("/sys/class/gpio/gpio%2/value").arg(QString::number(number)));
    if (file.open(QFile::WriteOnly)) {
        file.write(value ? "1": "0");
        file.waitForBytesWritten(1000);
        file.close();
        return true;
    } else {
        return false;
    }
}
