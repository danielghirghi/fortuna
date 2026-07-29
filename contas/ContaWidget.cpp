#include "ContaWidget.h"
#include "ui_ContaWidget.h"

#include "../repositories/ContasRepository.h"

#include <qpushbutton.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

ContaWidget::ContaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ContaWidget)
{
    ui->setupUi(this);

    ui->spnSaldoInicial->setDecimals(2);
    ui->spnSaldoInicial->setMinimum(-1000000000.0);
    ui->spnSaldoInicial->setMaximum(1000000000.0);
    ui->spnSaldoInicial->setSingleStep(100.0);

    connect(ui->bbConta, &QDialogButtonBox::accepted, this, &ContaWidget::confirmar);
    connect(ui->bbConta, &QDialogButtonBox::rejected, this, &ContaWidget::reject);
}

ContaWidget::~ContaWidget(){ delete ui; }

Conta ContaWidget::contaDaInterface() const
{
    Conta conta;

    conta.nome = ui->edtNome->text();
    conta.banco = ui->edtBanco->text();
    conta.tipo = ui->cmbTipo->currentText();
    conta.saldoInicial = ui->spnSaldoInicial->value();
    conta.ativo = ui->chkAtiva->isChecked();

    return conta;
}

void ContaWidget::preencherInterface(const Conta &conta)
{
    ui->edtNome->setText(conta.nome);
    ui->edtBanco->setText(conta.banco);
    ui->cmbTipo->setCurrentText(conta.tipo);
    ui->spnSaldoInicial->setValue(conta.saldoInicial);
    ui->chkAtiva->setChecked(conta.ativo);
}

void ContaWidget::setModo(Modo modo)
{
    m_modo = modo;
    QPushButton *botao = ui->bbConta->button(QDialogButtonBox::Save);

    switch (modo)
    {
    case Modo::Inserir:
        setWindowTitle("Nova Conta");
        botao->setText("Salvar");
        break;

    case Modo::Editar:
        setWindowTitle("Editar Conta");
        botao->setText("Atualizar");
        break;

    case Modo::Excluir:
        setWindowTitle("Excluir Conta");
        ui->edtNome->setReadOnly(true);
        ui->edtBanco->setReadOnly(true);
        ui->cmbTipo->setEnabled(false);
        ui->spnSaldoInicial->setEnabled(false);
        ui->chkAtiva->setEnabled(false);
        botao->setText("Excluir");
        break;
    }
}

void ContaWidget::confirmar()
{
    switch (m_modo)
    {
    case Modo::Inserir:
        inserirConta();
        break;

    case Modo::Editar:
        atualizarConta();
        break;

    case Modo::Excluir:
        excluirConta();
        break;
    }
}

void ContaWidget::setId(int id)
{
    m_id = id;
    carregarConta();
}

void ContaWidget::carregarConta()
{
    ContasRepository repository;
    Conta conta = repository.buscarPorId(m_id);

    if (conta.id == -1)
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    preencherInterface(conta);
}

void ContaWidget::inserirConta()
{
    ContasRepository repository;
    Conta conta = contaDaInterface();

    if (!repository.inserir(conta))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void ContaWidget::atualizarConta()
{
    ContasRepository repository;
    Conta conta = contaDaInterface();
    conta.id = m_id;

    if (!repository.atualizar(conta))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void ContaWidget::excluirConta()
{
    ContasRepository repository;

    if (!repository.remover(m_id))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

