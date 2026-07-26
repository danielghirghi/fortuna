#include "TagsWidget.h"
#include "ui_TagsWidget.h"
#include "TagWidget.h"

#include <QSqlQuery>
#include "../database/Database.h"

#include <QMessageBox>
#include <QSqlError>
#include <QTableWidgetItem>

TagsWidget::TagsWidget(QWidget *parent) : QWidget(parent)
    , ui(new Ui::TagsWidget)
{
    ui->setupUi(this);
    setWindowTitle("Tags");

    carregarTags();
}

TagsWidget::~TagsWidget() { delete ui; }

void TagsWidget::on_btnNova_clicked(){
    auto *janela = new TagWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

void TagsWidget::carregarTags()
{
    ui->tblTags->setRowCount(0);

    QSqlQuery query(Database::instance().db());
    if (!query.exec("SELECT nome, cor, ativo FROM tags ORDER BY nome")) {
        QMessageBox::warning(this, "Erro", "Falha ao carregar Tags: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tblTags->insertRow(row);
        ui->tblTags->setItem(row, 0, new QTableWidgetItem(query.value("nome").toString()));
        ui->tblTags->setItem(row, 1, new QTableWidgetItem(query.value("cor").toString()));
        ui->tblTags->setItem(row, 2, new QTableWidgetItem(query.value("ativo").toString()));
        row++;
    }
}