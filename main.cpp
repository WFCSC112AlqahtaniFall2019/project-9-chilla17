#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include "Data.h"
using namespace std;

// bubbleSort from slides
template <typename T>
void bubbleSort(vector<T>& arr, int size) {
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (arr[j+1] <= arr[j]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// selection sort from min to max from slides
template <typename T>
void minSort(vector <T>& arr, int size) {
    int min;
    for (int i = 0; i < size - 1; ++i) {
        min = i;
        for (int j = 1 + 1; j < size; ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}

// partition and quickSort from Zybooks
template <typename T>
int partition(vector <T>& numbers, int i, int k) {
    int l;
    int h;
    int midpoint;
    T pivot;
    T temp;
    bool done;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers.at(midpoint);

    done = false;
    l = i;
    h = k;

    while (!done) {

        /* Increment l while numbers[l] < pivot */
        while (numbers.at(l) < pivot) {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers.at(h)) {
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers.at(l);
            numbers.at(l) = numbers.at(h);
            numbers.at(h) = temp;

            ++l;
            --h;
        }
    }

    return h;
}

template <typename T>
void quickSort(vector<T>& numbers, int i, int k) {
    int j;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = partition(numbers, i, k);

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    quickSort(numbers, i, j);
    quickSort(numbers, j + 1, k);
}

// merge and mergeSort from Zybooks
template <typename T>
void merge(vector<T>& numbers, int i, int j, int k) {
    int mergedSize;                            // Size of merged partition
    int mergePos;                              // Position to insert merged number
    int leftPos;                               // Position of elements in left partition
    int rightPos;                              // Position of elements in right partition

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                               // Initialize left partition position
    rightPos = j + 1;                          // Initialize right partition position
    vector<T> mergedNumbers(mergedSize);

    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (numbers[leftPos] < numbers[rightPos]) {
            mergedNumbers.at(mergePos) = numbers.at(leftPos);
            ++leftPos;
        }
        else {
            mergedNumbers[mergePos] = numbers.at(rightPos);
            ++rightPos;

        }
        ++mergePos;
    }

    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
}

template <typename T>
void mergeSort(vector<T>& numbers, int i, int k) {
    int j;

    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        mergeSort(numbers, i, j);
        mergeSort(numbers, j + 1, k);

        // Merge left and right partition in sorted order
        merge(numbers, i, j, k);
    }
}

int main() {
    // create vectors
    vector<Data> dataV;
    vector<int> intV;

    ifstream in;
    ofstream out;
    string ID;
    string c;
    string st;
    string yr;
    string solv;
    string vSex;
    string vAge;
    string pSex;
    string pAge;

    // csv file to record times for each sorting algorithm
    out.open("../time.csv");
    if (!out.is_open()) {
        cout << "Unable to open time.csv" << endl;
        return 1;

    }

    cout << "Writing to time.csv..." << endl;

    in.open("../homicide.csv"); // open homicide.csv
    if (!in.is_open()){
         cout << "Unable to open homicide.csv" << endl;
         return 1;

    }

    cout << "Reading homicide.csv..." << endl;

    while (!in.eof()) {
        getline(in, ID, ',');
        getline(in, c, ',');
        getline(in, st, ',');
        getline(in, yr, ',');
        getline(in, solv, ',');
        getline(in, vSex, ',');
        getline(in, vAge, ',');
        getline(in, pSex, ',');
        getline(in, pAge, '\n');
        int age = stoi(vAge); // change age from string to int
        Data data(ID, c, st, yr, solv, vSex, age, pSex, pAge); // Data class object
        dataV.push_back(data); // put Data objects into vector

    }

    srand(time(NULL)); // random int seed by time

    // populate vector with random int
    for (int i = 0; i < dataV.size(); i++) {
        intV.push_back(rand()%100);

    }

    // copy dataV
    vector<Data> dataV_B = dataV;
    vector<Data> dataV_S = dataV;
    vector<Data> dataV_Q = dataV;
    vector<Data> dataV_M = dataV;

    // copy intV
    vector<int> intV_B = intV;
    vector<int> intV_S = intV;
    vector<int> intV_Q = intV;
    vector<int> intV_M = intV;

    for (int N = 0; N <= dataV.size(); N = N + 10000) {

        // bubbleSort
        cout << "bubbleSort..." << endl;
        // time
        clock_t start_dataV_B = clock(); //start clock
        bubbleSort(dataV_B, N);
        clock_t end_dataV_B = clock(); //end clock
        double elapsed_dataV_B = double(end_dataV_B - start_dataV_B) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(dataV_B.at(i - 1) <= dataV_B.at(i));
        }

        // time
        clock_t start_intV_B = clock(); //start clock
        bubbleSort(intV_B, N);
        clock_t end_intV_B = clock(); //end clock
        double elapsed_intV_B = double(end_intV_B - start_intV_B) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(intV_B.at(i - 1) <= intV_B.at(i));
        }
        cout << "finished bubbleSort" << endl;

        // minSort
        cout << "minSort..." << endl;
        // time
        clock_t start_dataV_S = clock(); // start clock
        minSort(dataV_S, N);
        clock_t end_dataV_S = clock(); //end clock
        double elapsed_dataV_S = double(end_dataV_S - start_dataV_S) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(dataV_B.at(i - 1) <= dataV_B.at(i));
        }

        // time
        clock_t start_intV_S = clock(); //start clock
        bubbleSort(intV_S, N);
        clock_t end_intV_S = clock(); //end clock
        double elapsed_intV_S = double(end_intV_S - start_intV_S) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(intV_S.at(i - 1) <= intV_S.at(i));
        }
        cout << "finished minSort" << endl;

        // quickSort
        cout << "quickSort..." << endl;
        // time
        clock_t start_dataV_Q = clock(); // start clock
        quickSort(dataV_Q, 0, N - 1);
        clock_t end_dataV_Q = clock(); //end clock
        double elapsed_dataV_Q = double(end_dataV_Q - start_dataV_Q) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(dataV_Q.at(i - 1) <= dataV_Q.at(i));
        }

        // time
        clock_t start_intV_Q = clock(); // start clock
        quickSort(intV_Q, 0, N - 1);
        clock_t end_intV_Q = clock(); //end clock
        double elapsed_intV_Q = double(end_intV_Q - start_intV_Q) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(intV_Q.at(i - 1) <= intV_Q.at(i));
        }

        cout << "finished quickSort" << endl;

        // mergeSort
        cout << "mergeSort..." << endl;
        // time
        clock_t start_dataV_M = clock(); // start clock
        mergeSort(dataV_M, 0, N - 1);
        clock_t end_dataV_M = clock(); //end clock
        double elapsed_dataV_M = double(end_dataV_M - start_dataV_M) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(dataV_M.at(i - 1) <= dataV_M.at(i));
        }

        // time
        clock_t start_intV_M = clock(); // start clock
        mergeSort(intV_M, 0, N - 1);
        clock_t end_intV_M = clock(); //end clock
        double elapsed_intV_M = double(end_intV_M - start_intV_M) / CLOCKS_PER_SEC;

        // unit test
        for (int i = 1; i < N - 1; i++) {
            assert(intV_M.at(i - 1) <= intV_M.at(i));
        }
        cout << "finished mergeSort" << endl;

        // while loop to print labels at the top of my time table
        int P = N;
        while (P == 0) {
            out << "N" << ", " << "bubbleSort homicide" << ", " << "bubbleSort int" << ", " << "selectionSort homicide" << ", " << "selectionSort int" << ", " << "quickSort homicide" << ", " << "quickSort int" << ", " << "mergeSort homicide" << ", " << "mergeSort int" << endl;
            P++;
        }

        out << N << ", " << elapsed_dataV_B << ", " << elapsed_intV_B << ", " << elapsed_dataV_S << ", " << elapsed_intV_S << ", " << elapsed_dataV_Q << ", " << elapsed_intV_Q << ", " << elapsed_dataV_M << ", " << elapsed_intV_M << endl;
    }

    return 0;
}