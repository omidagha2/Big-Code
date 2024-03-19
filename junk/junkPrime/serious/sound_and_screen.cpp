#include <iostream>
#include <conio.h>

using namespace std;


void set_background_color(int r, int g, int b);
void reset_background_color();

int main() {
    for (int i = 0; i < 256; i+=16){
        for (int j = 0; j < 256; j+=16){
            for (int k = 0; k < 256; k+=4){
                set_background_color(i, j, k);
                cout << ' ';
                reset_background_color();
            }
            cout << endl;
        }
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
