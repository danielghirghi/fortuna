#include "DespesaWidget.h"
#include "ui_DespesaWidget.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

DespesaWidget::DespesaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::DespesaWidget)
{
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Despesa");

    QSqlQuery query(Database::instance().db());

    query.exec("SELECT id, nome FROM contas WHERE ativo = 1 ORDER BY nome");
    while (query.next())
    {
        ui->cmbOrigem->addItem(
            query.value("nome").toString(),
            query.value("id"));
    }

    query.exec("SELECT id, nome FROM categorias WHERE ativo = 1 AND tipo = 'DESPESA' ORDER BY nome");
    while (query.next())
    {
        ui->cmbCategoria->addItem(
            query.value("nome").toString(),
            query.value("id"));
    }

    connect(ui->bbDespesa, &QDialogButtonBox::accepted, this, &DespesaWidget::salvar);
    connect(ui->bbDespesa, &QDialogButtonBox::rejected, this, &DespesaWidget::close);
}

DespesaWidget::~DespesaWidget(){ delete ui; }

void DespesaWidget::salvar()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO movimentacoes ( data, valor, descricao, tipo, conta_origem_id, categoria_id )
        VALUES ( :data, :valor, :descricao, :tipo, :conta_origem_id, :categoria_id )
    )");

    query.bindValue(":tipo", "DESPESA");
    query.bindValue(":data",            ui->dateDespesa->date());
    query.bindValue(":valor",           ui->spnValor->text());
    query.bindValue(":descricao",       ui->edtDescricao->text());
    query.bindValue(":conta_origem_id", ui->cmbOrigem->currentData().toInt());
    query.bindValue(":categoria_id",    ui->cmbCategoria->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}