/* Naive Approach: Try all possible subsets with all different fractions.
Time Complexity: O(2N)
Auxiliary Space: O(N) 
An efficient solution is to use the Greedy approach. */

#include <iostream>
#include <algorithm>
#include <chrono>

struct Item {
    int profit, weight;
    Item(){}
    Item(int profit, int weight) {
        this->profit = profit;
        this->weight = weight;
    }
};

static bool compareItems(Item a, Item b) {
    double a_profitWeightRatio = (double) a.profit / (double) a.weight;
    double b_profitWeightRatio = (double) b.profit / (double) b.weight;
    return a_profitWeightRatio > b_profitWeightRatio;
}

double fractionalKnapsack(int capacity, Item Items[], int numberOfItems) {
    std::sort(Items, Items + numberOfItems, compareItems);
    double finalProfit = 0.0;

    int remainingCapacity = capacity;
    for (int i = 0; i < numberOfItems; i++) {
        if (Items[i].weight <= remainingCapacity) {
            remainingCapacity -= Items[i].weight;
            finalProfit += Items[i].profit;
        }
        else {
            finalProfit += Items[i].profit * ((double) remainingCapacity / (double) Items[i].weight);
            break;
        }
    }

    return finalProfit;
}

int main() {
    int numberOfItems;
    std::cout << "Enter the number of items: ";
    std::cin >> numberOfItems;

    Item *Items = new Item[numberOfItems];
    for (int i = 0; i < numberOfItems; ++i) {
        std::cout << "Enter value and weight of item " << i + 1 << " (seperated by a space): ";
        std::cin >> Items[i].profit >> Items[i].weight;
    }

    int capacity;
    std::cout << "\nEnter the maximum capacity of the knapsack: ";
    std::cin >> capacity;

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "The maximum profit is: " << fractionalKnapsack(capacity, Items, numberOfItems) << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds> (stop - start).count();
    std::cout << "The time taken is: " << duration << "ns" << std::endl;

    delete[] Items;
    return 0;
}