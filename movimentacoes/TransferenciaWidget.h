#ifndef TRANSFERENCIAWIDGET_H
#define TRANSFERENCIAWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TransferenciaWidget; }
QT_END_NAMESPACE

class TransferenciaWidget : public QDialog {
    Q_OBJECT

public:
    explicit TransferenciaWidget(QWidget *parent = nullptr);
    ~TransferenciaWidget();

private slots:
    void salvar();

private:
    Ui::TransferenciaWidget *ui;
};

#endif // TRANSFERENCIAWIDGET_H
