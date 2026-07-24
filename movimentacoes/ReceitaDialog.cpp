#include "ReceitaDialog.h"
#include "ui_ReceitaDialog.h"

ReceitaDialog::ReceitaDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ReceitaDialog){
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Receita");
}

ReceitaDialog::~ReceitaDialog(){ delete ui; }
