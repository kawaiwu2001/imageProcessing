#ifndef GETPIXELGDIALOG_H
#define GETPIXELGDIALOG_H

#include <QDialog>

namespace Ui {
class GetPixelgDialog;
}

class GetPixelgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetPixelgDialog(QWidget *parent = nullptr);
    ~GetPixelgDialog();

    struct Coordinate{
        int x;
        int y;
    };

public:
    Coordinate getCoor();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();



private:
    Ui::GetPixelgDialog *ui;
    Coordinate coor;
};

#endif // GETPIXELGDIALOG_H
