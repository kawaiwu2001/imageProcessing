#include "sharpening.h"
#include "ui_sharpening.h"

Sharpening::Sharpening(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sharpening)
{
    ui->setupUi(this);
}

Sharpening::~Sharpening()
{
    delete ui;
}

Sharpening::Sharpen Sharpening::getSharpen()
{
    return sharpen;
}


void Sharpening::on_pushButton_clicked()
{
    sharpen.k1 = ui->textEdit->toPlainText().toDouble();
    sharpen.k2 = ui->textEdit2->toPlainText().toDouble();
    close();
}

