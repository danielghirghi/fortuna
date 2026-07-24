#ifndef TAGDIALOG_H
#define TAGDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TagDialog; }
QT_END_NAMESPACE

class TagDialog : public QDialog {
    Q_OBJECT

public:
    explicit TagDialog(QWidget *parent = nullptr);
    ~TagDialog();

private:
    Ui::TagDialog *ui;
};

#endif // TAGDIALOG_H
