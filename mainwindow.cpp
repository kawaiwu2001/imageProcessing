#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include "bmp.h"
#include "processing.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->bmp = new BMP;
}


MainWindow::~MainWindow()
{

    delete ui;
    delete this->bmp;
}

int MainWindow::reImage()
{
    QString tmp_file = "d:\\tmp.bmp";
    bmp->save_as(tmp_file);

    QImage img(tmp_file);
    this->ui->label_pic->resize(img.width(),img.height());
    this->ui->label_pic->setPixmap(QPixmap::fromImage(img));

    return 0;
}


void MainWindow::on_actionOpen_BMP_file_triggered()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open Image"),QDir::homePath(),tr("(*.bmp)"));
    qDebug()<<"filename:"<<filename;
    QPixmap image=QPixmap(filename);
   // qDebug()<<"image:"<<image;
    bmp->open(filename);
    if(!image.isNull())
    {
        //QMessageBox::warning(NULL, "Error", "图片打开成功!");
        ui->label_pic->setScaledContents(true);
        ui->label_pic->setPixmap(image);
    }else{
        QMessageBox::warning(NULL, "Error", "图片打开失败!");
        return;
    }
    //reImage();
}


void MainWindow::on_actionSave_to_new_BMP_file_triggered()
{
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.bmp)")); //选择路径
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(ui->label_pic->winId()).save(filename1);

}


void MainWindow::on_actionDisplay_file_header_triggered()
{
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
    QString str;
    BITMAPFILEHEADER& fh = bmp->bmpHead;
    BITMAPINFOHEADER& ih = bmp->bmpInforHead;
    if(fh.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }

    str += "bfType (file type) = " + QString().setNum(fh.bfType, 16);
    str += "\nbfSize (file length) = " + QString().setNum(fh.bfSize);
    str += "\nbfOffBits (offset of bitmap data in bytes) = " + QString().setNum(fh.bfOffBits);
    str += "\nbiSize (header structure length should be 40 or 0x28) = " + QString().setNum(ih.biSize);
    str += "\nbiWidth (image width) = " + QString().setNum(ih.biWidth);
    str += "\nbiHeight (image height) = " + QString().setNum(ih.biHeight);
    str += "\nbiPlanes (must equal to 1) = " + QString().setNum(ih.biPlanes);
    str += "\nbiBitCount (color/pixel bits) = " + QString().setNum(ih.biBitCount);
    str += "\nbiCompression (compressed?) = " + QString().setNum(ih.biCompression);
    str += "\nbiSizeImage (length of bitmap data in bytes must be the times of 4) = " + QString().setNum(ih.biSizeImage);
    str += "\nbiXPelsPerMeter (horizontal resolution of target device in pixels/metre) = " + QString().setNum(ih.biXPelsPerMeter);
    str += "\nbiYPelsPerMeter (vertical resolution of target device in pixels/metre) = " + QString().setNum(ih.biYPelsPerMeter);
    str += "\nbiClrUsed (number of colors used in bitmap,0=2**biBitCount) = " + QString().setNum(ih.biClrUsed);
    str += "\nbiClrImportant (number of important colors,0=all colors are important) = " + QString().setNum(ih.biClrImportant);
    str += "\n\nThe following is additional infomation:";
    str += "\nBytes per row in bitmap(nBytesPerRow) = " + QString().setNum(bmp->bytesPerLine);
    str += "\nTotal bytes of bitmap(nImageSizeInByte) = " + QString().setNum(bmp->height * bmp->bytesPerLine);
    str += "\nActual pixels per raw in bitmap(nPixelsPerRow) = " + QString().setNum(ih.biWidth);
    str += "\nTotal rows of bitmap(nTotalRows) = " + QString().setNum(ih.biHeight);
    str += "\nTotal colors(2**biBitCount)(nTotalColors) = " + QString().setNum(1 << ih.biBitCount);
    str += "\nUsed colors(biColorUsed)(nUsedColors) = " + QString().setNum(ih.biClrUsed);
    QMessageBox::information(NULL, "Info", str);
}


void MainWindow::on_actionGet_pixel_value_triggered()
{
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }else{
        getPixelDialog = new GetPixelgDialog(this);
        getPixelDialog->exec();
        auto coor = getPixelDialog->getCoor();
        int x = coor.x;
        int y = coor.y;
        //qDebug()<<"X:"<<coor.x;
        if(!(0<=x && x<=bmp->width && 0<=y && y<=bmp->height)){
            QMessageBox::warning(NULL, "Error", "Invalid coordinate!");
            return;
        }
        QString str;
        str += "HEX: #";
        if(bmp->bitsPerPixel == 8){
            BYTE gray = bmp->a[x][y];


            str += QString().sprintf("%.2X%.2X%.2X\n", gray, gray, gray);
            str += "RED: "+QString().setNum(gray);
            str += "\nGREEN: "+QString().setNum(gray);
            str += "\nBLUE: "+QString().setNum(gray);

           }else{
               RGBQUAD rgb = bmp->b[x][y];


              str += QString().sprintf("%.2X%.2X%.2X\n", rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
              str += "RED: "+QString().setNum(rgb.rgbRed);
              str += "\nGREEN: "+QString().setNum(rgb.rgbGreen);
              str += "\nBLUE: "+QString().setNum(rgb.rgbBlue);
           }
        QMessageBox::information(NULL, "Info", str);
    }



}


void MainWindow::on_actionSet_pixel_value_triggered()
{
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }

    if(bmp->bitsPerPixel == 8){
        setPiexelDialog2 = new SetPiexelDialog2(this);
        setPiexelDialog2->exec();
        auto set = setPiexelDialog2->setColor2();
        int x = set.x;
        int y = set.y;
        int gray = set.gray;
        if(!(0<=gray && gray<=255)){
            QMessageBox::warning(NULL, "Error", "Invalid value!");
            return;
        }

        bmp->a[y][x] = gray;

    }else{
        setPixelDialog = new SetPixelDialog(this);
        setPixelDialog->exec();
        auto set = setPixelDialog->setColor();
        int x = set.x;
        int y = set.y;
        if(!(0<=x && x<=bmp->width && 0<=y && y<=bmp->height)){
            QMessageBox::warning(NULL, "Error", "Invalid coordinate!");
            return;
        }
        int red = set.red;
        int green = set.green;
        int blue = set.blue;
        qDebug()<<"red:"<<set.red;
        if(!(0<=blue && blue<=255 && 0<=green && green<=255 && 0<=red && red<=255)){
            QMessageBox::warning(NULL, "Error", "Invalid value!");
            return;
        }
        RGBQUAD& rgb = this->bmp->b[y][x];
        rgb.rgbRed = red;
        rgb.rgbGreen = green;
        rgb.rgbBlue = blue;
    }
    reImage();
}


void MainWindow::on_actionImage_interpolation_triggered()
{
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
     if(bmp->bitsPerPixel == 8){
         imageInterpolation = new ImageInterpolation(this);
         imageInterpolation->exec();
         auto scale = imageInterpolation->getScale();

         double sx = scale.Sx;
         double sy = scale.Sy;
         int fun = scale.fun;

         BMP* pnew;
         if(fun == 0){
             pnew = nearest_neighbor(this->bmp, sx, sy);
         }else if (fun == 1){
             pnew = bilinear(this->bmp, sx, sy);
         }else{
             return;
         }
         delete this->bmp;
         this->bmp = pnew;
         this->reImage();

     }else{

         QMessageBox::warning(NULL, "Error", "Only grey-scale map!");
         return;
     }


}


void MainWindow::on_actionMedian_filtering_triggered()
{

    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
    if(bmp->bitsPerPixel == 8){
        medianFiltering = new MedianFiltering(this);
        medianFiltering->exec();
        int filter = medianFiltering->getFilter();
        if(filter<3 || !(filter%2)){ //要奇数
            QMessageBox::warning(NULL, "Error", "only odd number!");
            return;
        }
        BMP* pnew = median_filtering(this->bmp, filter);
        delete this->bmp;
        this->bmp = pnew;
        this->reImage();
    }else{
        QMessageBox::warning(NULL, "Error", "Only grey-scale map!");
        return;
    }

}


void MainWindow::on_actionGaussian_smoothing_triggered()
{
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
    if(bmp->bitsPerPixel == 8){
        gaussianSmoothing = new GaussianSmoothing(this);
        gaussianSmoothing->exec();

        double sigma = gaussianSmoothing->getSigma();
        if(sigma == -1){
            return;
        }
        BMP* pnew = gaussian_smoothing(this->bmp, sigma);

        delete this->bmp;
        this->bmp = pnew;
        this->reImage();
    }else{
        QMessageBox::warning(NULL, "Error", "Only grey-scale map!");
        return;
    }
}


void MainWindow::on_actionHistogram_equalization_triggered()
{
    //不用dialog
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
    if(bmp->bitsPerPixel == 8){
        BMP* pnew = histogram_equalization(this->bmp);

        delete this->bmp;
        this->bmp = pnew;
        this->reImage();
    }else{
        QMessageBox::warning(NULL, "Error", "Only grey-scale map!");
        return;
    }

}


void MainWindow::on_actionSharpening_by_gradient_triggered()
{
    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
    if(bmp->bitsPerPixel == 8){
        sharpening = new Sharpening(this);
        sharpening->exec();
        auto data = sharpening->getSharpen();
        double k1 = data.k1;
        double k2 = data.k2;
        if(k1>=1 || k1<=0 || k2<0){
            QMessageBox::warning(NULL, "Error", "Invalid value!");
            return;
        }
        BMP* pnew = sharpening_sobel(this->bmp,k1,k2);
        delete this->bmp;
        this->bmp = pnew;
        this->reImage();
    }else{
        QMessageBox::warning(NULL, "Error", "Only grey-scale map!");
        return;
    }

}


void MainWindow::on_actionBilateral_filtering_triggered()
{
    QMessageBox::warning(NULL, "Info", "未完成!");
}


void MainWindow::on_actionAdd_impulse_noise_triggered()
{

    if(bmp->bmpHead.bfType == 0){
        QMessageBox::warning(NULL,"Error","Please open image!");
        return;
    }
    if(bmp->bitsPerPixel == 8){
        impulseNoise = new ImpulseNoise(this);
        impulseNoise->exec();
        auto noise = impulseNoise->getNoise();
        double rate = noise.rate;
        int fun = noise.fun;
        if(rate>=0 && rate<=1){
            if(fun == 0){
                BMP* pnew = impulsive_noise_salt(this->bmp, rate);
                delete this->bmp;
                this->bmp = pnew;
                this->reImage();
            }else if(fun == 1){
                BMP* pnew = impulsive_noise_random(this->bmp, rate);
                delete this->bmp;
                this->bmp = pnew;
                this->reImage();
            }else{
                return;
            }
        }else{
            QMessageBox::warning(NULL, "Error", "Invalid value!");
            return;
        }


    }else{
        QMessageBox::warning(NULL, "Error", "Only grey-scale map!");
        return;
    }

}


void MainWindow::on_actionCanny_edge_detection_triggered()
{
    QMessageBox::warning(NULL, "Info", "未完成!");
}


void MainWindow::on_actionSnake_image_segmentation_triggered()
{
    QMessageBox::warning(NULL, "Info", "未完成!");
}

