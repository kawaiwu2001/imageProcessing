#include "getpixelgdialog.h"
#include "ui_getpixelgdialog.h"
#include <QDebug>

GetPixelgDialog::GetPixelgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetPixelgDialog)
{
    ui->setupUi(this);
}

GetPixelgDialog::~GetPixelgDialog()
{
    delete ui;
}

GetPixelgDialog::Coordinate GetPixelgDialog::getCoor()
{
    return coor;
}

void GetPixelgDialog::on_buttonBox_accepted()
{
    coor.x = ui->textEditX->toPlainText().toInt();
    coor.y = ui->textEditY->toPlainText().toInt();

    close();

}

void GetPixelgDialog::on_buttonBox_rejected()
{
    close();
}



