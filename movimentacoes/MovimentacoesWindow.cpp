#include <qmenu.h>

#include "MovimentacoesWindow.h"
#include "ui_MovimentacoesWindow.h"

#include "ReceitaDialog.h"
#include "DespesaDialog.h"
#include "TransferenciaDialog.h"

MovimentacoesWindow::MovimentacoesWindow(QWidget *parent) : QWidget(parent)
    , ui(new Ui::MovimentacoesWindow){
    ui->setupUi(this);

    QMenu *menu = new QMenu(this);

    QAction *actReceita = menu->addAction("Receita");
    connect(actReceita, &QAction::triggered, this, &MovimentacoesWindow::abrirReceita);
    QAction *actDespesa = menu->addAction("Despesa");
    connect(actDespesa, &QAction::triggered, this, &MovimentacoesWindow::abrirDespesa);
    QAction *actTransferencia = menu->addAction("Transferência");
    connect(actTransferencia, &QAction::triggered, this, &MovimentacoesWindow::abrirTransferencia);

    ui->btnNova->setMenu(menu);

    setWindowTitle("Movimentações");
}

void MovimentacoesWindow::abrirReceita() {
    auto *janela = new ReceitaDialog(this);
    janela->show();
}

void MovimentacoesWindow::abrirDespesa() {
    auto *janela = new DespesaDialog(this);
    janela->show();
}

void MovimentacoesWindow::abrirTransferencia() {
    auto *janela = new TransferenciaDialog(this);
    janela->show();
}

MovimentacoesWindow::~MovimentacoesWindow() { delete ui; }

