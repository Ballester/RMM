#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

int main(int argc, char *argv[0]) {
    if (argc != 4) {
        std::cout << "Wrong usage" << std::endl;
        exit(0);
    }

    int h = atoi(argv[1]);
    int w = atoi(argv[2]);
    int d = atoi(argv[3]);

    unsigned char c;
    int predicted[h][w][d];
    int residue[h][w][d];
    int raw_array[h][w][d];

    std::ifstream predicted_file;
    predicted_file.open("predicted.raw", std::ios::binary);
    std::ifstream residue_file;
    residue_file.open("residue.raw", std::ios::binary);

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            for (int k=0; k<d; k++) {
                residue_file >> c;
                residue[i][j][k] = (int) c; 
                
                predicted_file >> c;
                predicted[i][j][k] = (int) c;
            }
        }
    }
    predicted_file.close();
    residue_file.close();


    std::ofstream raw_file;
    raw_file.open("raw_file.raw", std::ios::binary);
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            for (int k=0; k<d; k++) {
                raw_file << (unsigned char) (predicted[i][j][k] + residue[i][j][k]); 
            }
        }
    }

}