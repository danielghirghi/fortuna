#include "CategoriasWidget.h"
#include "ui_CategoriasWidget.h"

#include "CategoriaWidget.h"

CategoriasWidget::CategoriasWidget(QWidget *parent) : QWidget(parent)
    , ui(new Ui::CategoriasWidget)
{
    ui->setupUi(this);

    setWindowTitle("Categorias");
}

CategoriasWidget::~CategoriasWidget(){ delete ui; }

void CategoriasWidget::on_btnNova_clicked(){
    auto *janela = new CategoriaWidget(nullptr);
    janela->show();
}
