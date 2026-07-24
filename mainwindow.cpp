#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "contas/ContasWindow.h"
#include "categorias/CategoriasWindow.h"
#include "tags/TagsWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){ ui->setupUi(this); }

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_btnContas_clicked(){
    auto *janela = new ContasWindow(nullptr);
    janela->show();
}

void MainWindow::on_btnCategorias_clicked(){
    auto *janela = new CategoriasWindow(nullptr);
    janela->show();
}

void MainWindow::on_btnTags_clicked(){
    auto *janela = new TagsWindow(nullptr);
    janela->show();
}
