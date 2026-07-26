#include "Database.h"

#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QMessageBox>

#include <QStandardPaths>
#include <QDir>

const QString Database::CONNECTION_NAME = "finance_connection";

// Não cria a database nem as tabelas, por enquanto ele assume que o banco e as tabelas já existem
Database& Database::instance()
{
    static Database instance;
    return instance;
}

bool Database::connect()
{
    // Encontra o caminho padrão da base de dados, a depender do OS:
    // Linux: ~/.local/share/fortuna/
    // Windows: AppData\Local\Fortuna\ ou AppData\Roaming\Fortuna\
    // macOS: ~/Library/Application Support/Fortuna/
    QString pastaDados = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(pastaDados);
    QString caminhoBanco = pastaDados + "/finance.db";

    if (m_db.isOpen())
        return true;

    if (!QFile::exists(caminhoBanco)) {
        qWarning() << "Arquivo de banco de dados não encontrado:" << caminhoBanco;
        return false;
    }

    // Evita recriar a conexão se já existir com esse nome
    if (QSqlDatabase::contains(CONNECTION_NAME)) {
        m_db = QSqlDatabase::database(CONNECTION_NAME);
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
        m_db.setDatabaseName(caminhoBanco);
    }

    if (!m_db.open()) {
        qWarning() << "Erro ao abrir o banco de dados:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "Conectado ao banco de dados:" << caminhoBanco;
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