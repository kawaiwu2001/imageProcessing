#ifndef IMPULSENOISE_H
#define IMPULSENOISE_H

#include <QDialog>

namespace Ui {
class ImpulseNoise;
}

class ImpulseNoise : public QDialog
{
    Q_OBJECT

public:
    explicit ImpulseNoise(QWidget *parent = nullptr);
    ~ImpulseNoise();
    struct Noise{
        double rate;
        int fun = -1;
    };

public:
    Noise getNoise();
private slots:
    void on_pushButton_clicked();

    void on_pushButton2_clicked();

private:
    Ui::ImpulseNoise *ui;
    Noise noise;
};

#endif // IMPULSENOISE_H
