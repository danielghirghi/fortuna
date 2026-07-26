#include <qmenu.h>

#include "MovimentacoesWidget.h"
#include "ui_MovimentacoesWidget.h"

#include "ReceitaWidget.h"
#include "DespesaWidget.h"
#include "TransferenciaWidget.h"

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
}

void MovimentacoesWidget::abrirReceita() {
    auto *janela = new ReceitaWidget(this);
    janela->show();
}

void MovimentacoesWidget::abrirDespesa() {
    auto *janela = new DespesaWidget(this);
    janela->show();
}

void MovimentacoesWidget::abrirTransferencia() {
    auto *janela = new TransferenciaWidget(this);
    janela->show();
}

MovimentacoesWidget::~MovimentacoesWidget() { delete ui; }

