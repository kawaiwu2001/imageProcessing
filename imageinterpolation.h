#ifndef IMAGEINTERPOLATION_H
#define IMAGEINTERPOLATION_H

#include <QDialog>

namespace Ui {
class ImageInterpolation;
}

class ImageInterpolation : public QDialog
{
    Q_OBJECT

public:
    explicit ImageInterpolation(QWidget *parent = nullptr);
    ~ImageInterpolation();
    struct Scale{
        double Sx;
        double Sy;
        int fun = -1; //0是最邻近,1是双线性
    };

public:
    Scale getScale();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ImageInterpolation *ui;
    Scale scale;
};

#endif // IMAGEINTERPOLATION_H
