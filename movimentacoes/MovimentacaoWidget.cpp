#include "MovimentacaoWidget.h"
#include "ui_MovimentacaoWidget.h"

#include "../repositories/MovimentacoesRepository.h"

#include "../repositories/ContasRepository.h"
#include "../repositories/CategoriasRepository.h"

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

    connect(ui->bbMovimentacao, &QDialogButtonBox::accepted, this, &MovimentacaoWidget::confirmar);
    connect(ui->bbMovimentacao, &QDialogButtonBox::rejected, this, &MovimentacaoWidget::reject);
}

MovimentacaoWidget::~MovimentacaoWidget(){ delete ui; }

QString MovimentacaoWidget::getTipo() const
{
    switch (MovimentacaoWidget::tipo)
    {
    case TipoMovWdgt::Receita:
        return "RENDA";
    case TipoMovWdgt::Despesa:
        return "DESPESA";
    case TipoMovWdgt::Transferencia:
        return "TRANSFERENCIA";
    }
    return "ERRO";
}

void MovimentacaoWidget::setTipo(QString tipo)
{
    if (tipo == "RENDA" || tipo == "RECEITA")
    {
        MovimentacaoWidget::tipo = TipoMovWdgt::Receita;
        return;
    }
    if (tipo =="DESPESA")
    {
        MovimentacaoWidget::tipo = TipoMovWdgt::Despesa;
        return;
    }
    if (tipo =="TRANSFERENCIA")
    {
        MovimentacaoWidget::tipo = TipoMovWdgt::Transferencia;
        return;
    }
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
    ContasRepository contasrepo;
    QList<Conta> contas = contasrepo.listar();
    if (!contasrepo.lastError().isEmpty())
    {
        QMessageBox::warning( this, "Erro", contasrepo.lastError());
        return;
    }
    for (const Conta &conta : contas){ ui->cmbPrim->addItem(conta.nome); }

    if (this->tipo == TipoMovWdgt::Transferencia)
    {
        ui->lblSecn->setText("Conta Destino:");
        for (const Conta &conta : contas)
        { ui->cmbSecn->addItem(conta.nome); }
    }
    else
    {

        if (this->tipo == TipoMovWdgt::Receita)
        {
            ui->lblPrim->setText("Conta Destino:");
        }
        CategoriasRepository catrepo;
        QList<Categoria> categorias = catrepo.listar();
        if (!catrepo.lastError().isEmpty())
        {
            QMessageBox::warning( this, "Erro", catrepo.lastError());
            return;
        }
        for (const Categoria &categoria : categorias)
        { ui->cmbSecn->addItem(categoria.nome); }
    }

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
