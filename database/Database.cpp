#include "Database.h"

#include <QDebug>
#include <QSqlError>
#include <qsqlquery.h>

#include <QRegularExpression>
#include <sqlite3.h>

#include <QStandardPaths>
#include <QFile>
#include <QDir>

#include <QMessageBox>

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

    bool bancoNovo = !QFile::exists(caminhoBanco);

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

    if (bancoNovo)
        criarBanco();

    if (m_db.isOpen())
        return true;

    // if (!QFile::exists(caminhoBanco)) {
    //     qWarning() << "Arquivo de banco de dados não encontrado:" << caminhoBanco;
    //     // return false;
    //     return inicializarBanco();
    // }

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

bool Database::inicializarBanco()
{
    int versao = obterVersao();

    if (versao == 0)
    {
        criarBanco();
    }

    //atualizarBanco();

    return true;
}

int Database::obterVersao()
{
    QSqlQuery query(m_db);

    query.exec("PRAGMA user_version");

    if (query.next())
        return query.value(0).toInt();

    return 0;
}

void Database::definirVersao(int versao)
{
    QSqlQuery query(m_db);

    query.exec(
        QString("PRAGMA user_version = %1")
            .arg(versao));
}

bool Database::criarBanco()
{
    executarArquivo(":/resources/sql/schema.sql");
    executarArquivo(":/resources/sql/views.sql");
    executarArquivo(":/resources/sql/triggers.sql");

    //definirVersao(DB_VERSION);

    return true;
}

bool Database::executarArquivo(QString path)
{
    QFile arquivo(path);
    if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Erro ao abrir o arquivo:" << path << arquivo.errorString();
        return false;
    }

    QTextStream in(&arquivo);
    QString todoOConteudo = in.readAll();
    arquivo.close();

    QStringList comandos = separarComandosSQL(todoOConteudo);

    QSqlDatabase &db = m_db;
    db.transaction();
    QSqlQuery query(db);

    for (const QString &comando : comandos) {
        QString comandoLimpo = comando.trimmed();
        if (comandoLimpo.isEmpty()) continue;

        if (!query.exec(comandoLimpo)) {
            qWarning() << "Erro ao executar comando:" << query.lastError().text();
            qDebug() << "Comando com falha:" << comandoLimpo;
            db.rollback();
            return false;
        }
    }

    return db.commit();
}

QStringList Database::separarComandosSQL(const QString &sql)
{
    QStringList comandos;
    QString atual;
    int depth = 0;
    int i = 0;
    const int n = sql.length();

    auto isWordChar = [](QChar c) {
        return c.isLetterOrNumber() || c == '_';
    };

    while (i < n) {
        QChar c = sql[i];

        // Comentário de linha: -- até o fim da linha
        if (c == '-' && i + 1 < n && sql[i+1] == '-') {
            int start = i;
            while (i < n && sql[i] != '\n') i++;
            atual += sql.mid(start, i - start);
            continue;
        }

        // Comentário de bloco /* ... */
        if (c == '/' && i + 1 < n && sql[i+1] == '*') {
            int start = i;
            i += 2;
            while (i + 1 < n && !(sql[i] == '*' && sql[i+1] == '/')) i++;
            i = qMin(i + 2, n);
            atual += sql.mid(start, i - start);
            continue;
        }

        // String literal 'texto' (com '' como aspas escapada)
        if (c == '\'') {
            int start = i;
            i++;
            while (i < n) {
                if (sql[i] == '\'') {
                    if (i + 1 < n && sql[i+1] == '\'') { i += 2; continue; }
                    i++;
                    break;
                }
                i++;
            }
            atual += sql.mid(start, i - start);
            continue;
        }

        // Identificador "entre aspas duplas"
        if (c == '"') {
            int start = i;
            i++;
            while (i < n && sql[i] != '"') i++;
            if (i < n) i++;
            atual += sql.mid(start, i - start);
            continue;
        }

        // Palavra-chave: BEGIN / CASE abrem bloco, END fecha
        if (c.isLetter() || c == '_') {
            int start = i;
            while (i < n && isWordChar(sql[i])) i++;
            QString palavra = sql.mid(start, i - start);
            atual += palavra;

            QString up = palavra.toUpper();
            if (up == "BEGIN" || up == "CASE") {
                depth++;
            } else if (up == "END") {
                depth--;
                if (depth < 0) depth = 0;
            }
            continue;
        }

        // ';' só separa comando se estivermos FORA de qualquer bloco (depth == 0)
        if (c == ';' && depth == 0) {
            QString comando = atual.trimmed();
            if (!comando.isEmpty())
                comandos.append(comando);
            atual.clear();
            i++;
            continue;
        }

        atual += c;
        i++;
    }

    QString resto = atual.trimmed();
    if (!resto.isEmpty())
        comandos.append(resto);

    return comandos;
}
