#ifndef FORMAT_H
#define FORMAT_H

#include <QString>
#include <qdatetime.h>

class Format
{
public:
    static QString data(const QDate &data)
    {
        return QLocale().toString(data, QLocale::ShortFormat);
    }
};

#endif // FORMAT_H
