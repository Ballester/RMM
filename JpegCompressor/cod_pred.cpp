#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "jo_jpeg.cpp"

int main(int argc, char *argv[0]) {
    if (argc != 5) {
        std::cout << "Wrong usage" << std::endl;
        exit(0);
    }

    std::ifstream raw_file;
    raw_file.open(argv[1], std::ios::binary);

    int h = atoi(argv[2]);
    int w = atoi(argv[3]);
    int d = atoi(argv[4]);

    unsigned char c;
    int predicted[h][w][d];
    int residue[h][w][d];
    int raw_array[h][w][d];
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            for (int k=0; k<d; k++) {
                raw_file >> c;
                raw_array[i][j][k] = (int) c; 
                predicted[i][j][k] = (int) c;
            }
        }
    }
    raw_file.close();

    for (int i=1; i<h; i++) {
        for (int j=0; j<w; j++) {
            for (int k=0; k<d; k++) {
                predicted[i][j][k] = raw_array[i-1][j][k];
                // raw_array[i][j][k] = raw_array[i][j-1][k];
            }
        }
    }

    std::ofstream residue_file;
    residue_file.open("residue.raw", std::ios::binary);
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            for (int k=0; k<d; k++) {
                residue[i][j][k] = abs(raw_array[i][j][k] - predicted[i][j][k]);
                residue_file << (unsigned char) residue[i][j][k];
            }
        }
    }

    residue_file.close();

    char *residue_c = new char[w*h*d];
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            for (int k=0; k<d; k++) {
                residue_c[(i*w)+(j*d)+k] = (char) residue[i][j][k];
            }
        }
    }
    jo_write_jpg("residue.jpg", residue_c, h, w, d, 100);
}
