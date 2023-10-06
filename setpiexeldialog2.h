#ifndef SETPIEXELDIALOG2_H
#define SETPIEXELDIALOG2_H

#include <QDialog>

namespace Ui {
class SetPiexelDialog2;
}

class SetPiexelDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit SetPiexelDialog2(QWidget *parent = nullptr);
    ~SetPiexelDialog2();
    struct SetColor2{
        int x;
        int y;
        int gray;
    };

public:
    SetColor2 setColor2();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::SetPiexelDialog2 *ui;
    SetColor2 setcolor2;
};

#endif // SETPIEXELDIALOG2_H
