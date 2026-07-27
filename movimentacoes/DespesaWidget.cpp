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

    ui->spnValor->setDecimals(2);
    ui->spnValor->setMinimum(-1000000000.0);
    ui->spnValor->setMaximum(1000000000.0);

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

void DespesaWidget::setId(int id)
{
    m_id = id;
    carregarDespesa();
}

void DespesaWidget::carregarDespesa()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( SELECT data, valor, descricao, conta_origem_id, categoria_id FROM movimentacoes WHERE id =  :id )");
    query.bindValue(":id", m_id);
    if (!query.exec()) return;
    if (!query.next()) return;

    ui->dateDespesa->setDate(query.value("data").toDate());
    ui->spnValor->setValue(query.value("valor").toDouble());
    ui->edtDescricao->setText(query.value("descricao").toString());
    int contaId = query.value("conta_origem_id").toInt();
    int indiceOrigem = ui->cmbOrigem->findData(contaId);
    if (indiceOrigem >= 0)
        ui->cmbOrigem->setCurrentIndex(indiceOrigem);
    int categoriaId = query.value("categoria_id").toInt();
    int indiceCategoria = ui->cmbCategoria->findData(categoriaId);
    if (indiceCategoria >= 0)
        ui->cmbCategoria->setCurrentIndex(indiceCategoria);
}

void DespesaWidget::salvar()
{
    if (m_id == -1)
        inserirDespesa();
    else
        atualizarDespesa();
}

void DespesaWidget::inserirDespesa()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO movimentacoes ( data, valor, descricao, tipo, conta_origem_id, categoria_id )
        VALUES ( :data, :valor, :descricao, :tipo, :conta_origem_id, :categoria_id )
    )");

    query.bindValue(":tipo", "DESPESA");
    query.bindValue(":data",            ui->dateDespesa->date());
    query.bindValue(":valor",           ui->spnValor->value());
    query.bindValue(":descricao",       ui->edtDescricao->text());
    query.bindValue(":conta_origem_id", ui->cmbOrigem->currentData().toInt());
    query.bindValue(":categoria_id",    ui->cmbCategoria->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}

void DespesaWidget::atualizarDespesa()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE movimentacoes
        SET
            data = :data,
            valor = :valor,
            descricao = :descricao,
            conta_origem_id = :conta_origem_id,
            categoria_id = :categoria_id
        WHERE id = :id
    )");

    query.bindValue(":id", m_id);
    query.bindValue(":data",            ui->dateDespesa->date());
    query.bindValue(":valor",           ui->spnValor->value());
    query.bindValue(":descricao",       ui->edtDescricao->text());
    query.bindValue(":conta_origem_id", ui->cmbOrigem->currentData().toInt());
    query.bindValue(":categoria_id",    ui->cmbCategoria->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
