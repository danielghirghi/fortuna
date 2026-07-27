#ifndef RECEITAWIDGET_H
#define RECEITAWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ReceitaWidget; }
QT_END_NAMESPACE

class ReceitaWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ReceitaWidget(QWidget *parent = nullptr);
    ~ReceitaWidget();
    void setId(int id);

private slots:
    void salvar();
    void inserirReceita();
    void atualizarReceita();

private:
    int m_id = -1;
    void carregarReceita();
    Ui::ReceitaWidget *ui;
};

#endif // RECEITAWIDGET_H
