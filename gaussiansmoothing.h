#ifndef GAUSSIANSMOOTHING_H
#define GAUSSIANSMOOTHING_H

#include <QDialog>

namespace Ui {
class GaussianSmoothing;
}

class GaussianSmoothing : public QDialog
{
    Q_OBJECT

public:
    explicit GaussianSmoothing(QWidget *parent = nullptr);
    ~GaussianSmoothing();


public:
    double getSigma();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GaussianSmoothing *ui;
    double sigma = -1;
};

#endif // GAUSSIANSMOOTHING_H
