#include "TagWidget.h"
#include "ui_TagWidget.h"

#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

#include "../database/Database.h"

TagWidget::TagWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TagWidget){
    ui->setupUi(this);
    setWindowTitle("Nova Tag");

    connect(ui->bbTag, &QDialogButtonBox::accepted, this, &TagWidget::salvar);
    connect(ui->bbTag, &QDialogButtonBox::rejected, this, &TagWidget::close);
}

TagWidget::~TagWidget(){ delete ui; }

void TagWidget::setId(int id)
{
    m_id = id;
    carregarTag();
}

void TagWidget::carregarTag()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"( SELECT nome, cor, ativo FROM tags WHERE id =  :id )");
    query.bindValue(":id", m_id);
    if (!query.exec()) return;
    if (!query.next()) return;

    ui->edtNome->setText(query.value("nome").toString());
    ui->edtCor->setText(query.value("cor").toString());
    ui->chkAtiva->setChecked(query.value("ativo").toBool());
}

void TagWidget::salvar()
{
    if (m_id == -1)
        inserirTag();
    else
        atualizarTag();
}

void TagWidget::inserirTag()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
        INSERT INTO tags ( nome, cor, ativo ) VALUES ( :nome, :cor, :ativo )
    )");

    query.bindValue(":nome",  ui->edtNome->text());
    query.bindValue(":cor",   ui->edtCor->text());
    query.bindValue(":ativo", ui->chkAtiva->isChecked());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}

void TagWidget::atualizarTag()
{
    QSqlQuery query(Database::instance().db());

    query.prepare(R"(
    UPDATE tags
        SET
            nome = :nome,
            cor = :cor,
            ativo = :ativa
        WHERE id = :id
    )");

    query.bindValue(":id", m_id);
    query.bindValue(":nome",  ui->edtNome->text());
    query.bindValue(":cor",   ui->edtCor->text());
    query.bindValue(":ativa", ui->chkAtiva->isChecked());

    if(query.exec()) { accept(); }
    else { QMessageBox::critical( this, "Erro", query.lastError().text()); }
}
