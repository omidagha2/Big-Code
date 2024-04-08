class b; // Forward declaration for class b

class a {
public:
    void hi(b b1); // Declare the function
};

class b {
public:
    void hi(a a1); // Declare the function
};

// Implement the member functions outside the class definitions
void a::hi(b b1) {
    // Implementation for a::hi
}

void b::hi(a a1) {
    // Implementation for b::hi
}

int main() {
    // Your main function
}
