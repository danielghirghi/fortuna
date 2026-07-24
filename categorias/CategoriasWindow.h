#ifndef CATEGORIASWINDOW_H
#define CATEGORIASWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriasWindow; }
QT_END_NAMESPACE

class CategoriasWindow : public QWidget {
    Q_OBJECT

public:
    explicit CategoriasWindow(QWidget *parent = nullptr);
    ~CategoriasWindow();

private slots:
    void on_btnNova_clicked();

private:
    Ui::CategoriasWindow *ui;
};

#endif // CATEGORIASWINDOW_H
