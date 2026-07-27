#ifndef CATEGORIASWIDGET_H
#define CATEGORIASWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriasWidget; }
QT_END_NAMESPACE

class CategoriasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriasWidget(QWidget *parent = nullptr);
    ~CategoriasWidget();

private slots:
    void carregarCategorias();
    void on_btnNova_clicked();
    void on_btnEditar_clicked();

private:
    Ui::CategoriasWidget *ui;
};

#endif // CATEGORIASWIDGET_H
