#ifndef CategoriaSWINDOW_H
#define CategoriaSWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class CategoriasWindow;
}
QT_END_NAMESPACE

class CategoriasWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriasWindow(QWidget *parent = nullptr);
    ~CategoriasWindow();

private:
    Ui::CategoriasWindow *ui;
};

#endif // CategoriaSWINDOW_H
