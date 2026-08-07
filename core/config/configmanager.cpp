#include "configmanager.h"

#include <QSettings>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

QString ConfigManager::defaultDatabasePath()
{
    QString pastaDados = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(pastaDados);
    return pastaDados + "/finance.db";
}


QString ConfigManager::databasePath()
{
    QSettings settings("Daniel", "Fortuna");

    return settings.value(
                       "database/path",
                       defaultDatabasePath()
                       ).toString();
}


void ConfigManager::setDatabasePath(const QString& path)
{
    QSettings settings("Daniel", "Fortuna");
    settings.setValue("database/path", path);
}

QString ConfigManager::testDatabaseFolder()
{
#ifdef QT_DEBUG

    QFile file("config/localsettings.json");

    if(file.open(QIODevice::ReadOnly))
    {
        auto json = QJsonDocument::fromJson(file.readAll());

        return json.object()
            .value("testDatabaseFolder")
            .toString();
    }

#endif

    return QDir::homePath();
}
