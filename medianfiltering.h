#ifndef MEDIANFILTERING_H
#define MEDIANFILTERING_H

#include <QDialog>

namespace Ui {
class MedianFiltering;
}

class MedianFiltering : public QDialog
{
    Q_OBJECT

public:
    explicit MedianFiltering(QWidget *parent = nullptr);
    ~MedianFiltering();
public:
    int getFilter();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MedianFiltering *ui;
    int filter;
};

#endif // MEDIANFILTERING_H
