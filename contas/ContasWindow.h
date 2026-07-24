#ifndef CONTASWINDOW_H
#define CONTASWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ContasWindow;
}
QT_END_NAMESPACE

class ContasWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ContasWindow(QWidget *parent = nullptr);
    ~ContasWindow();

private:
    Ui::ContasWindow *ui;
};

#endif // CONTASWINDOW_H
