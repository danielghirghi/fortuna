#include "TransferenciaWidget.h"
#include "ui_TransferenciaWidget.h"

TransferenciaWidget::TransferenciaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TransferenciaWidget){
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Transferência");
}

TransferenciaWidget::~TransferenciaWidget(){ delete ui; }
