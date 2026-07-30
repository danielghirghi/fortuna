#include "Movimentacao.h"

QString Movimentacao::getTipo() const
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

void Movimentacao::setTipo(QString tipo)
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
