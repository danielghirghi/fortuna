#include "CategoriasRepository.h"

#include <qsqlerror.h>
#include <qsqlquery.h>

#include "../core/database/Database.h"

QString CategoriasRepository::lastError(){ return m_lastError; }

QList<Categoria> CategoriasRepository::listar()
{
    QList<Categoria> categorias;

    QSqlQuery query(Database::instance().db());

    if (!query.exec(R"(
        SELECT
            id,
            nome,
            grupo,
            tipo,
            ativo
        FROM categorias
        ORDER BY nome
    )"))
    {
        m_lastError = query.lastError().text();
        return categorias;
    }

    while (query.next())
    {
        Categoria categoria;

        categoria.id    = query.value("id").toInt();
        categoria.nome  = query.value("nome").toString();
        categoria.grupo = query.value("grupo").toString();
        categoria.tipo  = query.value("tipo").toString();
        categoria.ativo = query.value("ativo").toBool();

        categorias.append(categoria);
    }

    return categorias;
}

Categoria CategoriasRepository::buscarPorId(int id)
{
    Categoria categoria;
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        SELECT
            id,
            nome,
            grupo,
            tipo,
            ativo
        FROM categorias
        WHERE id = :id
        )");

    query.bindValue(":id", id);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return categoria;
    }
    if (!query.next()) return categoria;

    categoria.id    = query.value("id").toInt();
    categoria.nome  = query.value("nome").toString();
    categoria.grupo = query.value("grupo").toString();
    categoria.tipo  = query.value("tipo").toString();
    categoria.ativo = query.value("ativo").toBool();

    return categoria;
}

bool CategoriasRepository::inserir(const Categoria &categoria)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO categorias
        (
            nome,
            grupo,
            tipo,
            ativo
        )
        VALUES
        (
            :nome,
            :grupo,
            :tipo,
            :ativo
        )
    )");
    query.bindValue(":nome",  categoria.nome);
    query.bindValue(":grupo", categoria.grupo);
    query.bindValue(":tipo",  categoria.tipo);
    query.bindValue(":ativo", categoria.ativo);

    return query.exec();
}

bool CategoriasRepository::atualizar(const Categoria &categoria)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE categorias
        SET
            nome =  :nome,
            grupo = :grupo,
            tipo =  :tipo,
            ativo = :ativo
        WHERE id = :id
    )");
    query.bindValue(":id",    categoria.id);
    query.bindValue(":nome",  categoria.nome);
    query.bindValue(":grupo", categoria.grupo);
    query.bindValue(":tipo",  categoria.tipo);
    query.bindValue(":ativo", categoria.ativo);

    return query.exec();
}

bool CategoriasRepository::remover(int id)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    DELETE FROM categorias
        WHERE id = :id
    )");
    query.bindValue(":id", id);

    return query.exec();
}

int CategoriasRepository::contar()
{
    QSqlQuery query(Database::instance().db());

    int total {};

    if (!query.exec(R"(
        SELECT COUNT(*) FROM categorias
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

