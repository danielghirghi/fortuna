#include <qmenu.h>

#include "MovimentacoesWidget.h"
#include "ui_MovimentacoesWidget.h"

#include "ReceitaWidget.h"
#include "DespesaWidget.h"
#include "TransferenciaWidget.h"

#include <QSqlQuery>
#include "../database/Database.h"

#include <QMessageBox>
#include <QSqlError>
#include <QTableWidgetItem>

MovimentacoesWidget::MovimentacoesWidget(QWidget *parent) : QWidget(parent)
    , ui(new Ui::MovimentacoesWidget){
    ui->setupUi(this);

    QMenu *menu = new QMenu(this);

    QAction *actReceita = menu->addAction("Receita");
    connect(actReceita, &QAction::triggered, this, &MovimentacoesWidget::abrirReceita);
    QAction *actDespesa = menu->addAction("Despesa");
    connect(actDespesa, &QAction::triggered, this, &MovimentacoesWidget::abrirDespesa);
    QAction *actTransferencia = menu->addAction("Transferência");
    connect(actTransferencia, &QAction::triggered, this, &MovimentacoesWidget::abrirTransferencia);

    ui->btnNova->setMenu(menu);

    setWindowTitle("Movimentações");

    carregarMovimentacoes();

    ui->tblMovimentacoes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblMovimentacoes->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MovimentacoesWidget::carregarMovimentacoes()
{
    ui->tblMovimentacoes->setRowCount(0);

    QSqlQuery query(Database::instance().db());
    if (!query.exec("SELECT m.id, m.data, m.descricao, co.nome AS conta_origem, cd.nome AS conta_destino, cat.nome AS categoria, m.valor, m.tipo AS tipo FROM movimentacoes m LEFT JOIN contas co ON co.id = m.conta_origem_id LEFT JOIN contas cd ON cd.id = m.conta_destino_id LEFT JOIN categorias cat ON cat.id = m.categoria_id ORDER BY m.data DESC")) {
        QMessageBox::warning(this, "Erro", "Falha ao carregar Movimentações: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tblMovimentacoes->insertRow(row);
        ui->tblMovimentacoes->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->tblMovimentacoes->setItem(row, 1, new QTableWidgetItem(query.value("data").toString()));
        ui->tblMovimentacoes->setItem(row, 2, new QTableWidgetItem(query.value("valor").toString()));
        ui->tblMovimentacoes->setItem(row, 3, new QTableWidgetItem(query.value("descricao").toString()));
        ui->tblMovimentacoes->setItem(row, 4, new QTableWidgetItem(query.value("tipo").toString()));
        ui->tblMovimentacoes->setItem(row, 5, new QTableWidgetItem(query.value("conta_origem").toString()));
        ui->tblMovimentacoes->setItem(row, 6, new QTableWidgetItem(query.value("conta_destino").toString()));
        ui->tblMovimentacoes->setItem(row, 7, new QTableWidgetItem(query.value("categoria").toString()));
        row++;
    }
    ui->tblMovimentacoes->setColumnHidden(0,true);
}

void MovimentacoesWidget::abrirReceita() {
    auto *janela = new ReceitaWidget(this);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
    if (janela->exec() == QDialog::Accepted) { carregarMovimentacoes(); }
}

void MovimentacoesWidget::abrirDespesa() {
    auto *janela = new DespesaWidget(this);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
    if (janela->exec() == QDialog::Accepted) { carregarMovimentacoes(); }
}

void MovimentacoesWidget::abrirTransferencia() {
    auto *janela = new TransferenciaWidget(this);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
    if (janela->exec() == QDialog::Accepted) { carregarMovimentacoes(); }
}

void MovimentacoesWidget::on_btnEditar_clicked()
{
    QModelIndex index = ui->tblMovimentacoes->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Movimentação", "Selecione uma Movimentação.");
        return;
    }

    int linha = index.row();
    int id = ui->tblMovimentacoes->item(linha, 0)->text().toInt();

    auto tipo = ui->tblMovimentacoes->item(linha, 4)->text();
    if (tipo == "DESPESA"){
        DespesaWidget dlg(this);
        dlg.setId(id);
        if (dlg.exec() == QDialog::Accepted) { carregarMovimentacoes(); }
    }
    if (tipo == "RENDA"){
        ReceitaWidget dlg(this);
        dlg.setId(id);
        if (dlg.exec() == QDialog::Accepted) { carregarMovimentacoes(); }
    }
    if (tipo == "TRANSFERENCIA"){
        TransferenciaWidget dlg(this);
        dlg.setId(id);
        if (dlg.exec() == QDialog::Accepted) { carregarMovimentacoes(); }
    }
}

MovimentacoesWidget::~MovimentacoesWidget() { delete ui; }

