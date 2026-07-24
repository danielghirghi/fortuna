#include "ContasWindow.h"
#include "ui_ContasWindow.h"

ContasWindow::ContasWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ContasWindow)
{
    ui->setupUi(this);

    setWindowTitle("Contas");
}

ContasWindow::~ContasWindow()
{
    delete ui;
}
