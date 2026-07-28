#ifndef TAGCONFIRMDIALOG_H
#define TAGCONFIRMDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TagConfirmDialog; }
QT_END_NAMESPACE

class TagConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TagConfirmDialog(QWidget *parent = nullptr);
    ~TagConfirmDialog();
    void setId(int id);

private slots:
    void Remover();

private:
    int m_id = -1;
    void carregarTag();
    Ui::TagConfirmDialog *ui;
};

#endif // TAGCONFIRMDIALOG_H
