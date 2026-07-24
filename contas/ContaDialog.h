#ifndef CONTADIALOG_H
#define CONTADIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ContaDialog; }
QT_END_NAMESPACE

class ContaDialog : public QDialog {
    Q_OBJECT

public:
    explicit ContaDialog(QWidget *parent = nullptr);
    ~ContaDialog();

private:
    Ui::ContaDialog *ui;
};

#endif // CONTADIALOG_H
