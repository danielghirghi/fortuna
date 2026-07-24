#include "TagDialog.h"
#include "ui_TagDialog.h"

TagDialog::TagDialog(QWidget *parent) : QDialog(parent)
    , ui(new Ui::TagDialog){
    ui->setupUi(this);
    setWindowTitle("Nova Tag");
}

TagDialog::~TagDialog(){ delete ui; }
