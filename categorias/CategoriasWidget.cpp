#include "CategoriasWidget.h"
#include "ui_CategoriasWidget.h"
#include "CategoriaWidget.h"

#include <QSqlQuery>
#include "../database/Database.h"

#include <QMessageBox>
#include <QSqlError>
#include <QTableWidgetItem>

CategoriasWidget::CategoriasWidget(QWidget *parent) : QWidget(parent)
    , ui(new Ui::CategoriasWidget)
{
    ui->setupUi(this);
    setWindowTitle("Categorias");

    carregarCategorias();
}

CategoriasWidget::~CategoriasWidget(){ delete ui; }

void CategoriasWidget::on_btnNova_clicked(){
    auto *janela = new CategoriaWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();

    if (janela->exec() == QDialog::Accepted) { carregarCategorias(); }
}

void CategoriasWidget::carregarCategorias()
{
    ui->tblCategorias->setRowCount(0);

    QSqlQuery query(Database::instance().db());
    if (!query.exec("SELECT nome, grupo, tipo, ativo FROM categorias ORDER BY nome")) {
        QMessageBox::warning(this, "Erro", "Falha ao carregar categorias: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tblCategorias->insertRow(row);
        ui->tblCategorias->setItem(row, 0, new QTableWidgetItem(query.value("nome").toString()));
        ui->tblCategorias->setItem(row, 1, new QTableWidgetItem(query.value("grupo").toString()));
        ui->tblCategorias->setItem(row, 2, new QTableWidgetItem(query.value("tipo").toString()));
        ui->tblCategorias->setItem(row, 3, new QTableWidgetItem(query.value("ativo").toString()));
        row++;
    }
}
