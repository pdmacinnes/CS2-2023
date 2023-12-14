#include <iostream>

int fibonacci(int n) {
    // Base case
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        // Recursive case
        return fibonacci(n - 1) + fibonacci(n - 2);
   }
}

int main() {
    int n = 10;
    int result = fibonacci(n);
    std::cout << "The " << n << "th term of the Fibonacci sequence is: " << std::endl;
    return 0;
}