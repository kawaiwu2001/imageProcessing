#include "bmp.h"
#include <cmath>
#include <QDebug>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
const int N = 2048;
bool flag[N];

void bubble_sort(int* arr,int num){
    for(int i = 0;i < num-1;i++){
        for(int j = 0; j < num-i-1; j++){
            if(arr[j] > arr[j+1]){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

BMP* median_filtering(BMP* p, int filter){

    BMP* pnew = new BMP;
    int center = filter/2;
    int height = p->height;
    int width = p->width;
    pnew->create_gray_bmp(p->width, p->height);
    int *array = (int*)malloc(sizeof(int)*filter*filter);
    for (int i = center; i< height-center; i++){
        for(int j = center; j<width - center; j++){
            int num = 0;
            for(int m = -1*center; m<=center; m++){
                for(int n = -1*center; n<=center; n++){
                    array[num] = p->a[i+m][j+n];
                    num++;
                }
            }
            bubble_sort(array,filter*filter);
            pnew->a[i][j] = array[(filter*filter - 1)/2];
        }

    }
    free(array);
    return pnew;
}

BMP* nearest_neighbor(BMP* p, double sx, double sy){
    BMP* pnew = new BMP;
    pnew->create_gray_bmp(int(sx * p->width), int(sy * p->height));

    double sx_reci = 1/sx;
    double sy_reci = 1/sy;
    for(int y=0; y<pnew->height; y++){
        for(int x=0; x<pnew->width; x++){
            int a = (int)(sx_reci * x);
            int b = (int)(sy_reci * y);
            pnew->a[y][x] = p->a[b][a];
        }
    }

    return pnew;
}

BMP* bilinear(BMP* p, double sx, double sy){
    BMP* pnew = new BMP;
    pnew->create_gray_bmp(int(sx * p->width), int(sy * p->height));

    double sx_reci = 1/sx;
    double sy_reci = 1/sy;
    for(int y=0; y<pnew->height; y++){
        for(int x=0; x<pnew->width; x++){
            double _x = sx_reci * x;
            double _y = sy_reci * y;
            int x_floor = (int)floor(_x);
            int x_ceil = (int)ceil(_x);
            if(x_ceil > p->width) x_ceil = x_floor;
            int y_floor = (int)floor(_y);
            int y_ceil = (int)ceil(_y);
            if(y_ceil > p->height) y_ceil = y_floor;
            BYTE g1 = p->a[y_floor][x_floor];
            BYTE g2 = p->a[y_ceil][x_floor];
            BYTE g3 = p->a[y_floor][x_ceil];
            BYTE g4 = p->a[y_ceil][x_ceil];
            double dx = _x - x_floor;
            double dy = _y - y_floor;
            double ga = g1 + dy*(g2 - g1);
            double gb = g3 + dy*(g4 - g3);
            double g = ga + dx*(gb - ga);
            pnew->a[y][x] = g;
        }
    }

    return pnew;
}

void square_sampling(BYTE* s, BMP* p, int radius, int center_x, int center_y){
    int i=0;
    for(int y = center_y - radius; y <= center_y + radius; y++){
        for(int x = center_x - radius; x <= center_x + radius; x++){
            int a = x, b = y;
            if(a < 0 || a >= p->width){
                a = 2*center_x - a;
            }

            if(b < 0 || b >= p->height){
                 b = 2*center_y - b;
            }
            s[i] = p->a[b][a];
            i++;
        }
    }
}

void get_gaussian_kernel(double sigma, double* kernel, int radius){
    const double pi = 3.1415926;
    //double x, y;
    int i = 0;
    for (int x = -radius; x <= radius; x++){
        int _x = x * x;
        for (int y = -radius; y <= radius; y++){
            int _y = y * y;
            double g = exp(-(_x + _y) / (2 * sigma * sigma));
            g /= 2 * pi * sigma * sigma;
            kernel[i] = g;
            i++;
        }
    }
}

BMP* gaussian_smoothing(BMP* p, double sigma){
    BMP* pnew = new BMP;
    pnew->create_gray_bmp(p->width, p->height);

    int width = (int)ceil(sigma*6);
    if((width + 1)%2) width += 1;  //窗口宽度取奇数
    int radius = width / 2;

    double* kernel = new double[width*width];
    get_gaussian_kernel(sigma, kernel, radius);

    BYTE* s = new BYTE[width*width];
    for(int y=0; y<p->height; y++){
        for(int x=0; x<p->width; x++){
            square_sampling(s, p, radius, x, y);
            double sum = 0;
            for(int i=0; i<width*width; i++){
                sum += kernel[i] * s[i];
            }
            pnew->a[y][x] = (BYTE)sum;
        }
    }

    delete[] kernel;
    delete[] s;
    return pnew;
}

const int L = 256;

BMP* histogram_equalization(BMP* p){
    BMP* pnew = new BMP;
    pnew->create_gray_bmp(p->width, p->height);

    double total_pixel_num = p->width * p->height;
    int n[L];
    for(int i=0; i<L; i++){
        n[i] = 0;
    }

    for(int y=0; y<p->height; y++){
        for(int x=0; x<p->width; x++){
            int g = p->a[y][x];
            n[g]++;
        }
    }

    double h_cumulate[L];
    h_cumulate[0] = n[0] / total_pixel_num;
    for(int i=1; i<L; i++){
        h_cumulate[i] = h_cumulate[i-1] + n[i] / total_pixel_num;
    }

    BYTE gray_new[L];
    for(int i=0; i<L; i++){
        gray_new[i] = int((L-1)*h_cumulate[i] + 0.5);
    }

    for(int y=0; y<pnew->height; y++){
        for(int x=0; x<pnew->width; x++){
            int g = p->a[y][x];
            pnew->a[y][x] = gray_new[g];
        }
    }

    return pnew;
}

BMP* sharpening_sobel(BMP* p, double k1, double k2){
    BMP* pnew = new BMP;
    pnew->create_gray_bmp(p->width, p->height);

    int kernel_x[9] = {-1,0,1,-2,0,2,-1,0,1};
    int kernel_y[9] = {-1,-2,-1,0,0,0,1,2,1};
    BYTE s[9];
    for(int y=0; y<p->height; y++){
        for(int x=0; x<p->width; x++){
            square_sampling(s, p, 1, x, y);
            int grad_x=0, grad_y=0;
            for(int i=0; i<9; i++){
                grad_x += kernel_x[i] * s[i];
                grad_y += kernel_y[i] * s[i];
            }
            BYTE g = sqrt(grad_x*grad_x + grad_y*grad_y);
            pnew->a[y][x] = k1 * p->a[y][x] + k2 * g;
        }
    }

    return pnew;
}



BMP* impulsive_noise_salt(BMP* p, double rate){
    BMP* pnew = new BMP;
    pnew->create_gray_bmp(p->width, p->height);

    for(int i=0; i<N*rate; i++){
         flag[i] = true;
    }

    for(int i=N*rate; i<N; i++){
        flag[i] = false;
    }


    for(int y=0; y<p->height; y++){
        for(int x=0; x<p->width; x++){
            if(flag[rand() % N]){
                pnew->a[y][x] = rand()%2 ? 0 : 255;
            }else{
                pnew->a[y][x] = p->a[y][x];
            }
        }
    }

    return pnew;
}

BMP* impulsive_noise_random(BMP* p, double rate){
    BMP* pnew = new BMP;
    pnew->create_gray_bmp(p->width, p->height);

    for(int i=0; i<N*rate; i++) flag[i] = true;
    for(int i=N*rate; i<N; i++) flag[i] = false;

    for(int y=0; y<p->height; y++){
        for(int x=0; x<p->width; x++){
            if(flag[rand() % N]){
                pnew->a[y][x] = rand()%256;
            }else{
                pnew->a[y][x] = p->a[y][x];
            }
        }
    }

    return pnew;
}


