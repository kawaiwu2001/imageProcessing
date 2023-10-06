#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bmp.h"
#include "getpixelgdialog.h"
#include "setpixeldialog.h"
#include "setpiexeldialog2.h"
#include "imageinterpolation.h"
#include "gaussiansmoothing.h"
#include "sharpening.h"
#include "impulsenoise.h"
#include "medianfiltering.h"
#include <QMainWindow>
//#include "dialogcolordisplay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    int reImage();

    void on_actionOpen_BMP_file_triggered();

    void on_actionSave_to_new_BMP_file_triggered();

    void on_actionDisplay_file_header_triggered();

    void on_actionGet_pixel_value_triggered();

    void on_actionSet_pixel_value_triggered();

    void on_actionImage_interpolation_triggered();

    void on_actionMedian_filtering_triggered();

    void on_actionGaussian_smoothing_triggered();

    void on_actionHistogram_equalization_triggered();

    void on_actionSharpening_by_gradient_triggered();

    void on_actionBilateral_filtering_triggered();

    void on_actionAdd_impulse_noise_triggered();

    void on_actionCanny_edge_detection_triggered();

    void on_actionSnake_image_segmentation_triggered();

private:
    BMP* bmp;
    Ui::MainWindow *ui;
    GetPixelgDialog *getPixelDialog;
    SetPixelDialog *setPixelDialog;
    SetPiexelDialog2 *setPiexelDialog2;
    ImageInterpolation *imageInterpolation;
    GaussianSmoothing *gaussianSmoothing;
    Sharpening *sharpening;
    ImpulseNoise *impulseNoise;
    MedianFiltering *medianFiltering;
    //DialogColorDisplay *dialogColorDisplay;
};
#endif // MAINWINDOW_H
