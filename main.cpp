// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

/*
Histogram sorting:
Technique: Divide the data into bins, and sort each bin
*/

const size_t INPUT_SIZE = 1000000;
const size_t RAND_MAX_VAL = 1000;

void histogramSort(std::vector<int>& input, int start, int end) {
    if ((end == start)||(input.size()<2)) {
        return;
    }
    else {
        int mid = (start + end) / 2;
        std::vector<int> lower;
        std::vector<int> upper;
        for (size_t i = 0; i < input.size(); i++) {
            if (input[i] <= mid) {
                lower.push_back(input[i]);
            }
            else {
                upper.push_back(input[i]);
            }
        }
        histogramSort(lower, start, mid);
        histogramSort(upper, mid+1, end);
        lower.insert(lower.end(), upper.begin(), upper.end());
        input = lower;
        return;
    }
}

int main()
{
    cout << "Histogram sorting" << endl;
    std::vector<int> input;
    //cout << "\nInput:";
    for (size_t i = 0; i < INPUT_SIZE; i++) {
        input.push_back(rand() % RAND_MAX_VAL);
     //   cout << "\t" << input[i];
    }
    auto startTime = std::chrono::steady_clock::now();
    histogramSort(input, 0, RAND_MAX_VAL);
    auto endTime = std::chrono::steady_clock::now();
    //cout << "\nOutput:";
    //for (size_t i = 0; i < INPUT_SIZE; i++) {
    //    cout << "\t" << output[i];
    //}

    //validation
    bool status = true;
    for (size_t i = 0; i < INPUT_SIZE-1; i++) {
        if (input[i] > input[i + 1]) {
            status = false;
            break;
        }
    }
    cout << "\nStatus: " << status;
    cout << "\nelapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()<<"\n";
    return 0;
}
