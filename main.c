#include <stdio.h>
#include <string.h>

/* stb_image_write を使用してPNG出力 */
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define SIZE 21  // QRコードのサイズ（バージョン1: 21x21）

int matrix[SIZE][SIZE] = {0};  // QRコード用マトリクス

/* 関数プロトタイプ宣言 */
void save_qr_as_png(const char *filename);

/**
 * QRコードのデータをPNG画像として保存
 */
void save_qr_as_png(const char *filename) {
    unsigned char img[SIZE * SIZE];

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            img[y * SIZE + x] = matrix[y][x] ? 0 : 255;  // 1なら黒、0なら白
        }
    }

    // グレースケール1チャネルのPNGとして保存
    stbi_write_png(filename, SIZE, SIZE, 1, img, SIZE);
}

int main(int argc, char *argv[]) {
    
}