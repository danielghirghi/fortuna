#include "TagWidget.h"
#include "ui_TagWidget.h"

TagWidget::TagWidget(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TagWidget){
    ui->setupUi(this);
    setWindowTitle("Nova Tag");
}

TagWidget::~TagWidget(){ delete ui; }
