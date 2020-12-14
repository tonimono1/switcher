#include "scheduleorganizer.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ScheduleOrganizer schedule;
    return a.exec();
}
