#ifndef TAG_H
#define TAG_H

#include <QString>

class Tag
{
public:
    int id {-1};
    QString nome {};
    QString cor {};
    bool ativo {true};
};

#endif // TAG_H
