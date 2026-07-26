#include "ContasWidget.h"
#include "ui_ContasWidget.h"

#include "ContaWidget.h"

ContasWidget::ContasWidget(QWidget *parent) : QWidget(parent)
    , ui(new Ui::ContasWidget){
    ui->setupUi(this);

    setWindowTitle("Contas");
}

ContasWidget::~ContasWidget(){ delete ui; }

void ContasWidget::on_btnNova_clicked(){
    auto *janela = new ContaWidget(nullptr);
    janela->show();
}
