#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

class Database
{
public:
    static Database& instance();

    bool connect(const QString &path = "/tmp/finance.db");
    void disconnect();
    bool isOpen() const;

    QSqlDatabase db() const;

private:
    Database() = default;
    ~Database() = default;

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    QSqlDatabase m_db;
    static const QString CONNECTION_NAME;
};
#endif // DATABASE_H
