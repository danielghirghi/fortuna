#include "MovimentacaoWidget.h"
#include "ui_MovimentacaoWidget.h"

#include "../../repositories/MovimentacoesRepository.h"

#include "../../repositories/ContasRepository.h"
#include "../../repositories/CategoriasRepository.h"

#include <qmenu.h>
#include <qpushbutton.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

MovimentacaoWidget::MovimentacaoWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::MovimentacaoWidget)
{
    ui->setupUi(this);

    ui->spnValor->setDecimals(2);
    ui->spnValor->setMinimum(-1000000000.0);
    ui->spnValor->setMaximum(1000000000.0);

    ui->dateMovimentacao->setDate(QDate::currentDate());
    ui->dateMovimentacao->setCalendarPopup(true);

    ui->cmbTipo->addItem("Despesa", QVariant::fromValue(int(TipoMovimentacao::Despesa)));
    ui->cmbTipo->addItem("Renda", QVariant::fromValue(int(TipoMovimentacao::Receita)));
    ui->cmbTipo->addItem("Transferência", QVariant::fromValue(int(TipoMovimentacao::Transferencia)));
    atualizarInterface();

    connect(ui->cmbTipo,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &MovimentacaoWidget::atualizarInterface);

    connect(ui->bbMovimentacao, &QDialogButtonBox::accepted, this, &MovimentacaoWidget::confirmar);
    connect(ui->bbMovimentacao, &QDialogButtonBox::rejected, this, &MovimentacaoWidget::reject);
}

MovimentacaoWidget::~MovimentacaoWidget(){ delete ui; }

QString MovimentacaoWidget::getTipo() const
{
    switch (MovimentacaoWidget::tipo)
    {
    case TipoMovimentacao::Receita:
        return "RENDA";
    case TipoMovimentacao::Despesa:
        return "DESPESA";
    case TipoMovimentacao::Transferencia:
        return "TRANSFERENCIA";
    }
    return "ERRO";
}

void MovimentacaoWidget::setTipo(QString tipo)
{
    if (tipo == "RENDA" || tipo == "RECEITA")
    {
        MovimentacaoWidget::tipo = TipoMovimentacao::Receita;
        return;
    }
    if (tipo =="DESPESA")
    {
        MovimentacaoWidget::tipo = TipoMovimentacao::Despesa;
        return;
    }
    if (tipo =="TRANSFERENCIA")
    {
        MovimentacaoWidget::tipo = TipoMovimentacao::Transferencia;
        return;
    }
}

void MovimentacaoWidget::atualizarInterface()
{
    ui->cmbPrim->clear();
    ui->cmbSecn->clear();

    QString tipo = ui->cmbTipo->currentText();

    ContasRepository contasrepo;
    QList<Conta> contas = contasrepo.listar();
    if (!contasrepo.lastError().isEmpty())
    {
        QMessageBox::warning( this, "Erro", contasrepo.lastError());
        return;
    }
    for (const Conta &conta : contas){ ui->cmbPrim->addItem(conta.nome); }

    if (tipo.compare("Transferencia", Qt::CaseInsensitive) == 0 ||
        tipo.compare("Transferência", Qt::CaseInsensitive)== 0)
    {
        this->setTipo("TRANSFERENCIA");
        ui->lblPrim->setText("Conta Origem:");
        ui->lblSecn->setText("Conta Destino:");
        for (const Conta &conta : contas)
        { ui->cmbSecn->addItem(conta.nome); }
        return;
    }
    CategoriasRepository catrepo;
    QList<Categoria> categorias = catrepo.listar();
    if (!catrepo.lastError().isEmpty())
    {
        QMessageBox::warning( this, "Erro", contasrepo.lastError());
        return;
    }

    if (tipo.compare("Renda", Qt::CaseInsensitive) == 0 ||
        tipo.compare("Receita", Qt::CaseInsensitive)== 0)
    {
        this->setTipo("RENDA");
        ui->lblPrim->setText("Conta Destino:");
        ui->lblSecn->setText("Categoria:");
        for (const Categoria &categoria : categorias)
        {
            if (categoria.tipo.compare("Renda", Qt::CaseInsensitive) == 0)
            {
                ui->cmbSecn->addItem(categoria.nome);
            }
        }
        return;
    }

    // Tipo = DESPESA
    this->setTipo("DESPESA");
    ui->lblPrim->setText("Conta Origem:");
    ui->lblSecn->setText("Categoria:");
    for (const Categoria &categoria : categorias)
    {
        if (categoria.tipo.compare("Despesa", Qt::CaseInsensitive) == 0)
        {
            ui->cmbSecn->addItem(categoria.nome);
        }
    }
    return;
}

Movimentacao MovimentacaoWidget::movimentacaoDaInterface() const
{
    Movimentacao movimentacao;

    movimentacao.data = ui->dateMovimentacao->date();
    movimentacao.descricao = ui->edtDescricao->text();
    movimentacao.valor = ui->spnValor->value();
    movimentacao.setTipo(this->getTipo());
    switch (movimentacao.tipo)
    {
    case TipoMovimentacao::Despesa:
        movimentacao.origem = ui->cmbPrim->currentText();
        movimentacao.destino = "";
        movimentacao.categoria = ui->cmbSecn->currentText();
        break;
    case TipoMovimentacao::Receita:
        movimentacao.origem = "";
        movimentacao.destino = ui->cmbPrim->currentText();;
        movimentacao.categoria = ui->cmbSecn->currentText();
        break;
    case TipoMovimentacao::Transferencia:
        movimentacao.origem = ui->cmbPrim->currentText();
        movimentacao.destino = ui->cmbSecn->currentText();
        movimentacao.categoria = "";
        break;
    }

    return movimentacao;
}

void MovimentacaoWidget::preencherInterface(const Movimentacao &movimentacao)
{
    ui->dateMovimentacao->setDate(movimentacao.data);
    ui->edtDescricao->setText(movimentacao.descricao);
    ui->spnValor->setValue(movimentacao.valor);
    ui->cmbPrim->setCurrentText(movimentacao.origem);
    ui->cmbSecn->setCurrentText(movimentacao.categoria);
}

void MovimentacaoWidget::setModo(Modo modo)
{
    m_modo = modo;
    QPushButton *botao = ui->bbMovimentacao->button(QDialogButtonBox::Save);

    switch (modo)
    {
    case Modo::Inserir:
        setWindowTitle("Nova " + this->getTipo());
        botao->setText("Salvar");
        break;

    case Modo::Editar:
        setWindowTitle("Editar " + this->getTipo());
        botao->setText("Atualizar");
        break;

    case Modo::Excluir:
        setWindowTitle("Excluir " + this->getTipo());
        ui->dateMovimentacao->setReadOnly(true);
        ui->edtDescricao->setReadOnly(true);
        ui->cmbTipo->setEnabled(false);
        ui->cmbPrim->setEnabled(false);
        ui->cmbSecn->setEnabled(false);
        ui->spnValor->setEnabled(false);
        botao->setText("Excluir");
        break;
    }
}

void MovimentacaoWidget::confirmar()
{
    switch (m_modo)
    {
    case Modo::Inserir:
        inserirMovimentacao();
        break;

    case Modo::Editar:
        atualizarMovimentacao();
        break;

    case Modo::Excluir:
        excluirMovimentacao();
        break;
    }
}

void MovimentacaoWidget::setId(int id)
{
    m_id = id;
    carregarMovimentacao();
}

void MovimentacaoWidget::carregarMovimentacao()
{
    MovimentacoesRepository repository;
    Movimentacao movimentacao = repository.buscarPorId(m_id);

    if (movimentacao.id == -1)
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }

    setTipo(movimentacao.getTipo());
    ui->cmbTipo->setCurrentIndex(ui->cmbTipo->findData(QVariant::fromValue(int(movimentacao.tipo))));
    atualizarInterface();

    preencherInterface(movimentacao);
}

void MovimentacaoWidget::inserirMovimentacao()
{
    MovimentacoesRepository repository;
    Movimentacao movimentacao = movimentacaoDaInterface();

    if (!repository.inserir(movimentacao))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void MovimentacaoWidget::atualizarMovimentacao()
{
    MovimentacoesRepository repository;
    Movimentacao movimentacao = movimentacaoDaInterface();
    movimentacao.id = m_id;

    if (!repository.atualizar(movimentacao))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void MovimentacaoWidget::excluirMovimentacao()
{
    MovimentacoesRepository repository;

    if (!repository.remover(m_id))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}
