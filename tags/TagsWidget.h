#ifndef TAGSWIDGET_H
#define TAGSWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TagsWidget; }
QT_END_NAMESPACE

class TagsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagsWidget(QWidget *parent = nullptr);
    ~TagsWidget();

private slots:
    void carregarTags();
    void on_btnNova_clicked();
    void on_btnEditar_clicked();

private:
    Ui::TagsWidget *ui;
};

#endif // TAGSWIDGET_H
