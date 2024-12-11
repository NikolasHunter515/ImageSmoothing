//
// Created by Nikolas on 12/11/2024.
//
#include "getMedian.h"
using namespace std;

int lPartition(vector<int>& A, int l, int r, double &step){
    int i = l - 1;

    for(int j = l; j < r ; j++){
        if(A[j] < A[r - 1]){
            i++;
            swap(A[i], A[j]);
            step += 3;
        }
        step++;
    }
    swap(A[i + 1], A[r - 1]);
    step += 3;
    return i + 1;
}

void LquickSort(vector<int>& A, int l, int r, double &step){
    if(l < r){
        int q = lPartition(A, l, r, step);
        LquickSort(A, l, q - 1, step);
        LquickSort(A, q + 1, r, step);
    }
}

void insertionSort(int A[], int p, int n, double& step){ // O(n^2)
    step = 0;
    step += 1;
    step += (p - (n + 1)); // condition
    step += (p - (n + 1)); //  increment
    int i;
    for(i = p; i <= n; i++){
        int temp = A[i];
        int j = i - 1;

        step += 2;

        while(j >= p && A[j] > temp){
            A[j + 1] = A[j];
            j--;
            step += 2;
        }
        step += i - 1; // inner loop conditions.
        step += i + 1;
        A[j + 1] = temp;
        step += 1;
    }
}

int medOfMed(vector<int> A, int n, int groupSize, double & step){
    vector<int> medians; // size should be n/5


    for(int i = 0; i < n; i += groupSize){
        int temp[groupSize];
        int end = min(i + (groupSize - 1), n - 1);

        for(int j = i; j <= end; j++){
            temp[j - i] = A[j];
            step++;
        }
        // sort the temp, using insertion sort.
        insertionSort(temp, 0, end - i, step);
        // then take its median and insertinto the medians vector.
        medians.push_back(temp[(end - i) / 2]);
        step++; // for the outter loop
    }
    //sort the medians.
    LquickSort(medians, 0, medians.size(), step);

    //return the median of medians
    if(medians.size() % 2 == 0){
        return medians[((medians.size() / 2) + ((medians.size() / 2) + 1)) / 2];
    }

    return medians[(medians.size() + 1 )/ 2];
}

int randomMedian(vector<int>& window) {
    sort(window.begin(), window.end());
    int n = window.size();
    return window[n / 2];
}

int getPivotIndex(vector<int> A, int pivot, int n, double & step){
    for(int i = 0; i < n; i++){
        step++;
        if(A[i] == pivot) return i;
    }
    return n - 1;
}

int selection(vector<int>& A, int l, int r, int k, double & step){

    if(k > 0 && k <= r - l + 1){
        int pivot = medOfMed(A, r, 2, step);
        int pivotIndex = getPivotIndex(A, pivot, r, step);
        //call pivoting method

        swap(A[pivotIndex], A[r - 1]);
        step += 3;
        pivot = lPartition(A, l, r, step); //need to change all arrays to vectors first.
        //partition inputs around the pivot(median of medians)
        // this is more like a binary search after partitioning around the pivot  choose new interval based on location of k.

        step++;
        if(k - 1 == pivot - l){
            return A[pivot];
        }

        if(k - 1 < pivot - l){
            return selection(A, l, pivot - 1, k, step);
        }
        else return selection(A, pivot + 1, r, k - pivot + l - 1, step);
    }

    return 0;
}