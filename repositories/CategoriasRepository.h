#ifndef CATEGORIASREPOSITORY_H
#define CATEGORIASREPOSITORY_H

#include "../models/Categoria.h"

class CategoriasRepository
{
    QString m_lastError {};
public:
    QString lastError();
    QList<Categoria> listar();
    Categoria buscarPorId(int id);
    bool inserir(const Categoria &categoria);
    bool atualizar(const Categoria &categoria);
    bool remover(int id);
    int contar();
};


#endif // CATEGORIASREPOSITORY_H
