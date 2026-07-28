#ifndef MOVIMENTACAOCONFIRMDIALOG_H
#define MOVIMENTACAOCONFIRMDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MovimentacaoConfirmDialog; }
QT_END_NAMESPACE

class MovimentacaoConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MovimentacaoConfirmDialog(QWidget *parent = nullptr);
    ~MovimentacaoConfirmDialog();
    void setId(int id);

private slots:
    void Remover();

private:
    int m_id = -1;
    void carregarMovimentacao();
    Ui::MovimentacaoConfirmDialog *ui;
};

#endif // MOVIMENTACAOCONFIRMDIALOG_H
