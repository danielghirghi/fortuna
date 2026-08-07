#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    using QWidget::QWidget;

    virtual void refresh() = 0;
};

#endif // BASEWIDGET_H
