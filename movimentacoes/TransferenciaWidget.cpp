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

void TransferenciaWidget::setId(int id)
{
    m_id = id;
    carregarTransferencia();
}


void TransferenciaWidget::carregarTransferencia()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( SELECT data, valor, descricao, conta_origem_id, conta_destino_id FROM movimentacoes WHERE id =  :id )");
    query.bindValue(":id", m_id);
    if (!query.exec()) return;
    if (!query.next()) return;

    ui->dateTransferencia->setDate(query.value("data").toDate());
    ui->spnValor->setValue(query.value("valor").toDouble());
    ui->edtDescricao->setText(query.value("descricao").toString());
    int contaId = query.value("conta_origem_id").toInt();
    int indiceOrigem = ui->cmbOrigem->findData(contaId);
    if (indiceOrigem >= 0)
        ui->cmbOrigem->setCurrentIndex(indiceOrigem);
    int categoriaId = query.value("categoria_id").toInt();
    int indiceDestino = ui->cmbDestino->findData(categoriaId);
    if (indiceDestino >= 0)
        ui->cmbDestino->setCurrentIndex(indiceDestino);
}


void TransferenciaWidget::salvar()
{
    if (m_id == -1)
        inserirTransferencia();
    else
        atualizarTransferencia();
}

void TransferenciaWidget::inserirTransferencia()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO movimentacoes ( data, valor, descricao, tipo, conta_origem_id, conta_destino_id )
        VALUES ( :data, :valor, :descricao, :tipo, :conta_origem_id, :conta_destino_id )
    )");

    query.bindValue(":tipo", "TRANSFERENCIA");
    query.bindValue(":data", ui->dateTransferencia->date());
    query.bindValue(":valor", ui->spnValor->value());
    query.bindValue(":descricao", ui->edtDescricao->text());
    query.bindValue(":conta_origem_id", ui->cmbOrigem->currentData().toInt());
    query.bindValue(":conta_destino_id", ui->cmbDestino->currentData().toInt());

    if (query.exec()) {
        accept();
    } else {
        QMessageBox::critical(this, "Erro", query.lastError().text());
    }
}

void TransferenciaWidget::atualizarTransferencia()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE movimentacoes
        SET
            data = :data,
            valor = :valor,
            descricao = :descricao,
            conta_origem_id = :conta_origem_id,
            conta_destino_id = :conta_destino_id
        WHERE id = :id
    )");

    query.bindValue(":id", m_id);
    query.bindValue(":data",             ui->dateTransferencia->date());
    query.bindValue(":valor",            ui->spnValor->value());
    query.bindValue(":descricao",        ui->edtDescricao->text());
    query.bindValue(":conta_origem_id",  ui->cmbOrigem->currentData().toInt());
    query.bindValue(":conta_destino_id", ui->cmbDestino->currentData().toInt());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
