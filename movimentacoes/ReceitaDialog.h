#ifndef RECEITADIALOG_H
#define RECEITADIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ReceitaDialog; }
QT_END_NAMESPACE

class ReceitaDialog : public QDialog {
    Q_OBJECT

public:
    explicit ReceitaDialog(QWidget *parent = nullptr);
    ~ReceitaDialog();

private:
    Ui::ReceitaDialog *ui;
};

#endif // RECEITADIALOG_H
