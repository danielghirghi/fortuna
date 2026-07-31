#include "MovimentacoesRepository.h"

#include <qsqlerror.h>
#include <qsqlquery.h>

#include "../database/Database.h"

QString MovimentacoesRepository::lastError(){ return m_lastError; }

QList<Movimentacao> MovimentacoesRepository::listar()
{
    QList<Movimentacao> movimentacoes;
    QSqlQuery query(Database::instance().db());

    if (!query.exec(R"(
        SELECT
            m.id,
            m.data,
            m.descricao,
            co.nome AS conta_origem,
            cd.nome AS conta_destino,
            cat.nome AS categoria,
            m.valor,
            m.tipo AS tipo
        FROM movimentacoes m
        LEFT JOIN contas co ON co.id = m.conta_origem_id
        LEFT JOIN contas cd ON cd.id = m.conta_destino_id
        LEFT JOIN categorias cat ON cat.id = m.categoria_id
        ORDER BY m.data DESC
    )"))
    {
        m_lastError = query.lastError().text();
        return movimentacoes;
    }

    while (query.next())
    {
        Movimentacao movimentacao;
        movimentacao.id        = query.value("id").toInt();
        movimentacao.data      = query.value("data").toDate();
        movimentacao.origem    = query.value("conta_origem").toString();
        movimentacao.destino   = query.value("conta_destino").toString();
        movimentacao.categoria = query.value("categoria").toString();
        movimentacao.descricao = query.value("descricao").toString();
        movimentacao.setTipo(query.value("tipo").toString());
        movimentacao.valor     = query.value("valor").toDouble();

        movimentacoes.append(movimentacao);
    }
    return movimentacoes;
}

Movimentacao MovimentacoesRepository::buscarPorId(int id)
{
    Movimentacao movimentacao;
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        SELECT
            m.id,
            m.data,
            m.descricao,
            co.nome AS conta_origem,
            cd.nome AS conta_destino,
            cat.nome AS categoria,
            m.valor,
            m.tipo AS tipo
        FROM movimentacoes m
        LEFT JOIN contas co ON co.id = m.conta_origem_id
        LEFT JOIN contas cd ON cd.id = m.conta_destino_id
        LEFT JOIN categorias cat ON cat.id = m.categoria_id
        WHERE m.id = :id
        )");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return movimentacao;
    }
    if (!query.next()) return movimentacao;

    movimentacao.id        = query.value("id").toInt();
    movimentacao.data      = query.value("data").toDate();
    movimentacao.valor     = query.value("valor").toDouble();
    movimentacao.descricao = query.value("descricao").toString();
    movimentacao.setTipo(query.value("tipo").toString());
    movimentacao.origem    = query.value("conta_origem").toString();
    movimentacao.destino   = query.value("conta_destino").toString();
    movimentacao.categoria = query.value("categoria").toString();

    return movimentacao;
}

bool MovimentacoesRepository::inserir(const Movimentacao &movimentacao)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO movimentacoes
        (
            data,
            valor,
            descricao,
            tipo,
            conta_origem_id,
            conta_destino_id,
            categoria_id
        )
        VALUES
        (
            :data,
            :valor,
            :descricao,
            :tipo,
            (CASE WHEN :tipo_receita = 'RENDA' THEN NULL
            ELSE (SELECT id FROM contas WHERE nome = :conta_origem_nome) END),
            (CASE WHEN :tipo_despesa = 'DESPESA' THEN NULL
            ELSE (SELECT id FROM contas WHERE nome = :conta_destino_nome) END),
            (CASE WHEN :tipo_transferencia = 'TRANSFERENCIA' THEN NULL
            ELSE (SELECT id FROM categorias WHERE nome = :categoria_nome) END)
        )
    )");
    query.bindValue(":data",               movimentacao.data.toString("yyyy-MM-dd"));
    query.bindValue(":valor",              movimentacao.valor);
    query.bindValue(":descricao",          movimentacao.descricao);
    query.bindValue(":tipo",               movimentacao.getTipo());
    // Para os CASEs
    query.bindValue(":tipo_receita",        movimentacao.getTipo());
    query.bindValue(":tipo_despesa",        movimentacao.getTipo());
    query.bindValue(":tipo_transferencia",  movimentacao.getTipo());

    query.bindValue(":conta_origem_nome",  movimentacao.origem);
    query.bindValue(":conta_destino_nome", movimentacao.destino);
    query.bindValue(":categoria_nome",     movimentacao.categoria);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool MovimentacoesRepository::atualizar(const Movimentacao &movimentacao)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE movimentacoes
        SET
            data = :data,
            valor = :valor,
            descricao = :descricao,
            tipo = :tipo,
            conta_origem_id = (
                CASE WHEN :tipo_receita = 'RENDA' THEN NULL
                ELSE (SELECT id FROM contas WHERE nome = :conta_origem_nome) END
            ),
            conta_destino_id = (
                CASE WHEN :tipo_despesa = 'DESPESA' THEN NULL
                ELSE (SELECT id FROM contas WHERE nome = :conta_destino_nome) END
            ),
            categoria_id = (
                CASE WHEN :tipo_transferencia = 'TRANSFERENCIA' THEN NULL
                ELSE (SELECT id FROM categorias WHERE nome = :categoria_nome) END
            )
        WHERE id = :id
    )");

    query.bindValue(":id",                 movimentacao.id);
    query.bindValue(":data",               movimentacao.data);
    query.bindValue(":valor",              movimentacao.valor);
    query.bindValue(":descricao",          movimentacao.descricao);
    query.bindValue(":tipo",               movimentacao.getTipo());
    // Para os CASEs
    query.bindValue(":tipo_receita",        movimentacao.getTipo());
    query.bindValue(":tipo_despesa",        movimentacao.getTipo());
    query.bindValue(":tipo_transferencia",  movimentacao.getTipo());

    query.bindValue(":conta_origem_nome",  movimentacao.origem);
    query.bindValue(":conta_destino_nome", movimentacao.destino);
    query.bindValue(":categoria_nome",     movimentacao.categoria);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool MovimentacoesRepository::remover(int id)
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    DELETE FROM movimentacoes
        WHERE id = :id
    )");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

int MovimentacoesRepository::contar()
{
    QSqlQuery query(Database::instance().db());

    int total {};

    if (!query.exec(R"(
        SELECT COUNT(*) FROM movimentacoes
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
