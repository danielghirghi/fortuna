#include "CategoriasWindow.h"
#include "ui_CategoriasWindow.h"

#include "CategoriaDialog.h"

CategoriasWindow::CategoriasWindow(QWidget *parent) : QWidget(parent)
    , ui(new Ui::CategoriasWindow)
{
    ui->setupUi(this);

    setWindowTitle("Categorias");
}

CategoriasWindow::~CategoriasWindow(){ delete ui; }

void CategoriasWindow::on_btnNova_clicked(){
    auto *janela = new CategoriaDialog(nullptr);
    janela->show();
}
