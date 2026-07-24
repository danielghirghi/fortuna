#ifndef TagSWINDOW_H
#define TagSWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class TagsWindow;
}
QT_END_NAMESPACE

class TagsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TagsWindow(QWidget *parent = nullptr);
    ~TagsWindow();

private:
    Ui::TagsWindow *ui;
};

#endif // TagSWINDOW_H
