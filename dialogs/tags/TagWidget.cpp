#include "TagWidget.h"
#include "ui_TagWidget.h"

#include "../../repositories/TagsRepository.h"

#include <qpushbutton.h>
#include <qsqlerror.h>
#include <qsqlquery.h>
#include <QMessageBox>

TagWidget::TagWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TagWidget)
{
    ui->setupUi(this);
    setWindowTitle("Nova Tag");

    connect(ui->bbTag, &QDialogButtonBox::accepted, this, &TagWidget::confirmar);
    connect(ui->bbTag, &QDialogButtonBox::rejected, this, &TagWidget::reject);
}

TagWidget::~TagWidget(){ delete ui; }

Tag TagWidget::tagDaInterface() const
{
    Tag tag;

    tag.nome  = ui->edtNome->text();
    tag.cor   = ui->edtCor->text();
    tag.ativo = ui->chkAtiva->isChecked();

    return tag;
}

void TagWidget::preencherInterface(const Tag &tag)
{
    ui->edtNome->setText(tag.nome);
    ui->edtCor->setText(tag.cor);
    ui->chkAtiva->setChecked(tag.ativo);
}

void TagWidget::setModo(Modo modo)
{
    m_modo = modo;
    QPushButton *botao = ui->bbTag->button(QDialogButtonBox::Save);

    switch (modo)
    {
    case Modo::Inserir:
        setWindowTitle("Nova Tag");
        botao->setText("Salvar");
        break;

    case Modo::Editar:
        setWindowTitle("Editar Tag");
        botao->setText("Atualizar");
        break;

    case Modo::Excluir:
        setWindowTitle("Excluir Tag");
        ui->edtNome->setReadOnly(true);
        ui->edtCor->setReadOnly(true);
        ui->chkAtiva->setEnabled(false);
        botao->setText("Excluir");
        break;
    }
}

void TagWidget::confirmar()
{
    switch (m_modo)
    {
    case Modo::Inserir:
        inserirTag();
        break;

    case Modo::Editar:
        atualizarTag();
        break;

    case Modo::Excluir:
        excluirTag();
        break;
    }
}

void TagWidget::setId(int id)
{
    m_id = id;
    carregarTag();
}

void TagWidget::carregarTag()
{
    TagsRepository repository;
    Tag tag = repository.buscarPorId(m_id);

    if (tag.id == -1)
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }

    preencherInterface(tag);
}

void TagWidget::inserirTag()
{
    TagsRepository repository;
    Tag tag = tagDaInterface();

    if(!repository.inserir(tag))
    {
        QMessageBox::warning( this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void TagWidget::atualizarTag()
{
    TagsRepository repository;
    Tag tag = tagDaInterface();
    tag.id = m_id;

    if (!repository.atualizar(tag))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}

void TagWidget::excluirTag()
{
    TagsRepository repository;

    if (!repository.remover(m_id))
    {
        QMessageBox::warning(this, "Erro", repository.lastError());
        return;
    }
    accept();
}
