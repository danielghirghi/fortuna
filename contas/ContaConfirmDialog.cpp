#include "ContaConfirmDialog.h"
#include "ui_ContaConfirmDialog.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

ContaConfirmDialog::ContaConfirmDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ContaConfirmDialog)
{
    ui->setupUi(this);
    setWindowTitle("Excluir Conta");

    connect(ui->bbConfirm, &QDialogButtonBox::accepted, this, &ContaConfirmDialog::Remover);
    connect(ui->bbConfirm, &QDialogButtonBox::rejected, this, &ContaConfirmDialog::close);
}

ContaConfirmDialog::~ContaConfirmDialog(){ delete ui; }

void ContaConfirmDialog::setId(int id)
{
    m_id = id;
    carregarConta();
}

void ContaConfirmDialog::carregarConta()
{


    QSqlQuery query(Database::instance().db());

    query.prepare("SELECT nome, banco, tipo, saldo_inicial, ativo FROM contas WHERE id = :id");
    query.bindValue(":id", m_id);
    if (!query.exec())
    {
        QMessageBox::critical(this, "Erro", query.lastError().text());
        return;
    }
    if (!query.next()) return;

    ui->edtNome->setText(query.value("nome").toString());
    ui->edtBanco->setText(query.value("banco").toString());
    ui->edtTipo->setText(query.value("tipo").toString());
    ui->edtSaldo->setText(query.value("saldo_inicial").toString());
    ui->edtAtiva->setText(query.value("ativo").toString());
}

void ContaConfirmDialog::Remover()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( DELETE FROM contas WHERE id = :id )");
    query.bindValue(":id", m_id);

    if(!query.exec()) { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
