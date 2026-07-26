#ifndef CATEGORIAWIDGET_H
#define CATEGORIAWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriaWidget; }
QT_END_NAMESPACE

class CategoriaWidget : public QDialog {
    Q_OBJECT

public:
    explicit CategoriaWidget(QWidget *parent = nullptr);
    ~CategoriaWidget();

private:
    Ui::CategoriaWidget *ui;
};

#endif // CATEGORIAWIDGET_H
