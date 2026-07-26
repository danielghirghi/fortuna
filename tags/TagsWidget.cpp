#include "TagsWidget.h"
#include "ui_TagsWidget.h"

#include "TagWidget.h"

TagsWidget::TagsWidget(QWidget *parent) : QWidget(parent)
    , ui(new Ui::TagsWidget){
    ui->setupUi(this);

    setWindowTitle("Tags");
}

TagsWidget::~TagsWidget() { delete ui; }

void TagsWidget::on_btnNova_clicked(){
    auto *janela = new TagWidget(nullptr);
    janela->show();
}
