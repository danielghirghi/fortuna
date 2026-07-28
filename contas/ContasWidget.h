#ifndef CONTASWIDGET_H
#define CONTASWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ContasWidget; }
QT_END_NAMESPACE

class ContasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContasWidget(QWidget *parent = nullptr);
    ~ContasWidget();

private slots:
    void carregarContas();
    void on_btnNova_clicked();
    void on_btnEditar_clicked();
    void on_btnExcluir_clicked();

private:
    Ui::ContasWidget *ui;
};

#endif // CONTASWIDGET_H
