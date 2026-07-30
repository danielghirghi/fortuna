#ifndef CONTA_H
#define CONTA_H

#include <QString>

class Conta
{
public:
    int id {-1};
    QString nome {};
    QString banco {};
    QString tipo {};
    double saldoInicial {0.0};
    bool ativo {true};
};

#endif // CONTA_H
