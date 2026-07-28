#ifndef CONTACONFIRMDIALOG_H
#define CONTACONFIRMDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ContaConfirmDialog; }
QT_END_NAMESPACE

class ContaConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContaConfirmDialog(QWidget *parent = nullptr);
    ~ContaConfirmDialog();
    void setId(int id);

private slots:
    void Remover();

private:
    int m_id = -1;
    void carregarConta();
    Ui::ContaConfirmDialog *ui;
};

#endif // CONTACONFIRMDIALOG_H
