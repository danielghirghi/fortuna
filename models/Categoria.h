#ifndef CATEGORIA_H
#define CATEGORIA_H

#include <QString>

class Categoria
{
public:
    int id {-1};
    QString nome {};
    QString tipo {};
    QString grupo {};
    bool ativo {true};
};

#endif // CATEGORIA_H
