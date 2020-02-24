#include <stdio.h>
#include <iostream>
#include <time.h>
using namespace std;

int* getRandomArray(int n) {
    int* arr = new int[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
    return arr;
}

int* getSortedArray(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}

int main() {
    int* r, *s;
    int size = 6;
    r = getRandomArray(6);
    s = getSortedArray(6);
    cout << "Random array: ";
    printArray(r, size);
    cout << endl;
    cout <<"Sorted array: ";
    printArray(s, size);
    return 0;
}