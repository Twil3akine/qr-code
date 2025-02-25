#include <stdio.h>
#include <string.h>

/* output as PNG */
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define SIZE 21

int matrix[SIZE][SIZE];

void text_to_binary(char *txt);
void apply_finder_pattern();
void print_qr_matrix();

void save_qr_as_png(const char *filename) {
    unsigned char img[SIZE * SIZE];

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            img[y * SIZE + x] = matrix[y][x] ? 0 : 255;
        }
    }

    // 1チャネル（グレースケール）でPNG保存
    stbi_write_png(filename, SIZE, SIZE, 1, img, SIZE);
}


void text_to_binary(char *txt) {
	for (int i = 0; i < strlen(txt); i++) {
		for (int j = 7; j >= 0; j--) {
			printf("%d", (txt[i] >> j) & 1);
		}
	}
	putchar(10); putchar(10);
}

void apply_finder_pattern() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i == 0 || j == 0 || i == 6 || j == 6 || (i >= 2 && i <= 4 && j >= 2 && j <= 4)) {
                matrix[i][j] = 1;
                matrix[SIZE - i - 1][j] = 1;
                matrix[i][SIZE - j - 1] = 1;
            }
        }
    }
}

void print_qr_matrix() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            printf("%s", matrix[y][x] ? "■" : " ");
        }
        putchar(10);
    }
}

int main(int argc, char *argv[]) {
    char *url = (argc == 1) ? "https://twil3akine.pages.dev" : argv[1];
    text_to_binary(url);

    apply_finder_pattern();
    print_qr_matrix();

    save_qr_as_png("qr_code.png");

    return 0;
}