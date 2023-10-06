#include "setpiexeldialog2.h"
#include "ui_setpiexeldialog2.h"

SetPiexelDialog2::SetPiexelDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPiexelDialog2)
{
    ui->setupUi(this);
}

SetPiexelDialog2::~SetPiexelDialog2()
{
    delete ui;
}

SetPiexelDialog2::SetColor2 SetPiexelDialog2::setColor2()
{
    return setcolor2;
}

void SetPiexelDialog2::on_buttonBox_accepted()
{
    setcolor2.x = ui->textEditX->toPlainText().toInt();
    setcolor2.y = ui->textEditY->toPlainText().toInt();
    setcolor2.gray = ui->textEditGray->toPlainText().toInt();

    close();
}


void SetPiexelDialog2::on_buttonBox_rejected()
{
    close();
}

