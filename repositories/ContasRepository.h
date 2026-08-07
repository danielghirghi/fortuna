#ifndef CONTASREPOSITORY_H
#define CONTASREPOSITORY_H

#include "../models/Conta.h"

class ContasRepository
{
    QString m_lastError {};
public:
    QString lastError();
    QList<Conta> listar();
    Conta buscarPorId(int id);
    bool inserir(const Conta &conta);
    bool atualizar(const Conta &conta);
    bool remover(int id);
    int contar();
    QList <Conta> pesquisar(QString busca);
};

#endif
