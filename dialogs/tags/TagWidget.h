#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QDialog>

#include "../../models/Tag.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TagWidget; }
QT_END_NAMESPACE

class TagWidget : public QDialog
{
    Q_OBJECT

public:
    enum class Modo
    {
        Inserir,
        Editar,
        Excluir
    };
    explicit TagWidget(QWidget *parent = nullptr);
    ~TagWidget();
    void setModo(Modo modo);
    void setId(int id);

private slots:
    void confirmar();
    void inserirTag();
    void atualizarTag();
    void excluirTag();

private:
    int m_id = -1;
    Ui::TagWidget *ui;
    Modo m_modo = Modo::Inserir;
    void carregarTag();
    Tag tagDaInterface() const;
    void preencherInterface(const Tag &tag);
};

#endif // TAGWIDGET_H
