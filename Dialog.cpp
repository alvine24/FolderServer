#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_buttonBox_clicked()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_clicked(){
    myFolder.uploadFolder(ui->lineEdit->text(), "");
}
