#include "TagsWidget.h"
#include "ui_TagsWidget.h"
#include "TagWidget.h"
#include "../repositories/TagsRepository.h"

#include <QSqlQuery>

#include <QMessageBox>
#include <QSqlError>
#include <QTableWidgetItem>

TagsWidget::TagsWidget(QWidget *parent) : BaseWidget(parent)
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

    TagsRepository repository;
    QList<Tag> tags = repository.listar();

    if (!repository.lastError().isEmpty())
    {
        QMessageBox::warning( this, "Erro", repository.lastError());
        return;
    }

    int row = 0;

    for (const Tag &tag : tags)
    {
        ui->tblTags->insertRow(row);
        ui->tblTags->setItem(row, 0, new QTableWidgetItem(QString::number(tag.id)));
        ui->tblTags->setItem(row, 1, new QTableWidgetItem(tag.nome));
        ui->tblTags->setItem(row, 2, new QTableWidgetItem(tag.cor));
        ui->tblTags->setItem(row, 3, new QTableWidgetItem(tag.ativo ? "Sim" : "Não"));
        row++;
    }
    ui->tblTags->setColumnHidden(0, true);
    ui->lblQuantidade->setText(QString::number(repository.contar()) + " tags");
    ui->tblTags->verticalHeader()->setVisible(false);
    ui->tblTags->setAlternatingRowColors(true);
    ui->tblTags->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblTags->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto *header = ui->tblTags->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ID
    header->setSectionResizeMode(1, QHeaderView::Stretch);          // Nome
    header->setSectionResizeMode(2, QHeaderView::Stretch); // Cor
    header->setSectionResizeMode(3, QHeaderView::Stretch); // Ativa
}

void TagsWidget::on_btnNova_clicked()
{
    TagWidget *dlg = new TagWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(TagWidget::Modo::Inserir);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) { carregarTags(); }
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

    TagWidget *dlg = new TagWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(TagWidget::Modo::Editar);
    dlg->setId(id);
    if (dlg->exec() == QDialog::Accepted){ carregarTags(); }
}

void TagsWidget::on_btnExcluir_clicked()
{
    QModelIndex index = ui->tblTags->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Tag", "Selecione uma tag.");
        return;
    }

    int linha = index.row();
    int id = ui->tblTags->item(linha, 0)->text().toInt();

    TagWidget *dlg = new TagWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(TagWidget::Modo::Excluir);
    dlg->setId(id);
    if (dlg->exec() == QDialog::Accepted) { carregarTags(); }
}

void TagsWidget::refresh()
{
    carregarTags();
}
