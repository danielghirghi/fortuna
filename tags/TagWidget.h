#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TagWidget; }
QT_END_NAMESPACE

class TagWidget : public QDialog {
    Q_OBJECT

public:
    explicit TagWidget(QWidget *parent = nullptr);
    ~TagWidget();

private:
    Ui::TagWidget *ui;
};

#endif // TAGWIDGET_H
