#include "CategoriasWindow.h"
#include "ui_CategoriasWindow.h"

CategoriasWindow::CategoriasWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CategoriasWindow)
{
    ui->setupUi(this);

    setWindowTitle("Categorias");
}

CategoriasWindow::~CategoriasWindow()
{
    delete ui;
}
