#ifndef TAGSWIDGET_H
#define TAGSWIDGET_H

#include "../models/BaseWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TagsWidget; }
QT_END_NAMESPACE

class TagsWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit TagsWidget(QWidget *parent = nullptr);
    ~TagsWidget();
    void refresh();

private slots:
    void carregarTags();
    void on_btnNova_clicked();
    void on_btnEditar_clicked();
    void on_btnExcluir_clicked();

private:
    Ui::TagsWidget *ui;
};

#endif // TAGSWIDGET_H
