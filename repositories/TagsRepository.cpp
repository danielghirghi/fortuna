#include "TagsRepository.h"

#include <qsqlerror.h>
#include <qsqlquery.h>

#include "../database/Database.h"

QString TagsRepository::lastError(){ return m_lastError; }

QList<Tag> TagsRepository::listar()
{
    QList<Tag> tags;

    QSqlQuery query(Database::instance().db());

    if (!query.exec(R"(
        SELECT
            id,
            nome,
            cor,
            ativo
        FROM tags
        ORDER BY nome
    )"))
    {
        m_lastError = query.lastError().text();
        return tags;
    }

    while (query.next())
    {
        Tag tag;

        tag.id    = query.value("id").toInt();
        tag.nome  = query.value("nome").toString();
        tag.cor   = query.value("cor").toString();
        tag.ativo = query.value("ativo").toBool();

        tags.append(tag);
    }

    return tags;
}

Tag TagsRepository::buscarPorId(int id)
{
    Tag tag;
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        SELECT
            id,
            nome,
            cor,
            ativo
        FROM tags
        WHERE id = :id
        )");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return tag;
    }
    if (!query.next()) return tag;

    tag.id    = query.value("id").toInt();
    tag.nome  = query.value("nome").toString();
    tag.cor   = query.value("cor").toString();
    tag.ativo = query.value("ativo").toBool();

    return tag;
}

bool TagsRepository::inserir(const Tag &tag)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO tags
        (
            nome,
            cor,
            ativo
        )
        VALUES
        (
            :nome,
            :cor,
            :ativo
        )
    )");
    query.bindValue(":nome",  tag.nome);
    query.bindValue(":cor",   tag.cor);
    query.bindValue(":ativo", tag.ativo);

    return query.exec();
}

bool TagsRepository::atualizar(const Tag &tag)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE tags
        SET
            nome = :nome,
            cor = :cor,
            ativo = :ativo
        WHERE id = :id
    )");
    query.bindValue(":id",    tag.id);
    query.bindValue(":nome",  tag.nome);
    query.bindValue(":cor",   tag.cor);
    query.bindValue(":ativo", tag.ativo);

    return query.exec();
}

bool TagsRepository::remover(int id)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    DELETE FROM tags
        WHERE id = :id
    )");
    query.bindValue(":id", id);

    return query.exec();
}

int TagsRepository::contar()
{
    QSqlQuery query(Database::instance().db());

    int total {};

    if (!query.exec(R"(
        SELECT COUNT(*) FROM tags
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

