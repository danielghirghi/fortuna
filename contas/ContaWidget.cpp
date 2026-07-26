#include "ContaWidget.h"
#include "ui_ContaWidget.h"

ContaWidget::ContaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::ContaWidget){
    ui->setupUi(this);
    setWindowTitle("Nova Conta");
}

ContaWidget::~ContaWidget(){ delete ui; }
