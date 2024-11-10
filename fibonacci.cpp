#include <iostream>
#include <chrono>

int fibonacci_sequence_recursive(int number) {
    if (number <= 1) {
        return number;
    }
    return fibonacci_sequence_recursive(number-1) + fibonacci_sequence_recursive(number-2);
}

int fibonacci_sequence_recursive_optimized(int number, int previous_number2 = 0, int previous_number1 = 1) {
    if (number == 0) {
        return previous_number2;
    }
    if (number == 1) {
        return previous_number1;
    }
    return fibonacci_sequence_recursive_optimized(number - 1, previous_number1, previous_number2 + previous_number1);
}

int fibonacci_sequence_non_recursive(int number) {
    if (number <= 1) {
        return number;
    }

    int previous_term1 = 1, previous_term2 = 0, current_term;

    for (int i = 2; i <= number; i++) {
        current_term = previous_term1 + previous_term2;
        previous_term2 = previous_term1;
        previous_term1 = current_term;
    }
    return current_term;
}

int main() {
    using namespace std::chrono;

    int user_number;
    std::cout << "Enter n to find the nth fibonacci number: ";
    std::cin >> user_number;

    std::cout << "The " << user_number << "th fibonacci number is: " << std::endl;

    int ITERATIONS = 100000;
    std::cout << "By recursive method: " << std::endl;
    auto recursive_start = high_resolution_clock::now();
    int nth_fibonacci_recursive = fibonacci_sequence_recursive(user_number);
    auto recursive_stop = high_resolution_clock::now();
    duration<double> recursive_duration = (recursive_stop - recursive_start);
    std::cout << "Number: " << nth_fibonacci_recursive << std::endl;
    std::cout << "Time Taken: " << recursive_duration.count() << "s" << std::endl;
    /* Time Complexity: O (2n), where n is the number of term to find.
    Auxiliary Space: O (n) */

    std::cout << "By optimized recursive method: " << std::endl;
    auto optimized_recursive_start = high_resolution_clock::now();
    int nth_fibonacci_recursive_optimized;
    for (int _ = 0; _ <= ITERATIONS; _++) {
        nth_fibonacci_recursive_optimized = fibonacci_sequence_recursive_optimized(user_number);
    }
    auto optimized_recursive_stop = high_resolution_clock::now();
    duration<double> optimized_recursive_duration = (optimized_recursive_stop - optimized_recursive_start) / ITERATIONS;
    std::cout << "Number: " << nth_fibonacci_recursive_optimized << std::endl;
    std::cout << "Time Taken: " << optimized_recursive_duration.count() << "s" << std::endl;
    /* Time Complexity: O (n), where n is the number of term to find.
    Auxiliary Space: O (n) */

    std::cout << "By non-recursive method: " << std::endl;
    auto non_recursive_start = high_resolution_clock::now();
    int nth_fibonacci_non_recursive;
    for (int _ = 0; _ <= ITERATIONS; _++) {
        nth_fibonacci_non_recursive = fibonacci_sequence_non_recursive(user_number);
    }
    auto non_recursive_stop = high_resolution_clock::now();
    duration<double> non_recursive_duration = (non_recursive_stop - non_recursive_start) / ITERATIONS;
    std::cout << "Number: " << nth_fibonacci_non_recursive << std::endl;
    std::cout << "Time Taken: " << non_recursive_duration.count() << "s" << std::endl;
    /* Time Complexity: O(n), where n is the number of term to find.
    Auxiliary Space: O(1) */

    return 0;
}