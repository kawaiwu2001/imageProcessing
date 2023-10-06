#include "medianfiltering.h"
#include "ui_medianfiltering.h"

MedianFiltering::MedianFiltering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianFiltering)
{
    ui->setupUi(this);
}

MedianFiltering::~MedianFiltering()
{
    delete ui;
}

int MedianFiltering::getFilter()
{
    return filter;
}

void MedianFiltering::on_pushButton_clicked()
{
    filter =  ui->textEdit->toPlainText().toInt();
    close();
}

