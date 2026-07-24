#ifndef TRANSFERENCIADIALOG_H
#define TRANSFERENCIADIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TransferenciaDialog; }
QT_END_NAMESPACE

class TransferenciaDialog : public QDialog {
    Q_OBJECT

public:
    explicit TransferenciaDialog(QWidget *parent = nullptr);
    ~TransferenciaDialog();

private:
    Ui::TransferenciaDialog *ui;
};

#endif // TRANSFERENCIADIALOG_H
