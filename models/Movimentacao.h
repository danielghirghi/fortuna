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

    QString getTipo() const;
    void setTipo(QString tipo);
};

#endif // MOVIMENTACAO_H
