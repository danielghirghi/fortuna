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

void CategoriaWidget::salvar()
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