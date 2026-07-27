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

    ui->tblTags->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblTags->setSelectionMode(QAbstractItemView::SingleSelection);
}

TagsWidget::~TagsWidget() { delete ui; }

void TagsWidget::carregarTags()
{
    ui->tblTags->setRowCount(0);

    QSqlQuery query(Database::instance().db());
    if (!query.exec("SELECT id, nome, cor, ativo FROM tags ORDER BY nome")) {
        QMessageBox::warning(this, "Erro", "Falha ao carregar Tags: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tblTags->insertRow(row);
        ui->tblTags->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->tblTags->setItem(row, 1, new QTableWidgetItem(query.value("nome").toString()));
        ui->tblTags->setItem(row, 2, new QTableWidgetItem(query.value("cor").toString()));
        ui->tblTags->setItem(row, 3, new QTableWidgetItem(query.value("ativo").toString()));
        row++;
    }
    ui->tblTags->setColumnHidden(0, true);
}

void TagsWidget::on_btnNova_clicked(){
    auto *janela = new TagWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
    if (janela->exec() == QDialog::Accepted) { carregarTags(); }
}

void TagsWidget::on_btnEditar_clicked()
{
    QModelIndex index = ui->tblTags->currentIndex();

    if(!index.isValid())
    {
        QMessageBox::warning(this, "Tag", "Selecione uma tag.");
        return;
    }

    int linha = index.row();
    int id = ui->tblTags->item(linha, 0)->text().toInt();

    TagWidget dlg(this);
    dlg.setId(id);
    if (dlg.exec() == QDialog::Accepted){ carregarTags(); }
}
