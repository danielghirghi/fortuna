#include "CategoriaWidget.h"
#include "ui_CategoriaWidget.h"

CategoriaWidget::CategoriaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::CategoriaWidget){
        ui->setupUi(this);
        setWindowTitle("Nova Categoria");
}

CategoriaWidget::~CategoriaWidget(){ delete ui; }
