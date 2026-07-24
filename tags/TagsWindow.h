#ifndef TAGSWINDOW_H
#define TAGSWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TagsWindow; }
QT_END_NAMESPACE

class TagsWindow : public QWidget {
    Q_OBJECT

public:
    explicit TagsWindow(QWidget *parent = nullptr);
    ~TagsWindow();

private slots:
    void on_btnNova_clicked();

private:
    Ui::TagsWindow *ui;
};

#endif // TAGSWINDOW_H
