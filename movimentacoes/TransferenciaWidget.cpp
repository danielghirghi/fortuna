#include "TransferenciaWidget.h"
#include "ui_TransferenciaWidget.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

TransferenciaWidget::TransferenciaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TransferenciaWidget)
{
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Transferência");

    QSqlQuery query(Database::instance().db());

    query.exec("SELECT id, nome FROM contas WHERE ativo = 1 ORDER BY nome");
    while (query.next())
    {
        ui->cmbOrigem->addItem(
            query.value("nome").toString(),
            query.value("id"));
    }

    query.exec("SELECT id, nome FROM contas WHERE ativo = 1 ORDER BY nome");
    while (query.next())
    {
        ui->cmbDestino->addItem(
            query.value("nome").toString(),
            query.value("id"));
    }

    connect(ui->bbTransferencia, &QDialogButtonBox::accepted, this, &TransferenciaWidget::salvar);
    connect(ui->bbTransferencia, &QDialogButtonBox::rejected, this, &TransferenciaWidget::close);
}

TransferenciaWidget::~TransferenciaWidget(){ delete ui; }

void TransferenciaWidget::salvar()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO movimentacoes ( data, valor, descricao, tipo, conta_origem_id, conta_destino_id )
        VALUES ( :data, :valor, :descricao, :tipo, :conta_origem_id, :conta_destino_id )
    )");

    query.bindValue(":tipo", "TRANSFERENCIA");
    query.bindValue(":data",             ui->dateTransferencia->date());
    query.bindValue(":valor",            ui->spnValor->text());
    query.bindValue(":descricao",        ui->edtDescricao->text());
    query.bindValue(":conta_origem_id",  ui->cmbOrigem->currentData().toInt());
    query.bindValue(":conta_destino_id", ui->cmbDestino->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
