#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>

#include <QStandardPaths>
#include <QFile>
#include <QDir>

#include "database/Database.h"
#include "config/configmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "fortuna_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }

    if (!Database::instance().connect()) {
        QMessageBox::critical(nullptr, "Erro", "Não foi possível conectar ao banco de dados.");
        return -1;
    }

    QString banco = ConfigManager::databasePath();

    bool bancoNovo = !QFile::exists(banco);

    if (Database::instance().connect(banco))
    {
        if (bancoNovo)
            Database::instance().criarBanco();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
