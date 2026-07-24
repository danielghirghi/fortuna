#include "TransferenciaDialog.h"
#include "ui_TransferenciaDialog.h"

TransferenciaDialog::TransferenciaDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TransferenciaDialog){
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Transferência");
}

TransferenciaDialog::~TransferenciaDialog(){ delete ui; }
