//
// Created by Nikolas on 12/10/2024.
//

#ifndef IMGPROCESS_H
#define IMGPROCESS_H
#include <vector>
#include <fstream>
#include <sstream>
#include<iostream>
#include <cmath>

#include "imgProcessHelp.h"
#include "getMedian.h"

//may not need the header paramter if writing to a
//read and write to file.
void parseFile(const string& filename, vector<vector<int>>& image, string& header);
void writeFile(const string fileName, const vector<vector<int>> data, const string header);

//filter one image, and multiple.
void medianFilter(vector<vector<int>>& input, int windowSize, double& step);
void massFiltering(vector<string> names, string inFilePath, string outFilePath, string fileExtension, int windowSize);


#endif //IMGPROCESS_H
