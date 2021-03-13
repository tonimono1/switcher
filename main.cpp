#include "scheduleorganizer.h"

#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    auto configPath = QStandardPaths::locate(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory);
    QFile configFile(configPath +"/switcherconfig.json");
    QCoreApplication a(argc, argv);
    ScheduleOrganizer schedule;
    if (!configFile.exists()) {
        if (configFile.open(QFile::WriteOnly)) {
            QJsonObject object{{"sunriseOffsetMinutes", 0}, {"sunsetOffsetMinutes", 0}, {"sunrisePreTimeMinutes", 120}, {"sunsetAfterTimeMinutes", 120}};
            QJsonDocument document(object);
            configFile.write(document.toJson());
            configFile.close();
        }
    } else {
        if (configFile.open(QFile::ReadOnly)) {
            QJsonDocument jsonDocument = QJsonDocument::fromJson(configFile.readAll());
            configFile.close();
            QJsonObject configObject = jsonDocument.object();

            QJsonValue  sunriseOffsetMinutesValue = configObject.value(QLatin1String("sunriseOffsetMinutes"));
            if (!sunriseOffsetMinutesValue.isUndefined()) {
                schedule.setSunriseOffsetMinutes(sunriseOffsetMinutesValue.toInt());
            }

            QJsonValue  sunsetOffsetMinutesValue = configObject.value(QLatin1String("sunsetOffsetMinutes"));
            if (!sunsetOffsetMinutesValue.isUndefined()) {
                schedule.setSunsetOffsetMinutes(sunsetOffsetMinutesValue.toInt());
            }
            QJsonValue  sunrisePreTimeMinutesValue = configObject.value(QLatin1String("sunrisePreTimeMinutes"));
            if (!sunrisePreTimeMinutesValue.isUndefined()) {
                schedule.setSunrisePreTimeMinutes(sunrisePreTimeMinutesValue.toInt());
            }
            QJsonValue  sunsetAfterTimeMinutesValue = configObject.value(QLatin1String("sunsetAfterTimeMinutes"));
            if (!sunsetAfterTimeMinutesValue.isUndefined()) {
                schedule.setSunsetAfterTimeMinutes(sunsetAfterTimeMinutesValue.toInt());
            }
        }
    }
    return a.exec();
}
