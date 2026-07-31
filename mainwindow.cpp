#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle("Fortuna");
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_btnContas_clicked(){ abrirJanela(m_contas); }
void MainWindow::on_btnCategorias_clicked(){ abrirJanela(m_categorias); }
void MainWindow::on_btnTags_clicked(){ abrirJanela(m_tags); }
void MainWindow::on_btnMovimentacoes_clicked(){ abrirJanela(m_movimentacoes); }
