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
        OffsetBeforeSunrise,
        Day,
        OffsetAfterSunset,
        Unkown
    };

public:
    explicit ScheduleOrganizer(QObject *parent = nullptr);

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
};

#endif // SCHEDULEORGANIZER_H
