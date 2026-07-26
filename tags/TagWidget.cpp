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

void TagWidget::salvar()
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
