#include "scheduleorganizer.h"

#include <QDebug>
#include <QProcess>
#include <math.h>

#include "astrocalculator.h"
#include "gpiocontroller.h"


ScheduleOrganizer::ScheduleOrganizer(QObject *parent) : QObject(parent) 
{
  connect(&updateTimer, &QTimer::timeout, this,
          &ScheduleOrganizer::checkCurrentState);
  checkCurrentState();
  updateTimer.setInterval(60 * 1000);
  updateTimer.start();
}

void ScheduleOrganizer::calculateNewEvents() 
{
  QDate currentDate = QDate::currentDate();

  double sunrise = AstroCalculator::calculateSunrise(
      51.370787, 7.929925, currentDate.dayOfYear(), 0);
  double sunset = AstroCalculator::calculateSunset(51.370787, 7.929925,
                                                   currentDate.dayOfYear(), 0);

  sunriseTime = QTime(static_cast<int>(sunrise),
                    static_cast<int>(std::round(std::fmod(sunrise, 1) * 60)));
  sunsetTime = QTime(static_cast<int>(sunset),
                   static_cast<int>(std::round(std::fmod(sunset, 1) * 60)));

  qDebug() << QStringLiteral("Sunrise at %1  Sunset at %2").arg(sunriseTime.toString(), sunsetTime.toString());
}

void ScheduleOrganizer::checkCurrentState()
{
    int newDayOfYear = QDate::currentDate().dayOfYear();
    if (newDayOfYear != dayOfYear) {
        calculateNewEvents();
        dayOfYear = newDayOfYear;
    }
    QTime currentTime = QDateTime::currentDateTimeUtc().time();
    QTime offset (2, 0);
    auto  switchOnTimeSunrise = sunriseTime.addSecs(-2 * 60 * 60);
    auto  switchOffTimeSunset = sunsetTime.addSecs(2 * 60 * 60);

    if ((currentTime < switchOnTimeSunrise)) {
        if (state != Night) {
            qDebug() << QStringLiteral("It's night --> switch off");
            switchOn(false);
            state = Night;
        }
    } else if ((currentTime >= switchOnTimeSunrise) && (currentTime < sunriseTime)) {
        if (state != OffsetBeforeSunrise) {
            qDebug() << QStringLiteral("It's %1 before sunrise --> switch on").arg(offset.toString());
            switchOn(true);
            state = OffsetBeforeSunrise;
        }
    } else if ((currentTime >= sunriseTime) && (currentTime < sunsetTime)) {
        if (state != Day) {
            qDebug() << QStringLiteral("It's daytime --> switch off");
            switchOn(false);
            state = Day;
        }
    } else if ((currentTime >= sunsetTime) && (currentTime < switchOffTimeSunset)) {
        if (state != OffsetAfterSunset) {
            qDebug() << QStringLiteral("It's sunset --> switch on");
            switchOn(true);
            state = OffsetAfterSunset;
        }
    } else if (currentTime >= switchOffTimeSunset) {
        if (state != Night) {
            switchOn(false);
            qDebug() << QStringLiteral("It's %1 after sunset --> switch off").arg(offset.toString());
            state = Night;
        }
    } else {
        qDebug() << QStringLiteral("Should not happen");
        state = Unkown;
    }
}

void ScheduleOrganizer::switchOn(bool on)
{
    GpioController::switchGpio(21, !on);
}
