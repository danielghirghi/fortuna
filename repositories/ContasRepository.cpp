#include "ContasRepository.h"

#include <qsqlerror.h>
#include <qsqlquery.h>

#include "../core/database/Database.h"

QString ContasRepository::lastError(){ return m_lastError; }

QList<Conta> ContasRepository::listar()
{
    QList<Conta> contas;
    QSqlQuery query(Database::instance().db());

    if (!query.exec(R"(
        SELECT
            id,
            nome,
            banco,
            tipo,
            saldo_inicial,
            ativo
        FROM contas
        ORDER BY nome
    )"))
    {
        m_lastError = query.lastError().text();
        return contas;
    }

    while (query.next())
    {
        Conta conta;

        conta.id            = query.value("id").toInt();
        conta.nome          = query.value("nome").toString();
        conta.banco         = query.value("banco").toString();
        conta.tipo          = query.value("tipo").toString();
        conta.saldoInicial  = query.value("saldo_inicial").toDouble();
        conta.ativo         = query.value("ativo").toBool();

        contas.append(conta);
    }
    return contas;
}

Conta ContasRepository::buscarPorId(int id)
{
    Conta conta;
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        SELECT
            id,
            nome,
            banco,
            tipo,
            saldo_inicial,
            ativo
        FROM contas
        WHERE id = :id
        )");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return conta;
    }
    if (!query.next()) return conta;

    conta.id    = query.value("id").toInt();
    conta.nome  = query.value("nome").toString();
    conta.banco = query.value("banco").toString();
    conta.tipo  = query.value("tipo").toString();
    conta.saldoInicial = query.value("saldo_inicial").toDouble();
    conta.ativo = query.value("ativo").toBool();

    return conta;
}

bool ContasRepository::inserir(const Conta &conta)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO contas
        (
            nome,
            banco,
            tipo,
            saldo_inicial,
            ativo
        )
        VALUES
        (
            :nome,
            :banco,
            :tipo,
            :saldo,
            :ativo
        )
    )");
    query.bindValue(":nome",  conta.nome);
    query.bindValue(":banco", conta.banco);
    query.bindValue(":tipo",  conta.tipo);
    query.bindValue(":saldo", conta.saldoInicial);
    query.bindValue(":ativo", conta.ativo);

    return query.exec();
}

bool ContasRepository::atualizar(const Conta &conta)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE contas
        SET
            nome = :nome,
            banco = :banco,
            tipo = :tipo,
            saldo_inicial = :saldo,
            ativo = :ativo
        WHERE id = :id
    )");
    query.bindValue(":id",    conta.id);
    query.bindValue(":nome",  conta.nome);
    query.bindValue(":banco", conta.banco);
    query.bindValue(":tipo",  conta.tipo);
    query.bindValue(":saldo", conta.saldoInicial);
    query.bindValue(":ativo", conta.ativo);

    return query.exec();
}

bool ContasRepository::remover(int id)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    DELETE FROM contas
        WHERE id = :id
    )");
    query.bindValue(":id", id);

    return query.exec();
}

int ContasRepository::contar()
{
    QSqlQuery query(Database::instance().db());

    int total {};

    if (!query.exec(R"(
        SELECT COUNT(*) FROM contas
    )"))
    {
        m_lastError = query.lastError().text();
        return -1;
    }
    if (query.next())
    {
        total = query.value(0).toInt();
        return total;
    }
    return 0;
}

QList<Conta> ContasRepository::pesquisar(QString busca)
{
    QList<Conta> contas;
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        SELECT
            id,
            nome,
            banco,
            tipo,
            saldo_inicial,
            ativo
        FROM contas
        WHERE nome LIKE :busca
           OR banco LIKE :busca
           OR tipo LIKE :busca
        ORDER BY nome
    )");
    // LIKE no SQLite é case-insensitive EXCETO se tiver acento:
    // a = A ; porém ã != Ã
    // TODO: implementar busca accent-insensitive

    QString buscaComCuringa = "%" + busca + "%";

    query.bindValue(":busca", buscaComCuringa);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return contas;
    }

    while (query.next())
    {
        Conta conta;

        conta.id            = query.value("id").toInt();
        conta.nome          = query.value("nome").toString();
        conta.banco         = query.value("banco").toString();
        conta.tipo          = query.value("tipo").toString();
        conta.saldoInicial  = query.value("saldo_inicial").toDouble();
        conta.ativo         = query.value("ativo").toBool();

        contas.append(conta);
    }
    return contas;
}

