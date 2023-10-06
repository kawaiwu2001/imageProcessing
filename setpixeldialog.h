#ifndef SETPIXELDIALOG_H
#define SETPIXELDIALOG_H

#include <QDialog>

namespace Ui {
class SetPixelDialog;
}

class SetPixelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPixelDialog(QWidget *parent = nullptr);
    ~SetPixelDialog();
    struct SetColor{
        int x;
        int y;
        int red;
        int green;
        int blue;
    };

public:
    SetColor setColor();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SetPixelDialog *ui;
    SetColor setcolor;
};

#endif // SETPIXELDIALOG_H
