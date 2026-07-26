#include "DespesaWidget.h"
#include "ui_DespesaWidget.h"

DespesaWidget::DespesaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::DespesaWidget){
    ui->setupUi(this);
    setWindowTitle("Nova Movimentação - Despesa");
}

DespesaWidget::~DespesaWidget(){ delete ui; }
