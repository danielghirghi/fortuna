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

    ui->spnValor->setDecimals(2);
    ui->spnValor->setMinimum(-1000000000.0);
    ui->spnValor->setMaximum(1000000000.0);

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

void ReceitaWidget::setId(int id)
{
    m_id = id;
    carregarReceita();
}

void ReceitaWidget::carregarReceita()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( SELECT data, valor, descricao, conta_destino_id, categoria_id FROM movimentacoes WHERE id =  :id )");
    query.bindValue(":id", m_id);
    if (!query.exec()) return;
    if (!query.next()) return;

    ui->dateReceita->setDate(query.value("data").toDate());
    ui->spnValor->setValue(query.value("valor").toDouble());
    ui->edtDescricao->setText(query.value("descricao").toString());
    int contaId = query.value("conta_destino_id").toInt();
    int indiceDestino = ui->cmbDestino->findData(contaId);
    if (indiceDestino >= 0)
        ui->cmbDestino->setCurrentIndex(indiceDestino);
    int categoriaId = query.value("categoria_id").toInt();
    int indiceCategoria = ui->cmbCategoria->findData(categoriaId);
    if (indiceCategoria >= 0)
        ui->cmbCategoria->setCurrentIndex(indiceCategoria);
}


void ReceitaWidget::salvar()
{
    if (m_id == -1)
        inserirReceita();
    else
        atualizarReceita();
}

void ReceitaWidget::inserirReceita()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO movimentacoes ( data, valor, descricao, tipo, conta_destino_id, categoria_id )
        VALUES ( :data, :valor, :descricao, :tipo, :conta_destino_id, :categoria_id )
    )");

    query.bindValue(":tipo", "RENDA");
    query.bindValue(":data",             ui->dateReceita->date());
    query.bindValue(":valor",            ui->spnValor->value());
    query.bindValue(":descricao",        ui->edtDescricao->text());
    query.bindValue(":conta_destino_id", ui->cmbDestino->currentData().toInt());
    query.bindValue(":categoria_id",     ui->cmbCategoria->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}

void ReceitaWidget::atualizarReceita()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE movimentacoes
        SET
            data = :data,
            valor = :valor,
            descricao = :descricao,
            conta_destino_id = :conta_destino_id,
            categoria_id = :categoria_id
        WHERE id = :id
    )");

    query.bindValue(":id", m_id);
    query.bindValue(":data",             ui->dateReceita->date());
    query.bindValue(":valor",            ui->spnValor->value());
    query.bindValue(":descricao",        ui->edtDescricao->text());
    query.bindValue(":conta_destino_id", ui->cmbDestino->currentData().toInt());
    query.bindValue(":categoria_id",     ui->cmbCategoria->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}

