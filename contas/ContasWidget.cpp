#include "ContasWidget.h"
#include "ui_ContasWidget.h"
#include "ContaWidget.h"

#include <QSqlQuery>
#include "../database/Database.h"

#include <QMessageBox>
#include <QSqlError>
#include <QTableWidgetItem>

ContasWidget::ContasWidget(QWidget *parent) : QWidget(parent)
    , ui(new Ui::ContasWidget)
{
    ui->setupUi(this);
    setWindowTitle("Contas");

    carregarContas();

    ui->tblContas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblContas->setSelectionMode(QAbstractItemView::SingleSelection);
}

ContasWidget::~ContasWidget(){ delete ui; }

void ContasWidget::carregarContas()
{
    ui->tblContas->setRowCount(0);

    QSqlQuery query(Database::instance().db());
    if (!query.exec("SELECT id, nome, tipo, banco, saldo_inicial, ativo FROM contas ORDER BY nome")) {
        QMessageBox::warning(this, "Erro", "Falha ao carregar contas: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tblContas->insertRow(row);
        ui->tblContas->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->tblContas->setItem(row, 1, new QTableWidgetItem(query.value("nome").toString()));
        ui->tblContas->setItem(row, 2, new QTableWidgetItem(query.value("tipo").toString()));
        ui->tblContas->setItem(row, 3, new QTableWidgetItem(query.value("banco").toString()));
        ui->tblContas->setItem(row, 4, new QTableWidgetItem(query.value("saldo_inicial").toString()));
        ui->tblContas->setItem(row, 5, new QTableWidgetItem(query.value("ativo").toString()));
        row++;
    }
    ui->tblContas->setColumnHidden(0, true);
}

void ContasWidget::on_btnNova_clicked()
{
    auto *janela = new ContaWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
    if (janela->exec() == QDialog::Accepted) { carregarContas(); }
}

void ContasWidget::on_btnEditar_clicked()
{
    QModelIndex index = ui->tblContas->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Conta", "Selecione uma conta.");
        return;
    }

    int linha = index.row();
    int id = ui->tblContas->item(linha, 0)->text().toInt();

    ContaWidget dlg(this);
    dlg.setId(id);
    if (dlg.exec() == QDialog::Accepted) { carregarContas(); }
}
