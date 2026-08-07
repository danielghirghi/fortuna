#include "CategoriaWidget.h"
#include "ui_CategoriaWidget.h"

#include "../../repositories/CategoriasRepository.h"

#include <qpushbutton.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

CategoriaWidget::CategoriaWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::CategoriaWidget)
{
        ui->setupUi(this);

        connect(ui->bbCategoria, &QDialogButtonBox::accepted, this, &CategoriaWidget::confirmar);
        connect(ui->bbCategoria, &QDialogButtonBox::rejected, this, &CategoriaWidget::reject);
}

CategoriaWidget::~CategoriaWidget(){ delete ui; }

Categoria CategoriaWidget::categoriaDaInterface() const
{
    Categoria categoria;

    categoria.nome = ui->edtNome->text();
    categoria.grupo = ui->cmbGrupo->currentText();
    categoria.tipo = ui->cmbTipo->currentText();
    categoria.ativo = ui->chkAtiva->isChecked();

    return categoria;
}

void CategoriaWidget::preencherInterface(const Categoria &categoria)
{
    ui->edtNome->setText(categoria.nome);
    ui->cmbGrupo->setCurrentText(categoria.grupo);
    ui->cmbTipo->setCurrentText(categoria.tipo);
    ui->chkAtiva->setChecked(categoria.ativo);
}

void CategoriaWidget::setModo(Modo modo)
{
    m_modo = modo;
    QPushButton *botao = ui->bbCategoria->button(QDialogButtonBox::Save);

    switch (modo)
    {
    case Modo::Inserir:
        setWindowTitle("Nova Categoria");
        botao->setText("Salvar");
        break;

    case Modo::Editar:
        setWindowTitle("Editar Categoria");
        botao->setText("Atualizar");
        break;

    case Modo::Excluir:
        setWindowTitle("Excluir Categoria");
        ui->edtNome->setReadOnly(true);
        ui->cmbGrupo->setEnabled(false);
        ui->cmbTipo->setEnabled(false);
        ui->chkAtiva->setEnabled(false);
        botao->setText("Excluir");
        break;
    }
}

void CategoriaWidget::confirmar()
{
    switch (m_modo)
    {
    case Modo::Inserir:
        inserirCategoria();
        break;

    case Modo::Editar:
        atualizarCategoria();
        break;

    case Modo::Excluir:
        excluirCategoria();
        break;
    }
}

void CategoriaWidget::setId(int id)
{
    m_id = id;
    carregarCategoria();
}

void CategoriaWidget::carregarCategoria()
{
    CategoriasRepository repository;
    Categoria categoria = repository.buscarPorId(m_id);

    if (categoria.id == -1)
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    preencherInterface(categoria);
}

void CategoriaWidget::inserirCategoria()
{
    CategoriasRepository repository;
    Categoria categoria = categoriaDaInterface();

    if (!repository.inserir(categoria))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void CategoriaWidget::atualizarCategoria()
{
    CategoriasRepository repository;
    Categoria categoria = categoriaDaInterface();
    categoria.id = m_id;

    if (!repository.atualizar(categoria))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void CategoriaWidget::excluirCategoria()
{
    CategoriasRepository repository;

    if (!repository.remover(m_id))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}
