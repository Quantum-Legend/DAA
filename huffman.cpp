#include <iostream>
#include <queue>
#include <chrono>

class MinHeapNode {
public:
    char data;
    unsigned frequency;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned frequency) {
        left = right = NULL;
        this->data = data;
        this->frequency = frequency;
    }

    struct compare {
        bool operator() (MinHeapNode* l, MinHeapNode *r) {
            return (l->frequency > r->frequency);
        }
    };

};

MinHeapNode* HuffmanTree(char data[], int frequency[], int size) {
    struct MinHeapNode *left, *right, *top;
    std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, MinHeapNode::compare> minHeap;
    for (int i = 0; i < size; ++i) {
        minHeap.push(new MinHeapNode(data[i], frequency[i]));
    }

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    return minHeap.top();
}

void printCodes(struct MinHeapNode* root, std::string str = "") 
{ 
    if (!root) 
        return; 

    if (root->data != '$') 
        std::cout << root->data << " : " << root->frequency << " : " <<  str << std::endl;

    printCodes(root->left, str + "0"); 
    printCodes(root->right, str + "1"); 
}

int main() {
    int size = 1;
    std::cout << "Enter number of characters: ";
    std::cin >> size;
    char *characters = new char[size];
    int *frequencies = new int[size];
    for (int i = 0; i < size; i++) {
        std::cout << "Enter character #" << i+1 << ": ";
        std::cin >> characters[i];
        std::cout << "Enter it's frequency: ";
        std::cin >> frequencies[i];
    }
    std::cout << std::endl;

    /* int ITERATIONS = 100000;
    auto start = std::chrono::high_resolution_clock::now();
    MinHeapNode* top;
    for (int i = 0; i < ITERATIONS; i++) top = HuffmanTree(characters, frequencies, size);
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = (stop - start) / ITERATIONS; */

    int ITERATIONS = 100000;
    auto start = std::chrono::high_resolution_clock::now();
    MinHeapNode* top;
    for (int i = 0; i < ITERATIONS; i++) top = HuffmanTree(characters, frequencies, size);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds> (stop - start) / ITERATIONS;
    
    std::cout << "The Huffman Codes are: " << std::endl;
    printCodes(top);
    std::cout << "\nTime Taken: " << duration.count() << "ns" <<std::endl;
    /* Time complexity: O(nlogn) where n is the number of unique characters.
    If the input array is sorted, there exists a linear time algorithm.
    Space complexity :- O(N) */
    delete[] characters;
    delete[] frequencies;

    return 0;
}