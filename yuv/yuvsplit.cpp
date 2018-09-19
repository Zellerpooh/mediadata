//
// Created by Administrator on 2018/9/18.
// https://blog.csdn.net/leixiaohua1020/article/details/50534150
//

#include "yuvsplit.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


/**
 * 将YUV420P像素数据的周围加上边框
 * @param url
 * @param w
 * @param h
 * @param border
 * @param num
 * @return
 */
int simplest_yuv420_border(char *url, int w, int h, int border, int num) {
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("D:/zeller/clionproject/mediadata/output/output_border.yuv", "wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);
    for (int i = 0; i < num; i++) {
        fread(pic, 1, w * h * 3 / 2, fp);
        for (int j = 0; j < h; ++j) {
            for (int k = 0; k < w; k++) {
                if (k < border || k > (w - border) || j < border || j > (h - border)) {
                    pic[j * w + k] = 255;
                }
            }
        }
        fwrite(pic, 1, w * h * 3 / 2, fp1);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
    return 0;
}

/**
 * 将YUV420P像素数据的亮度减半
 * Halve Y value of YUV420P file
 * @param url
 * @param w
 * @param h
 * @param num
 * @return
 */
int simplest_yuv420_halfy(char *url, int w, int h, int num) {
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_half.yuv", "wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);
    for (int i = 0; i < num; ++i) {
        fread(pic, 1, w * h * 3 / 2, fp);

        for (int j = 0; j < w * h; ++j) {
            unsigned char temp = pic[j] / 2;
            pic[j] = temp;
        }
        fwrite(pic, 1, w * h * 3 / 2, fp1);
    }
    free(pic);
    fclose(fp);
    fclose(fp1);

    return 0;
}

/**
 *  将YUV420P像素数据去掉颜色（变成灰度图）
 * simplest_yuv420_gray
 * @return
 *
 *    memset(pic + w * h, 128, w * h / 2);
 *    把u、v向量全部设为128
 */
int simplest_yuv420_gray(char *url, int w, int h, int num) {
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_gray.yuv", "wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for (int i = 0; i < num; i++) {
        fread(pic, 1, w * h * 3 / 2, fp);
        //Gray
        memset(pic + w * h, 128, w * h / 2);
        fwrite(pic, 1, w * h * 3 / 2, fp1);
    }
    free(pic);
    fclose(fp);
    fclose(fp1);
    return 0;
}

/**
 * 分离YUV420P像素数据中的Y、U、V分量,yuv420p
 */
int simplest_yuv420_split(char *url, int w, int h, int num) {
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_420_y.y", "wb+");
    FILE *fp2 = fopen("output_420_u.y", "wb+");
    FILE *fp3 = fopen("output_420_v.y", "wb+");

    unsigned char *pic = (unsigned char *) malloc(w * h * 3 / 2);

    for (int i = 0; i < num; ++i) {
        fread(pic, 1, w * h * 3 / 2, fp);
        //Y
        fwrite(pic, 1, w * h, fp1);
        //U
        fwrite(pic + w * h, 1, w * h / 4, fp2);
        //V
        fwrite(pic + w * h * 5 / 4, 1, w * h / 4, fp3);
    }

    free(pic);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return 0;
}

int main(void) {
    simplest_yuv420_border("D:/zeller/clionproject/mediadata/source/lena_256x256_yuv420p.yuv", 256, 256, 20, 1);
    return 0;
}
