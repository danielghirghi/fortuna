#ifndef DESPESAWIDGET_H
#define DESPESAWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DespesaWidget; }
QT_END_NAMESPACE

class DespesaWidget : public QDialog
{
    Q_OBJECT

public:
    explicit DespesaWidget(QWidget *parent = nullptr);
    ~DespesaWidget();
    void setId(int id);

private slots:
    void salvar();
    void inserirDespesa();
    void atualizarDespesa();

private:
    int m_id = -1;
    void carregarDespesa();
    Ui::DespesaWidget *ui;
};

#endif // DESPESAWIDGET_H
