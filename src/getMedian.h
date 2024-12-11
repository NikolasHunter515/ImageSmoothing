//
// Created by Nikolas on 12/10/2024.
//

#ifndef GETMEDIAN_H
#define GETMEDIAN_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

#include "imgProcessHelp.h"
using namespace std;
using namespace chrono;

//sorting
int lPartition(vector<int>& A, int l, int r, double &step);
void LquickSort(vector<int>& A, int l, int r, double &step);
void insertionSort(int A[], int p, int n, double& step);

//deterministic median
int medOfMed(vector<int> A, int n, int groupSize, double & step);

//random median
int randomMedian(vector<int>& window);

//selection alg
int getPivotIndex(vector<int> A, int pivot, int n, double & step);
int selection(vector<int>& A, int l, int r, int k, double & step);

#endif //GETMEDIAN_H
