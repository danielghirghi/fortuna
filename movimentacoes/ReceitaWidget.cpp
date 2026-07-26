#include "ReceitaWidget.h"
#include "ui_ReceitaWidget.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

ReceitaWidget::ReceitaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ReceitaWidget)
{
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Receita");

    QSqlQuery query(Database::instance().db());

    query.exec("SELECT id, nome FROM contas WHERE ativo = 1 ORDER BY nome");
    while (query.next())
    {
        ui->cmbDestino->addItem(
            query.value("nome").toString(),
            query.value("id"));
    }

    query.exec("SELECT id, nome FROM categorias WHERE ativo = 1 AND tipo = 'RENDA' ORDER BY nome");
    while (query.next())
    {
        ui->cmbCategoria->addItem(
            query.value("nome").toString(),
            query.value("id"));
    }

    connect(ui->bbReceita, &QDialogButtonBox::accepted, this, &ReceitaWidget::salvar);
    connect(ui->bbReceita, &QDialogButtonBox::rejected, this, &ReceitaWidget::close);
}

ReceitaWidget::~ReceitaWidget(){ delete ui; }

void ReceitaWidget::salvar()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO movimentacoes ( data, valor, descricao, tipo, conta_destino_id, categoria_id )
        VALUES ( :data, :valor, :descricao, :tipo, :conta_destino_id, :categoria_id )
    )");

    query.bindValue(":tipo", "RENDA");
    query.bindValue(":data",            ui->dateReceita->date());
    query.bindValue(":valor",           ui->spnValor->text());
    query.bindValue(":descricao",       ui->edtDescricao->text());
    query.bindValue(":conta_destino_id", ui->cmbDestino->currentData().toInt());
    query.bindValue(":categoria_id",    ui->cmbCategoria->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}