#include "scheduleorganizer.h"
#include "astrocalculator.h"
#include <QDebug>
#include <math.h>

ScheduleOrganizer::ScheduleOrganizer(QObject *parent) : QObject(parent)
{
    connect(&updateTimer, &QTimer::timeout, this, &ScheduleOrganizer::calculateNewEvents);
    connect(&sunsetEventTimer, &QTimer::timeout, this, &ScheduleOrganizer::sunsetEvent);
    connect(&sunriseEventTimer, &QTimer::timeout, this, &ScheduleOrganizer::sunriseEvent);
    calculateNewEvents();
}

void ScheduleOrganizer::calculateNewEvents()
{
    QDate currentDate = QDate::currentDate();

    double sunrise = AstroCalculator::calculateSunrise(51.370787, 7.929925, currentDate.dayOfYear(), 0);
    double sunset = AstroCalculator::calculateSunset(51.370787, 7.929925, currentDate.dayOfYear(), 0);

    QTime sunriseTime(static_cast<int>(sunrise),   static_cast<int>(std::round(std::fmod(sunrise, 1) * 60)));
    QTime sunsetTime(static_cast<int>(sunset),   static_cast<int>(std::round(std::fmod(sunset, 1) * 60)));
    scheduleSunriseEvent(sunriseTime);
    scheduleSunsetEvent(sunsetTime);
    updateTimer.stop();
    updateTimer.start(milliSecondsTo(QTime(0, 0)));
}

void ScheduleOrganizer::sunsetEvent()
{
    qDebug() << QStringLiteral("Sunset event at %1").arg(QDateTime::currentDateTimeUtc().toString());
}

void ScheduleOrganizer::sunriseEvent()
{
    qDebug() << QStringLiteral("Sunrise event at %1").arg(QDateTime::currentDateTimeUtc().toString());
}

int ScheduleOrganizer::milliSecondsTo(const QTime &toTime)
{
    constexpr int MILLI_SECONDS_PER_DAY = 24 * 60 * 60 * 1000;

    auto currentTime = QDateTime::currentDateTimeUtc().time();
    int           milliSeconds          = currentTime.msecsTo(toTime);
    if (milliSeconds < 0) {
        milliSeconds += MILLI_SECONDS_PER_DAY;
    }
    return milliSeconds;
}

void ScheduleOrganizer::scheduleSunriseEvent(const QTime &atTime)
{
    sunriseEventTimer.stop();
    sunriseEventTimer.start(milliSecondsTo(atTime));
    qDebug() << QStringLiteral("Next Sunrise Event at: %1").arg(atTime.toString());
}

void ScheduleOrganizer::scheduleSunsetEvent(const QTime &atTime)
{
    sunsetEventTimer.stop();
    sunsetEventTimer.start(milliSecondsTo(atTime));
    qDebug() << QStringLiteral("Next Sunset Event at: %1").arg(atTime.toString());
}
