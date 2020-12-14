#ifndef SCHEDULEORGANIZER_H
#define SCHEDULEORGANIZER_H

#include <QObject>
#include <QTime>
#include <QTimer>

class ScheduleOrganizer : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleOrganizer(QObject *parent = nullptr);

private:
    int  milliSecondsTo(const QTime &toTime);
    void scheduleSunriseEvent(const QTime &atTime);
    void scheduleSunsetEvent(const QTime &atTime);

private slots:
    void calculateNewEvents();
    void sunsetEvent();
    void sunriseEvent();

private:
    QTimer updateTimer;
    QTimer sunsetEventTimer;
    QTimer sunriseEventTimer;
};

#endif // SCHEDULEORGANIZER_H
