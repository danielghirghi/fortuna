#include "CategoriaConfirmDialog.h"
#include "ui_CategoriaConfirmDialog.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

CategoriaConfirmDialog::CategoriaConfirmDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::CategoriaConfirmDialog)
{
    ui->setupUi(this);
    setWindowTitle("Excluir Categoria");

    connect(ui->bbConfirm, &QDialogButtonBox::accepted, this, &CategoriaConfirmDialog::Remover);
    connect(ui->bbConfirm, &QDialogButtonBox::rejected, this, &CategoriaConfirmDialog::close);
}

CategoriaConfirmDialog::~CategoriaConfirmDialog(){ delete ui; }

void CategoriaConfirmDialog::setId(int id)
{
    m_id = id;
    carregarCategoria();
}

void CategoriaConfirmDialog::carregarCategoria()
{


    QSqlQuery query(Database::instance().db());

    query.prepare("SELECT nome, grupo, tipo, ativo FROM categorias WHERE id = :id");
    query.bindValue(":id", m_id);
    if (!query.exec())
    {
        QMessageBox::critical(this, "Erro", query.lastError().text());
        return;
    }
    if (!query.next()) return;

    ui->edtNome->setText(query.value("nome").toString());
    ui->edtGrupo->setText(query.value("grupo").toString());
    ui->edtTipo->setText(query.value("tipo").toString());
    ui->edtAtiva->setText(query.value("ativo").toString());
}

void CategoriaConfirmDialog::Remover()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( DELETE FROM categorias WHERE id = :id )");
    query.bindValue(":id", m_id);

    if(!query.exec()) { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
