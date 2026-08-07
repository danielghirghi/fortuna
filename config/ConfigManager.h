#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>
#include <QSettings>

class ConfigManager
{
public:
    static QString databasePath();
    static void setDatabasePath(const QString& path);
    static QString defaultDatabasePath();

private:
    static QSettings settings();
};

#endif // CONFIGMANAGER_H
