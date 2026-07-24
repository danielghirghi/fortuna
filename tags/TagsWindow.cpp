#include "TagsWindow.h"
#include "ui_TagsWindow.h"

TagsWindow::TagsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TagsWindow)
{
    ui->setupUi(this);

    setWindowTitle("Tags");
}

TagsWindow::~TagsWindow()
{
    delete ui;
}
