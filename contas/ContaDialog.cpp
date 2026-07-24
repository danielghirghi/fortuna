#include "ContaDialog.h"
#include "ui_ContaDialog.h"

ContaDialog::ContaDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ContaDialog){
    ui->setupUi(this);
    setWindowTitle("Nova Conta");
}

ContaDialog::~ContaDialog(){ delete ui; }
