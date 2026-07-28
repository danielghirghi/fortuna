#include "MovimentacaoConfirmDialog.h"
#include "ui_MovimentacaoConfirmDialog.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

MovimentacaoConfirmDialog::MovimentacaoConfirmDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::MovimentacaoConfirmDialog)
{
    ui->setupUi(this);
    setWindowTitle("Excluir Movimentacao");

    connect(ui->bbConfirm, &QDialogButtonBox::accepted, this, &MovimentacaoConfirmDialog::Remover);
    connect(ui->bbConfirm, &QDialogButtonBox::rejected, this, &MovimentacaoConfirmDialog::close);
}

MovimentacaoConfirmDialog::~MovimentacaoConfirmDialog(){ delete ui; }

void MovimentacaoConfirmDialog::setId(int id)
{
    m_id = id;
    carregarMovimentacao();
}

void MovimentacaoConfirmDialog::carregarMovimentacao()
{


    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        SELECT
            m.id,
            m.data,
            m.descricao,
            co.nome AS conta_origem,
            cd.nome AS conta_destino,
            cat.nome AS categoria,
            m.valor,
            m.tipo
        FROM movimentacoes m
        LEFT JOIN contas co
            ON co.id = m.conta_origem_id
        LEFT JOIN contas cd
            ON cd.id = m.conta_destino_id
        LEFT JOIN categorias cat
            ON cat.id = m.categoria_id
        WHERE m.id = :id
    )");
    query.bindValue(":id", m_id);
    if (!query.exec())
    {
        QMessageBox::critical(this, "Erro", query.lastError().text());
        return;
    }
    if (!query.next()) return;

    ui->edtData->setText(query.value("data").toString());
    ui->edtValor->setText(query.value("valor").toString());
    ui->edtDescricao->setText(query.value("descricao").toString());
    ui->edtTipo->setText(query.value("tipo").toString());
    ui->edtOrigem->setText(query.value("conta_origem").toString());
    ui->edtDestino->setText(query.value("conta_destino").toString());
    ui->edtCategoria->setText(query.value("categoria").toString());
}

void MovimentacaoConfirmDialog::Remover()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( DELETE FROM movimentacoes WHERE id = :id )");
    query.bindValue(":id", m_id);

    if(!query.exec()) { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
