#include "ContaWidget.h"
#include "ui_ContaWidget.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

ContaWidget::ContaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ContaWidget)
{
    ui->setupUi(this);
    setWindowTitle("Nova Conta");

    ui->spnSaldoInicial->setDecimals(2);
    ui->spnSaldoInicial->setMinimum(-1000000000.0);
    ui->spnSaldoInicial->setMaximum(1000000000.0);
    ui->spnSaldoInicial->setSingleStep(100.0);

    connect(ui->bbConta, &QDialogButtonBox::accepted, this, &ContaWidget::salvar);
    connect(ui->bbConta, &QDialogButtonBox::rejected, this, &ContaWidget::close);
}

ContaWidget::~ContaWidget(){ delete ui; }

void ContaWidget::setId(int id)
{
    m_id = id;
    carregarConta();
}

void ContaWidget::carregarConta()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( SELECT nome, tipo, banco, saldo_inicial, ativo FROM contas WHERE id =  :id )");
    query.bindValue(":id", m_id);
    if (!query.exec()) return;
    if (!query.next()) return;

    ui->edtNome->setText(query.value("nome").toString());
    ui->cmbTipo->setCurrentText(query.value("tipo").toString());
    ui->edtBanco->setText(query.value("banco").toString());
    ui->spnSaldoInicial->setValue(query.value("saldo_inicial").toDouble());
    ui->chkAtiva->setChecked(query.value("ativo").toBool());
}

void ContaWidget::salvar()
{
    if (m_id == -1)
        inserirConta();
    else
        atualizarConta();
}

void ContaWidget::inserirConta()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO contas ( nome, banco, tipo, saldo_inicial, ativo ) VALUES ( :nome, :banco, :tipo, :saldo_inicial, :ativa )
    )");

    query.bindValue(":nome",          ui->edtNome->text());
    query.bindValue(":banco",         ui->edtBanco->text());
    query.bindValue(":tipo",          ui->cmbTipo->currentText());
    query.bindValue(":saldo_inicial", ui->spnSaldoInicial->value());
    query.bindValue(":ativa",         ui->chkAtiva->isChecked());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}

void ContaWidget::atualizarConta()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE contas
        SET
            nome = :nome,
            banco = :banco,
            tipo = :tipo,
            saldo_inicial = :saldo_inicial,
            ativo = :ativa
        WHERE id = :id
    )");

    query.bindValue(":id", m_id);
    query.bindValue(":nome",          ui->edtNome->text());
    query.bindValue(":banco",         ui->edtBanco->text());
    query.bindValue(":tipo",          ui->cmbTipo->currentText());
    query.bindValue(":saldo_inicial", ui->spnSaldoInicial->value());
    query.bindValue(":ativa",         ui->chkAtiva->isChecked());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
