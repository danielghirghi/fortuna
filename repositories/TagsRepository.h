#ifndef TAGSREPOSITORY_H
#define TAGSREPOSITORY_H

#include "../models/Tag.h"

class TagsRepository
{
    QString m_lastError {};
public:
    QString lastError();
    QList<Tag> listar();
    Tag buscarPorId(int id);
    bool inserir(const Tag &tag);
    bool atualizar(const Tag &tag);
    bool remover(int id);
};

#endif // TAGSREPOSITORY_H
