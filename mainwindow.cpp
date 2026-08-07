#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>

#include <QTableView>
#include <QStandardItemModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database/Database.h"
#include "config/configmanager.h"

#include "contas/ContasWidget.h"
#include "categorias/CategoriasWidget.h"
#include "tags/TagsWidget.h"
#include "movimentacoes/MovimentacoesWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle("Fortuna");

    tabelaInfo();
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::on_btnContas_clicked(){ abrirJanela(m_contas); }
void MainWindow::on_btnCategorias_clicked(){ abrirJanela(m_categorias); }
void MainWindow::on_btnTags_clicked(){ abrirJanela(m_tags); }
void MainWindow::on_btnMovimentacoes_clicked(){ abrirJanela(m_movimentacoes); }

void MainWindow::on_actionAbrirArquivo_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Selecionar banco"),
        QDir::homePath(),
        tr("Banco de dados (*.db)")
        );

    if (filePath.isEmpty())
        return;

    if (!Database::instance().connect(filePath))
    {
        QMessageBox::critical(this,
                              tr("Erro"),
                              tr("Não foi possível abrir o banco."));
        return;
    }

    ConfigManager::setDatabasePath(filePath);

    atualizarInterface();
}

void MainWindow::tabelaInfo()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    QStringList conexoes = QSqlDatabase::connectionNames();

    QStandardItemModel *m_infoModel = new QStandardItemModel(this);

    m_infoModel->setHorizontalHeaderLabels({
        "Conexão",
        "Arquivo",
        "Aberta"
    });

    ui->tblInfo->setModel(m_infoModel);

    for (const QString &nome : conexoes)
    {
        QSqlDatabase db = QSqlDatabase::database(nome);

        QList<QStandardItem*> linha;

        linha << new QStandardItem(db.connectionName());
        linha << new QStandardItem(db.databaseName());
        linha << new QStandardItem(db.isOpen() ? "Sim" : "Não");

        model->appendRow(linha);
    }

    ui->tblInfo->setModel(model);
    ui->tblInfo->resizeColumnsToContents();
}

void MainWindow::atualizarInterface()
{
    tabelaInfo();
    if (m_contas)        m_contas->refresh();
    if (m_categorias)    m_categorias->refresh();
    if (m_tags)          m_tags->refresh();
    if (m_movimentacoes) m_movimentacoes->refresh();
}
