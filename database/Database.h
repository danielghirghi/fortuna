#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>

// Não cria a database nem as tabelas, por enquanto ele assume que o banco e as tabelas já existem
class Database
{
public:
    static Database& instance();

    bool connect();
    void disconnect();
    bool isOpen() const;

    QSqlDatabase db() const;

private:
    Database() = default;
    ~Database() = default;

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    QSqlDatabase m_db;
    static const QString CONNECTION_NAME;

    bool inicializarBanco();
    int obterVersao();
    void definirVersao(int versao);
    bool criarBanco();
    //void atualizarBanco();
    bool executarArquivo(QString path);
    QStringList separarComandosSQL(const QString &sql);
};
#endif // DATABASE_H
