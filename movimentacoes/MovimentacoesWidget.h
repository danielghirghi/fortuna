#ifndef MOVIMENTACOESWIDGET_H
#define MOVIMENTACOESWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MovimentacoesWidget; }
QT_END_NAMESPACE

class MovimentacoesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovimentacoesWidget(QWidget *parent = nullptr);
    ~MovimentacoesWidget();

private slots:
    void carregarMovimentacoes();
    void abrirReceita();
    void abrirDespesa();
    void abrirTransferencia();
    void on_btnEditar_clicked();

private:
    Ui::MovimentacoesWidget *ui;
};

#endif // MOVIMENTACOESWIDGET_H
