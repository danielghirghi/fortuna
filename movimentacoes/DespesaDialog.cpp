#include "DespesaDialog.h"
#include "ui_DespesaDialog.h"

DespesaDialog::DespesaDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::DespesaDialog){
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Despesa");
}

DespesaDialog::~DespesaDialog(){ delete ui; }
