#ifndef SCHEDULEORGANIZER_H
#define SCHEDULEORGANIZER_H

#include <QObject>
#include <QTime>
#include <QTimer>

class ScheduleOrganizer : public QObject
{
    Q_OBJECT

    enum State {
        Night,
        TimeBeforeSunrise,
        Day,
        TimeAfterSunset,
        Unkown
    };

public:
    explicit ScheduleOrganizer(QObject *parent = nullptr);
    void setSunriseOffsetMinutes(int value);
    void setSunsetOffsetMinutes(int value);
    void setSunrisePreTimeMinutes(int value);
    void setSunsetAfterTimeMinutes(int value);

private:
    int  milliSecondsTo(const QTime &toTime);
    void scheduleSunriseEvent(const QTime &atTime);
    void scheduleSunsetEvent(const QTime &atTime);
    void switchOn(bool on);

private slots:
    void calculateNewEvents();
    void checkCurrentState();

private:
    QTimer updateTimer;
    int dayOfYear = -1;
    QTime sunriseTime;
    QTime sunsetTime;
    State state = Unkown;

    int sunriseOffsetMinutes = 0;
    int sunsetOffsetMinutes = 0;
    int sunrisePreTimeMinutes = 120;
    int sunsetAfterTimeMinutes = 120;
};

#endif // SCHEDULEORGANIZER_H
