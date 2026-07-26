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
}

void MovimentacoesWidget::carregarMovimentacoes()
{
    ui->tblMovimentacoes->setRowCount(0);

    QSqlQuery query(Database::instance().db());
    if (!query.exec("SELECT data, valor, descricao, tipo, conta_origem_id, conta_destino_id, categoria_id FROM movimentacoes ORDER BY data")) {
        QMessageBox::warning(this, "Erro", "Falha ao carregar Movimentações: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tblMovimentacoes->insertRow(row);
        ui->tblMovimentacoes->setItem(row, 0, new QTableWidgetItem(query.value("data").toString()));
        ui->tblMovimentacoes->setItem(row, 1, new QTableWidgetItem(query.value("valor").toString()));
        ui->tblMovimentacoes->setItem(row, 2, new QTableWidgetItem(query.value("descricao").toString()));
        ui->tblMovimentacoes->setItem(row, 3, new QTableWidgetItem(query.value("tipo").toString()));
        ui->tblMovimentacoes->setItem(row, 4, new QTableWidgetItem(query.value("conta_origem_id").toString()));
        ui->tblMovimentacoes->setItem(row, 5, new QTableWidgetItem(query.value("conta_destino_id").toString()));
        ui->tblMovimentacoes->setItem(row, 6, new QTableWidgetItem(query.value("categoria_id").toString()));
        row++;
    }
}

void MovimentacoesWidget::abrirReceita() {
    auto *janela = new ReceitaWidget(this);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

void MovimentacoesWidget::abrirDespesa() {
    auto *janela = new DespesaWidget(this);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

void MovimentacoesWidget::abrirTransferencia() {
    auto *janela = new TransferenciaWidget(this);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

MovimentacoesWidget::~MovimentacoesWidget() { delete ui; }

