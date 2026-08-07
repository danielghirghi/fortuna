#include "configmanager.h"

#include <QSettings>
#include <QStandardPaths>
#include <QFile>
#include <QDir>

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
