#ifndef CATEGORIACONFIRMDIALOG_H
#define CATEGORIACONFIRMDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriaConfirmDialog; }
QT_END_NAMESPACE

class CategoriaConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CategoriaConfirmDialog(QWidget *parent = nullptr);
    ~CategoriaConfirmDialog();
    void setId(int id);

private slots:
    void Remover();

private:
    int m_id = -1;
    void carregarCategoria();
    Ui::CategoriaConfirmDialog *ui;
};

#endif // CATEGORIACONFIRMDIALOG_H
