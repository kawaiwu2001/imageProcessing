#include "imageinterpolation.h"
#include "ui_imageinterpolation.h"

ImageInterpolation::ImageInterpolation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageInterpolation)
{
    ui->setupUi(this);
}

ImageInterpolation::~ImageInterpolation()
{
    delete ui;
}

ImageInterpolation::Scale ImageInterpolation::getScale()
{
    return scale;
}

void ImageInterpolation::on_pushButton_clicked()
{
    scale.Sx =  ui->textEditX->toPlainText().toDouble();
    scale.Sy =  ui->textEditY->toPlainText().toDouble();
    scale.fun = 0;
    close();
}


void ImageInterpolation::on_pushButton_2_clicked()
{
    scale.Sx =  ui->textEditX->toPlainText().toDouble();
    scale.Sy =  ui->textEditY->toPlainText().toDouble();
    scale.fun = 1;
    close();
}




void ImageInterpolation::on_pushButton_3_clicked()
{
    scale.Sx = -1;
    close();
}

