#include "CategoriaDialog.h"
#include "ui_CategoriaDialog.h"

CategoriaDialog::CategoriaDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::CategoriaDialog){
        ui->setupUi(this);
        setWindowTitle("Nova Categoria");
}

CategoriaDialog::~CategoriaDialog(){ delete ui; }
