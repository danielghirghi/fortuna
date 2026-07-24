#include "TagsWindow.h"
#include "ui_TagsWindow.h"

#include "TagDialog.h"

TagsWindow::TagsWindow(QWidget *parent) : QWidget(parent)
    , ui(new Ui::TagsWindow){
    ui->setupUi(this);

    setWindowTitle("Tags");
}

TagsWindow::~TagsWindow() { delete ui; }

void TagsWindow::on_btnNova_clicked(){
    auto *janela = new TagDialog(nullptr);
    janela->show();
}
