#ifndef CATEGORIAWIDGET_H
#define CATEGORIAWIDGET_H

#include <QDialog>

#include "../../models/Categoria.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriaWidget; }
QT_END_NAMESPACE

class CategoriaWidget : public QDialog
{
    Q_OBJECT

public:
    enum class Modo
    {
        Inserir,
        Editar,
        Excluir
    };
    explicit CategoriaWidget(QWidget *parent = nullptr);
    ~CategoriaWidget();
    void setModo(Modo modo);
    void setId(int id);

private slots:
    void confirmar();
    void inserirCategoria();
    void atualizarCategoria();
    void excluirCategoria();

private:
    int m_id = -1;
    Ui::CategoriaWidget *ui;
    Modo m_modo = Modo::Inserir;
    void carregarCategoria();
    Categoria categoriaDaInterface() const;
    void preencherInterface(const Categoria &categoria);
};

#endif // CATEGORIAWIDGET_H
