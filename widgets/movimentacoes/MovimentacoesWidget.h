#ifndef MOVIMENTACOESWIDGET_H
#define MOVIMENTACOESWIDGET_H

#include "../BaseWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MovimentacoesWidget; }
QT_END_NAMESPACE

class MovimentacoesWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit MovimentacoesWidget(QWidget *parent = nullptr);
    ~MovimentacoesWidget();
    void refresh();

private slots:
    void carregarMovimentacoes();
    void on_btnNova_clicked();
    void on_btnEditar_clicked();
    void on_btnExcluir_clicked();

private:
    Ui::MovimentacoesWidget *ui;
};

#endif // MOVIMENTACOESWIDGET_H
