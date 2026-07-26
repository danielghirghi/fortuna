#ifndef CONTAWIDGET_H
#define CONTAWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ContaWidget; }
QT_END_NAMESPACE

class ContaWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ContaWidget(QWidget *parent = nullptr);
    ~ContaWidget();

private slots:
    void salvar();

private:
    Ui::ContaWidget *ui;
};

#endif // CONTAWIDGET_H
