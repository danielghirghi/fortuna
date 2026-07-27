#include "CategoriaWidget.h"
#include "ui_CategoriaWidget.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

CategoriaWidget::CategoriaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::CategoriaWidget)
{
        ui->setupUi(this);
        setWindowTitle("Nova Categoria");

        connect(ui->bbCategoria, &QDialogButtonBox::accepted, this, &CategoriaWidget::salvar);
        connect(ui->bbCategoria, &QDialogButtonBox::rejected, this, &CategoriaWidget::close);
}

CategoriaWidget::~CategoriaWidget(){ delete ui; }

void CategoriaWidget::setId(int id)
{
    m_id = id;
    carregarCategoria();
}

void CategoriaWidget::carregarCategoria()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( SELECT nome, tipo, grupo, ativo FROM categorias WHERE id =  :id )");
    query.bindValue(":id", m_id);
    if (!query.exec()) return;
    if (!query.next()) return;

    ui->edtNome->setText(query.value("nome").toString());
    ui->cmbTipo->setCurrentText(query.value("tipo").toString());
    ui->cmbGrupo->setCurrentText(query.value("grupo").toString());
    ui->chkAtiva->setChecked(query.value("ativo").toBool());
}

void CategoriaWidget::salvar()
{
    if (m_id == -1)
        inserirCategoria();
    else
        atualizarCategoria();
}

void CategoriaWidget::inserirCategoria()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO categorias ( nome, tipo, grupo, ativo ) VALUES ( :nome, :tipo, :grupo, :ativo )
    )");

    query.bindValue(":nome",  ui->edtNome->text());
    query.bindValue(":tipo",  ui->cmbTipo->currentText());
    query.bindValue(":grupo", ui->cmbGrupo->currentText());
    query.bindValue(":ativo", ui->chkAtiva->isChecked());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}

void CategoriaWidget::atualizarCategoria()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE categorias
        SET
            nome = :nome,
            grupo = :grupo,
            tipo = :tipo,
            ativo = :ativa
        WHERE id = :id
    )");

    query.bindValue(":id", m_id);
    query.bindValue(":nome",  ui->edtNome->text());
    query.bindValue(":grupo", ui->cmbGrupo->currentText());
    query.bindValue(":tipo",  ui->cmbTipo->currentText());
    query.bindValue(":ativa", ui->chkAtiva->isChecked());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
