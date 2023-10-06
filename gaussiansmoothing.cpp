#include "gaussiansmoothing.h"
#include "ui_gaussiansmoothing.h"

GaussianSmoothing::GaussianSmoothing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianSmoothing)
{
    ui->setupUi(this);
}

GaussianSmoothing::~GaussianSmoothing()
{
    delete ui;
}

double GaussianSmoothing::getSigma()
{
    return sigma;
}

void GaussianSmoothing::on_pushButton_clicked()
{
    sigma = ui->textEdit->toPlainText().toInt();
    close();
}

