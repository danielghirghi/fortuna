#ifndef CATEGORIASWIDGET_H
#define CATEGORIASWIDGET_H

#include "../BaseWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriasWidget; }
QT_END_NAMESPACE

class CategoriasWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit CategoriasWidget(QWidget *parent = nullptr);
    ~CategoriasWidget();
    void refresh();

private slots:
    void carregarCategorias();
    void on_btnNova_clicked();
    void on_btnEditar_clicked();
    void on_btnExcluir_clicked();

private:
    Ui::CategoriasWidget *ui;
};

#endif // CATEGORIASWIDGET_H
