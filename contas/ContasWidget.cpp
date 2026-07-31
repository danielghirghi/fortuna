#include "ContasWidget.h"
#include "ui_ContasWidget.h"
#include "ContaWidget.h"
#include "../repositories/ContasRepository.h"

#include <QSqlQuery>

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

    ContasRepository repository;
    QList<Conta> contas = repository.listar();

    if (!repository.lastError().isEmpty())
    {
        QMessageBox::warning( this, "Erro", repository.lastError());
        return;
    }

    int row = 0;
    for (const Conta &conta : contas)
    {
        ui->tblContas->insertRow(row);
        ui->tblContas->setItem(row, 0, new QTableWidgetItem(QString::number(conta.id)));
        ui->tblContas->setItem(row, 1, new QTableWidgetItem(conta.nome));
        ui->tblContas->setItem(row, 2, new QTableWidgetItem(conta.tipo));
        ui->tblContas->setItem(row, 3, new QTableWidgetItem(conta.banco));
        ui->tblContas->setItem(row, 4, new QTableWidgetItem(QString::number(conta.saldoInicial, 'f', 2)));
        ui->tblContas->setItem(row, 5, new QTableWidgetItem(conta.ativo ? "Sim" : "Não"));
        row++;
    }
    ui->tblContas->setColumnHidden(0, true);
    ui->lblQuantidade->setText(QString::number(repository.contar()) + " contas");
    ui->tblContas->verticalHeader()->setVisible(false);
    ui->tblContas->setAlternatingRowColors(true);
    ui->tblContas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblContas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto *header = ui->tblContas->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ID
    header->setSectionResizeMode(1, QHeaderView::Stretch);          // Nome
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Tipo
    header->setSectionResizeMode(3, QHeaderView::Stretch);          // Banco
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents); // Saldo
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents); // Ativa
}

void ContasWidget::on_btnNova_clicked()
{
    ContaWidget *dlg = new ContaWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(ContaWidget::Modo::Inserir);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) { carregarContas(); }
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

    ContaWidget *dlg = new ContaWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(ContaWidget::Modo::Editar);
    dlg->setId(id);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) { carregarContas(); }
}

void ContasWidget::on_btnExcluir_clicked()
{
    QModelIndex index = ui->tblContas->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Conta", "Selecione uma conta.");
        return;
    }

    int linha = index.row();
    int id = ui->tblContas->item(linha, 0)->text().toInt();

    ContaWidget *dlg = new ContaWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(ContaWidget::Modo::Excluir);
    dlg->setId(id);
    if (dlg->exec() == QDialog::Accepted) { carregarContas(); }
}

