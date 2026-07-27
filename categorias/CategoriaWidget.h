#ifndef CATEGORIAWIDGET_H
#define CATEGORIAWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriaWidget; }
QT_END_NAMESPACE

class CategoriaWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CategoriaWidget(QWidget *parent = nullptr);
    ~CategoriaWidget();
    void setId(int id);

private slots:
    void salvar();
    void inserirCategoria();
    void atualizarCategoria();

private:
    int m_id = -1;
    void carregarCategoria();
    Ui::CategoriaWidget *ui;
};

#endif // CATEGORIAWIDGET_H
