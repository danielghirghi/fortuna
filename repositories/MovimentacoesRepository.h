#ifndef MOVIMENTACOESREPOSITORY_H
#define MOVIMENTACOESREPOSITORY_H

#include "../models/Movimentacao.h"

class MovimentacoesRepository
{
    QString m_lastError {};
public:
    QString lastError();
    QList<Movimentacao> listar();
    Movimentacao buscarPorId(int id);
    bool inserir(const Movimentacao &conta);
    bool atualizar(const Movimentacao &conta);
    bool remover(int id);
    int contar();
};

#endif // MOVIMENTACOESREPOSITORY_H
