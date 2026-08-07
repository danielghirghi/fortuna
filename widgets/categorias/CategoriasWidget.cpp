#include "CategoriasWidget.h"
#include "ui_CategoriasWidget.h"
#include "../../dialogs/categorias/CategoriaWidget.h"
#include "../../repositories/CategoriasRepository.h"

#include <QSqlQuery>

#include <QMessageBox>
#include <QSqlError>
#include <QTableWidgetItem>

CategoriasWidget::CategoriasWidget(QWidget *parent) : BaseWidget(parent)
    , ui(new Ui::CategoriasWidget)
{
    ui->setupUi(this);
    setWindowTitle("Categorias");

    carregarCategorias();

    ui->tblCategorias->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblCategorias->setSelectionMode(QAbstractItemView::SingleSelection);
}

CategoriasWidget::~CategoriasWidget(){ delete ui; }

void CategoriasWidget::carregarCategorias()
{
    ui->tblCategorias->setRowCount(0);

    CategoriasRepository repository;
    QList<Categoria> categorias = repository.listar();

    if (!repository.lastError().isEmpty())
    {
        QMessageBox::warning( this, "Erro", repository.lastError());
        return;
    }

    int row = 0;
    for (const Categoria &categoria : categorias) {
        ui->tblCategorias->insertRow(row);
        ui->tblCategorias->setItem(row, 0, new QTableWidgetItem(QString::number(categoria.id)));
        ui->tblCategorias->setItem(row, 1, new QTableWidgetItem(categoria.nome));
        ui->tblCategorias->setItem(row, 3, new QTableWidgetItem(categoria.grupo));
        ui->tblCategorias->setItem(row, 2, new QTableWidgetItem(categoria.tipo));
        ui->tblCategorias->setItem(row, 4, new QTableWidgetItem(categoria.ativo ? "Sim" : "Não"));
        row++;
    }
    ui->tblCategorias->setColumnHidden(0,true);
    ui->lblQuantidade->setText(QString::number(repository.contar()) + " categorias");
    ui->tblCategorias->verticalHeader()->setVisible(false);
    ui->tblCategorias->setAlternatingRowColors(true);
    ui->tblCategorias->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblCategorias->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblCategorias->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    auto *header = ui->tblCategorias->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ID
    header->setSectionResizeMode(1, QHeaderView::Stretch);          // Nome
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Grupo
    header->setSectionResizeMode(3, QHeaderView::Stretch);          // Tipo
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents); // Ativa
}

void CategoriasWidget::on_btnNova_clicked()
{
    CategoriaWidget *dlg = new CategoriaWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(CategoriaWidget::Modo::Inserir);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) { carregarCategorias(); }
}

void CategoriasWidget::on_btnEditar_clicked()
{
    QModelIndex index = ui->tblCategorias->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Categoria", "Selecione uma categoria.");
        return;
    }

    int linha = index.row();
    int id = ui->tblCategorias->item(linha, 0)->text().toInt();

    CategoriaWidget *dlg = new CategoriaWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(CategoriaWidget::Modo::Editar);
    dlg->setId(id);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) { carregarCategorias(); }
}

void CategoriasWidget::on_btnExcluir_clicked()
{
    QModelIndex index = ui->tblCategorias->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Categoria", "Selecione uma categoria.");
        return;
    }

    int linha = index.row();
    int id = ui->tblCategorias->item(linha, 0)->text().toInt();


    CategoriaWidget *dlg = new CategoriaWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(CategoriaWidget::Modo::Excluir);
    dlg->setId(id);
    if (dlg->exec() == QDialog::Accepted) { carregarCategorias(); }
}

void CategoriasWidget::refresh()
{
    carregarCategorias();
}
