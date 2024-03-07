#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

vector<int> split(string);
void set_background_color(int r, int g, int b);
void reset_background_color();
void draw(string pixelarr, int width);

int main() {
    ifstream infile;
    infile.open("testimg.txt");
    string image;
    getline(infile, image);
    // draw(image, 80);
    draw(img, 38);
    
}

//returns spaces till space
vector<int> split(string str){
    vector<int> vals;
    for (int i = 0; i < 3; i++){
        int a = str.find(',');
        vals.push_back(stoi(str.substr(0, a)));
        str = str.substr(a + 2, str.length() - a - 2);
    }
    return vals;
}

void draw(string pixelarr, int width){
    while (pixelarr.length()){
        for (int i = 0; i < width; i++){
            int a = pixelarr.find('[');
            int b = pixelarr.find(']');
            vector<int> rgbvals = split(pixelarr.substr(a + 1, b - a));
            set_background_color(rgbvals[0], rgbvals[1], rgbvals[2]);
            printf("  ");
            reset_background_color();
            pixelarr = pixelarr.substr(b + 1, pixelarr.length() - b - 1);
        }
        cout << endl;
    }
}

void set_background_color(int r, int g, int b) {
    //ANSI escape code for setting background color
    std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m";
}

void reset_background_color() {
    //ANSI escape code for resetting background color
    std::cout << "\033[0m";
}

void draw_mario(){
    
}

void draw_rainbow(){
    for (int i = 0; i < 256; i+=8){
        for (int j = 0; j < 256; j+=8){
            for (int k = 0; k < 256; k+=2){
                set_background_color(i, j, k);
                cout << ' ';
                reset_background_color();
            }
            cout << endl;
        }
    }
}