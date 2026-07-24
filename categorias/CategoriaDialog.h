#ifndef CATEGORIADIALOG_H
#define CATEGORIADIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class CategoriaDialog; }
QT_END_NAMESPACE

class CategoriaDialog : public QDialog {
    Q_OBJECT

public:
    explicit CategoriaDialog(QWidget *parent = nullptr);
    ~CategoriaDialog();

private:
    Ui::CategoriaDialog *ui;
};

#endif // CATEGORIADIALOG_H
