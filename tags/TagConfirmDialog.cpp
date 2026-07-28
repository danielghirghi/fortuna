#include "TagConfirmDialog.h"
#include "ui_TagConfirmDialog.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

TagConfirmDialog::TagConfirmDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TagConfirmDialog)
{
    ui->setupUi(this);
    setWindowTitle("Excluir Tag");

    connect(ui->bbConfirm, &QDialogButtonBox::accepted, this, &TagConfirmDialog::Remover);
    connect(ui->bbConfirm, &QDialogButtonBox::rejected, this, &TagConfirmDialog::close);
}

TagConfirmDialog::~TagConfirmDialog(){ delete ui; }

void TagConfirmDialog::setId(int id)
{
    m_id = id;
    carregarTag();
}

void TagConfirmDialog::carregarTag()
{


    QSqlQuery query(Database::instance().db());

    query.prepare("SELECT nome, cor, ativo FROM tags WHERE id = :id");
    query.bindValue(":id", m_id);
    if (!query.exec())
    {
        QMessageBox::critical(this, "Erro", query.lastError().text());
        return;
    }
    if (!query.next()) return;

    ui->edtNome->setText(query.value("nome").toString());
    ui->edtCor->setText(query.value("cor").toString());
    ui->edtAtiva->setText(query.value("ativo").toString());
}

void TagConfirmDialog::Remover()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( DELETE FROM tags WHERE id = :id )");
    query.bindValue(":id", m_id);

    if(!query.exec()) { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
