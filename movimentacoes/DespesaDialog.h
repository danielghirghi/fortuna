#ifndef DESPESADIALOG_H
#define DESPESADIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DespesaDialog; }
QT_END_NAMESPACE

class DespesaDialog : public QDialog {
    Q_OBJECT

public:
    explicit DespesaDialog(QWidget *parent = nullptr);
    ~DespesaDialog();

private:
    Ui::DespesaDialog *ui;
};

#endif // DESPESADIALOG_H
