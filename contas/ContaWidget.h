#ifndef CONTAWIDGET_H
#define CONTAWIDGET_H

#include <QDialog>

#include "../models/Conta.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ContaWidget; }
QT_END_NAMESPACE

class ContaWidget : public QDialog
{
    Q_OBJECT

public:
    enum class Modo
    {
        Inserir,
        Editar,
        Excluir
    };
    explicit ContaWidget(QWidget *parent = nullptr);
    ~ContaWidget();
    void setModo(Modo modo);
    void setId(int id);

private slots:
    void confirmar();
    void inserirConta();
    void atualizarConta();
    void excluirConta();

private:
    int m_id {-1};
    Ui::ContaWidget *ui;
    Modo m_modo {Modo::Inserir};
    void carregarConta();
    Conta contaDaInterface() const;
    void preencherInterface(const Conta &conta);
};

#endif // CONTAWIDGET_H
