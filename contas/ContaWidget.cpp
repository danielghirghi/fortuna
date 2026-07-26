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

    connect(ui->bbConta, &QDialogButtonBox::accepted, this, &ContaWidget::salvar);
    connect(ui->bbConta, &QDialogButtonBox::rejected, this, &ContaWidget::close);
}

ContaWidget::~ContaWidget(){ delete ui; }

void ContaWidget::salvar()
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
