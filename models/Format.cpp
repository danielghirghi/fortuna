#include "Format.h"
#include <qlocale.h>

QString Format::data(const QDate &data)
{
    return QLocale().toString(data, QLocale::ShortFormat);
}
