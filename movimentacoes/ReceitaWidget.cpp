#include "ReceitaWidget.h"
#include "ui_ReceitaWidget.h"

ReceitaWidget::ReceitaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ReceitaWidget){
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Receita");
}

ReceitaWidget::~ReceitaWidget(){ delete ui; }
