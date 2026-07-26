#include "Database.h"

#include <QDebug>
#include <QFile>
#include <QSqlError>

#include <QMessageBox>

const QString Database::CONNECTION_NAME = "finance_connection";

Database& Database::instance()
{
    static Database instance;
    return instance;
}

bool Database::connect(const QString &path)
{
    if (m_db.isOpen())
        return true;

    if (!QFile::exists(path)) {
        qWarning() << "Arquivo de banco de dados não encontrado:" << path;
        return false;
    }

    // Evita recriar a conexão se já existir com esse nome
    if (QSqlDatabase::contains(CONNECTION_NAME)) {
        m_db = QSqlDatabase::database(CONNECTION_NAME);
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
        m_db.setDatabaseName(path);
    }

    if (!m_db.open()) {
        qWarning() << "Erro ao abrir o banco de dados:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "Conectado ao banco de dados:" << path;
    return true;
}

void Database::disconnect()
{
    if (m_db.isOpen())
        m_db.close();
}

bool Database::isOpen() const
{
    return m_db.isOpen();
}

QSqlDatabase Database::db() const
{
    return m_db;
}