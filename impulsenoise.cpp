#include "impulsenoise.h"
#include "ui_impulsenoise.h"

ImpulseNoise::ImpulseNoise(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImpulseNoise)
{
    ui->setupUi(this);
}

ImpulseNoise::~ImpulseNoise()
{
    delete ui;
}

ImpulseNoise::Noise ImpulseNoise::getNoise()
{
    return noise;
}


void ImpulseNoise::on_pushButton_clicked()
{
    noise.rate = ui->textEdit->toPlainText().toDouble();
    noise.fun = 0;
    close();
}


void ImpulseNoise::on_pushButton2_clicked()
{
    noise.rate = ui->textEdit->toPlainText().toDouble();
    noise.fun = 1;
    close();
}

