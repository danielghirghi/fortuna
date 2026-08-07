#include <qmenu.h>
#include <QMessageBox>
#include <QSqlError>
#include <QTableWidgetItem>

#include "MovimentacoesWidget.h"
#include "ui_MovimentacoesWidget.h"

#include "../../repositories/MovimentacoesRepository.h"
#include "../../dialogs/movimentacoes/MovimentacaoWidget.h"

#include "../../models/Format.h"

MovimentacoesWidget::MovimentacoesWidget(QWidget *parent) : BaseWidget(parent)
    , ui(new Ui::MovimentacoesWidget){
    ui->setupUi(this);

    setWindowTitle("Movimentações");

    carregarMovimentacoes();

    ui->tblMovimentacoes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblMovimentacoes->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->edtPesquisar, &QLineEdit::returnPressed, this, &MovimentacoesWidget::on_btnPesquisar_clicked);
}

MovimentacoesWidget::~MovimentacoesWidget() { delete ui; }

void MovimentacoesWidget::carregarMovimentacoes()
{
    ui->tblMovimentacoes->setRowCount(0);

    MovimentacoesRepository repository;
    QList<Movimentacao> movimentacoes = repository.listar();

    if (!repository.lastError().isEmpty())
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }

    int row = 0;
    for (const Movimentacao &movimentacao : movimentacoes) {
        ui->tblMovimentacoes->insertRow(row);
        ui->tblMovimentacoes->setItem(row, 0, new QTableWidgetItem(QString::number(movimentacao.id)));
        ui->tblMovimentacoes->setItem(row, 1, new QTableWidgetItem(Format::data(movimentacao.data)));
        ui->tblMovimentacoes->setItem(row, 2, new QTableWidgetItem(QString::number(movimentacao.valor,'f', 2)));
        ui->tblMovimentacoes->setItem(row, 3, new QTableWidgetItem(movimentacao.descricao));
        ui->tblMovimentacoes->setItem(row, 4, new QTableWidgetItem(movimentacao.getTipo()));
        ui->tblMovimentacoes->setItem(row, 5, new QTableWidgetItem(movimentacao.origem));
        ui->tblMovimentacoes->setItem(row, 6, new QTableWidgetItem(movimentacao.destino));
        ui->tblMovimentacoes->setItem(row, 7, new QTableWidgetItem(movimentacao.categoria));
        row++;
    }
    ui->tblMovimentacoes->setColumnHidden(0,true);
    ui->lblQuantidade->setText(QString::number(movimentacoes.count()) + " movimentações");
    ui->tblMovimentacoes->verticalHeader()->setVisible(false);
    ui->tblMovimentacoes->setAlternatingRowColors(true);
    ui->tblMovimentacoes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblMovimentacoes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblMovimentacoes->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    auto *header = ui->tblMovimentacoes->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ID
    header->setSectionResizeMode(1, QHeaderView::Stretch);          // Data
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Valor
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Descrição
    header->setSectionResizeMode(4, QHeaderView::Stretch); // Tipo
    header->setSectionResizeMode(5, QHeaderView::Stretch); // Origem
    header->setSectionResizeMode(6, QHeaderView::Stretch); // Destino
    header->setSectionResizeMode(7, QHeaderView::ResizeToContents); // Categoria
}

void MovimentacoesWidget::on_btnNova_clicked() {
    auto *dlg = new MovimentacaoWidget(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(Modo::Inserir);
    dlg->show();
    if (dlg->exec() == QDialog::Accepted) { carregarMovimentacoes(); }
}

void MovimentacoesWidget::on_btnEditar_clicked()
{
    QModelIndex index = ui->tblMovimentacoes->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Movimentação", "Selecione uma Movimentação.");
        return;
    }

    int linha = index.row();
    int id = ui->tblMovimentacoes->item(linha, 0)->text().toInt();

    MovimentacaoWidget *dlg = new MovimentacaoWidget(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setTipo(ui->tblMovimentacoes->item(linha, 4)->text());
    dlg->setModo(Modo::Editar);
    dlg->setId(id);
    if (dlg->exec() == QDialog::Accepted) { carregarMovimentacoes(); }
    
}

void MovimentacoesWidget::on_btnExcluir_clicked()
{
    QModelIndex index = ui->tblMovimentacoes->currentIndex();

    if (!index.isValid())
    {
        QMessageBox::warning(this, "Movimentação", "Selecione uma movimentação.");
        return;
    }

    int linha = index.row();
    int id = ui->tblMovimentacoes->item(linha, 0)->text().toInt();

    MovimentacaoWidget *dlg = new MovimentacaoWidget(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setModo(Modo::Excluir);
    dlg->setId(id);
    if (dlg->exec() == QDialog::Accepted) { carregarMovimentacoes(); }
}

void MovimentacoesWidget::refresh()
{
    carregarMovimentacoes();
}

void MovimentacoesWidget::on_btnLimpar_clicked()
{
    ui->edtPesquisar->setText("");
    carregarMovimentacoes();
}

void MovimentacoesWidget::on_btnPesquisar_clicked()
{
    ui->tblMovimentacoes->setRowCount(0);

    QString busca = ui->edtPesquisar->text();

    MovimentacoesRepository repository;
    QList<Movimentacao> movimentacoes = repository.pesquisar(busca);

    if (!repository.lastError().isEmpty())
    {
        QMessageBox::warning( this, "Erro", repository.lastError());
        return;
    }


    int row = 0;
    for (const Movimentacao &movimentacao : movimentacoes) {
        ui->tblMovimentacoes->insertRow(row);
        ui->tblMovimentacoes->setItem(row, 0, new QTableWidgetItem(QString::number(movimentacao.id)));
        ui->tblMovimentacoes->setItem(row, 1, new QTableWidgetItem(Format::data(movimentacao.data)));
        ui->tblMovimentacoes->setItem(row, 2, new QTableWidgetItem(QString::number(movimentacao.valor,'f', 2)));
        ui->tblMovimentacoes->setItem(row, 3, new QTableWidgetItem(movimentacao.descricao));
        ui->tblMovimentacoes->setItem(row, 4, new QTableWidgetItem(movimentacao.getTipo()));
        ui->tblMovimentacoes->setItem(row, 5, new QTableWidgetItem(movimentacao.origem));
        ui->tblMovimentacoes->setItem(row, 6, new QTableWidgetItem(movimentacao.destino));
        ui->tblMovimentacoes->setItem(row, 7, new QTableWidgetItem(movimentacao.categoria));
        row++;
    }
    ui->tblMovimentacoes->setColumnHidden(0,true);
    ui->lblQuantidade->setText(QString::number(movimentacoes.count()) + " movimentações");
    ui->tblMovimentacoes->verticalHeader()->setVisible(false);
    ui->tblMovimentacoes->setAlternatingRowColors(true);
    ui->tblMovimentacoes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblMovimentacoes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblMovimentacoes->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    auto *header = ui->tblMovimentacoes->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // ID
    header->setSectionResizeMode(1, QHeaderView::Stretch);          // Data
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents); // Valor
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents); // Descrição
    header->setSectionResizeMode(4, QHeaderView::Stretch); // Tipo
    header->setSectionResizeMode(5, QHeaderView::Stretch); // Origem
    header->setSectionResizeMode(6, QHeaderView::Stretch); // Destino
    header->setSectionResizeMode(7, QHeaderView::ResizeToContents); // Categoria
}
