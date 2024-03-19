#include <iostream>
#include <cmath>

// Set background color based on RGB values
void set_background_color(int r, int g, int b) {
    std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m ";
}

// Reset background color
void reset_background_color() {
    std::cout << "\033[0m";
}

int main() {
    const int num_steps = 256; // Number of steps in the color spectrum

    for (int i = 0; i < num_steps; ++i) {
        // Calculate hue (0.0 to 1.0) for the current step
        double hue = static_cast<double>(i) / num_steps;

        // Convert hue to RGB using simple linear interpolation
        int r = static_cast<int>(255 * std::abs(1.0 - hue));
        int g = static_cast<int>(255 * std::abs(hue - 0.5));
        int b = static_cast<int>(255 * std::abs(hue - 1.0));

        set_background_color(r, g, b);
        std::cout << " "; // Print a colored pixel (space)
        reset_background_color();
    }

    std::cout << std::endl; // Move to the next line
    return 0;
}
