#include "mainwindow.h"
#include "movimentacoes/MovimentacoesWidget.h"
#include "ui_mainwindow.h"

#include "contas/ContasWidget.h"
#include "categorias/CategoriasWidget.h"
#include "tags/TagsWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle("Fortuna");
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_btnContas_clicked(){
    auto *janela = new ContasWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

void MainWindow::on_btnCategorias_clicked(){
    auto *janela = new CategoriasWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

void MainWindow::on_btnTags_clicked(){
    auto *janela = new TagsWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

void MainWindow::on_btnMovimentacoes_clicked(){
    auto *janela = new MovimentacoesWidget(nullptr);
    janela->setAttribute(Qt::WA_DeleteOnClose);
    janela->show();
}

