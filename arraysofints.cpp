#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> getSortedArray(int n)
{
    vector<int> list;
    for (int i = n; i > 0; i--)
    {
        list.push_back(i);
    }
    return list;
}

vector<int> getRandomArray(int n)
{
    vector<int> list;
    list = getSortedArray(n);
    random_shuffle(list.begin(), list.end());
    return list;
}

void printArray(vector<int> arr, int n) {
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}

int main() {
    vector<int> r;
    vector<int> s;
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
