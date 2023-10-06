#ifndef SHARPENING_H
#define SHARPENING_H

#include <QDialog>

namespace Ui {
class Sharpening;
}

class Sharpening : public QDialog
{
    Q_OBJECT

public:
    explicit Sharpening(QWidget *parent = nullptr);
    ~Sharpening();
    struct Sharpen{
        double k1 = -1;
        double k2 = -1;
    };

public:
    Sharpen getSharpen();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Sharpening *ui;
    Sharpen sharpen;
};

#endif // SHARPENING_H
