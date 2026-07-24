#include "ContasWindow.h"
#include "ui_ContasWindow.h"

#include "ContaDialog.h"

ContasWindow::ContasWindow(QWidget *parent) : QWidget(parent)
    , ui(new Ui::ContasWindow){
    ui->setupUi(this);

    setWindowTitle("Contas");
}

ContasWindow::~ContasWindow(){ delete ui; }

void ContasWindow::on_btnNova_clicked(){
    auto *janela = new ContaDialog(nullptr);
    janela->show();
}
