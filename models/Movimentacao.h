#ifndef MOVIMENTACAO_H
#define MOVIMENTACAO_H

#include <QString>
#include <qdatetime.h>

enum class TipoMovimentacao
{
    Despesa,
    Receita,
    Transferencia
};

class Movimentacao
{
public:
    int id {-1};
    QDate data {};
    double valor { 0.0 };
    QString descricao {};
    TipoMovimentacao tipo {};
    QString origem {};
    QString destino {};
    QString categoria {};

    QString getTipo() const
    {
        switch (Movimentacao::tipo)
        {
        case TipoMovimentacao::Receita:
            return "RENDA";
        case TipoMovimentacao::Despesa:
            return "DESPESA";
        case TipoMovimentacao::Transferencia:
            return "TRANSFERENCIA";
        }
        return "ERRO";
    }
    void setTipo(QString tipo)
    {
        if (tipo == "RENDA" || tipo == "RECEITA")
        {
            Movimentacao::tipo = TipoMovimentacao::Receita;
            return;
        }
        if (tipo =="DESPESA")
        {
            Movimentacao::tipo = TipoMovimentacao::Despesa;
            return;
        }
        if (tipo =="TRANSFERENCIA")
        {
            Movimentacao::tipo = TipoMovimentacao::Transferencia;
            return;
        }
    }
};

#endif // MOVIMENTACAO_H
