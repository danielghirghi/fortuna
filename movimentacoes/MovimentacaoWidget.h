#ifndef MOVIMENTACAOWIDGET_H
#define MOVIMENTACAOWIDGET_H

#include <QDialog>

#include "../models/Movimentacao.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MovimentacaoWidget; }
QT_END_NAMESPACE

enum class Modo
{
    Inserir,
    Editar,
    Excluir
};

enum class TipoMovWdgt
{
    Despesa,
    Receita,
    Transferencia
};

class MovimentacaoWidget : public QDialog
{
    Q_OBJECT

public:
    explicit MovimentacaoWidget(QWidget *parent = nullptr);
    ~MovimentacaoWidget();
    void setModo(Modo modo);
    TipoMovWdgt tipo;
    void setId(int id);
    QString getTipo() const;
    void setTipo(QString tipo);

private slots:
    void confirmar();
    void inserirMovimentacao();
    void atualizarMovimentacao();
    void excluirMovimentacao();

private:
    int m_id {-1};
    Ui::MovimentacaoWidget *ui;
    Modo m_modo {Modo::Inserir};
    void carregarMovimentacao();
    Movimentacao movimentacaoDaInterface() const;
    void preencherInterface(const Movimentacao &movimentacao);
};

#endif // MOVIMENTACAOWIDGET_H
