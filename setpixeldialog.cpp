#include "setpixeldialog.h"
#include "ui_setpixeldialog.h"

SetPixelDialog::SetPixelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPixelDialog)
{
    ui->setupUi(this);
}

SetPixelDialog::~SetPixelDialog()
{
    delete ui;
}

SetPixelDialog::SetColor SetPixelDialog::setColor()
{
    return setcolor;
}

void SetPixelDialog::on_buttonBox_accepted()
{
    setcolor.x = ui->textEditX->toPlainText().toInt();
    setcolor.y = ui->textEditY->toPlainText().toInt();
    setcolor.red = ui->textEditRed->toPlainText().toInt();
    setcolor.green = ui->textEditGeen->toPlainText().toInt();
    setcolor.blue = ui->textEditBlue->toPlainText().toInt();
    close();
}


void SetPixelDialog::on_buttonBox_rejected()
{
    close();
}

