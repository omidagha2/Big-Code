#include <iostream>
#include <cstdlib> // For system()

int main() {
    const char* command = "start ding.wav";

    std::cout << "Playing sound..." << std::endl;
    std::system(command);

    return 0;
}
