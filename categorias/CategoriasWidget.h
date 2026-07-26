#ifndef CATEGORIASWIDGET_H
#define CATEGORIASWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriasWidget; }
QT_END_NAMESPACE

class CategoriasWidget : public QWidget {
    Q_OBJECT

public:
    explicit CategoriasWidget(QWidget *parent = nullptr);
    ~CategoriasWidget();

private slots:
    void on_btnNova_clicked();

private:
    Ui::CategoriasWidget *ui;
};

#endif // CATEGORIASWIDGET_H
