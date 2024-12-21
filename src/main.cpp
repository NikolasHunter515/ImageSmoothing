#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <cmath>
#include "getMedian.h"
#include "imgProcess.h"

using namespace std;
using namespace chrono;

void randomInput(vector<int>& A, int inputSize){ // Generates random input.
	srand(time(0));
	int val;
	for(int i = 0; i < inputSize; i++){
		val = rand() % inputSize;
		A.push_back(val);
	}
}

//this one works properly now.
void instances(vector<int> sizes, int n){
	duration<double> randTimes[6];
	int windowSizes [6] = {100, 300, 500, 1000, 2000, 4000};

	double randSteps[6] = {0}; // steps to get the median of medians.

	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;

	string name = "median of Medians";


	for(int i = 0; i < 3; i++){
		vector<int> A;
		//for each population size test each window size.
		//TODO for each window size run it ntimes(5).
		for (int l = 0; l < n; l++) {
			for(int j = 0; j < 6; j++){
				double s = 0;
				randomInput(A, windowSizes[j]);

				t1 = high_resolution_clock::now();
				medOfMed(A, A.size(), windowSizes[j], s);
				t2 = high_resolution_clock::now();
				randSteps[j] += s;
				s = 0;
				randTimes[j] += duration_cast<duration<double>>(t2 - t1);
			}
		}

		cout << "N = " << sizes[i] << endl;
		for(int k = 0; k < 6; k++){
			cout << "Window size: " << windowSizes[k] << " :\n";
			cout << (randTimes[k].count() * milliseconds::period::num / milliseconds::period::den)  / n << endl;

			cout << "Random Ave steps:" << randSteps[k] / n << endl;
			cout << endl;
		}
		cout << endl;
	}
}// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

void toVect(const vector<vector<int>>& input, int row, int col, int windowSize, vector<int>& outVect) {
	/*int halfWindow = windowSize / 2; // This is equivalent to startDex
	for (int i = row - halfWindow; i <= row + halfWindow; ++i) {
		for (int j = col - halfWindow; j <= col + halfWindow; ++j) {
			// Check bounds to ensure valid access
			if (i >= 0 && i < input.size() && j >= 0 && j < input[i].size()) {
				outVect.push_back(input[i][j]);
			}
		}
	}*/

	int halfWindowSize = windowSize / 2; // This is equivalent to startDex
	int rows = input.size();
	int cols = input[0].size();
	for (int di = -halfWindowSize; di <= halfWindowSize; ++di) {
		for (int dj = -halfWindowSize; dj <= halfWindowSize; ++dj) {
			int ni = row + di;
			int nj = col + dj;

			// Check if the neighboring pixel is within bounds
			if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
				outVect.push_back(input[ni][nj]);
			}
		}
	}
}


//TODO if file is not txt file, throw an error and return.
//for file name pass in full file path to storage location including the extension(txt).

int main() {
	//TODO some images already had noise redu steps except for adding noise.

	//maybe consider running alg on already process images>
	vector<string> names = {"nose", "chrystler2", "chrystler", "bbridge", "ny80s", "arch", "spaceneedle", "indy500", "overlookhotel", "twilightzone", "woodstock69", "titanic", "oldman", "oldcar", "oldtypewriter", "oldfarmhouse", "lamp", "shadows", "wallstreet", "cemetary"};
	vector<int> sizes = {5000, 8000, 10000};
	cout << names.size() << endl;
	auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";
	string header;
	vector<vector<int>> im;
	vector<int> rand;
	double s = 0;
	randomInput(rand, 50);
	for (int i  = 0; i < rand.size(); i++) {
		cout << rand[i] << " ";
	}
	cout << endl;

	cout << selection(rand, 0, rand.size(), 2,s) << endl;

	//options include, run the instances method, run testfilering method, and quit.
	//TODO try with a 3 x 3 window and maybe try with the medofmed algorithm, this did not have to be done in c++
	char userSelection;
	do {
		cout << "Welcome select which method you would like to run: \n";
		cout << "1: Run the instances method\n";
		cout << "2: Run the filtering method\n";
		cin >> userSelection;
		cout << endl;
		if (userSelection == '1') {
			//run the instances method
			instances(sizes, 5);
		}
		else if (userSelection == '2') {
			massFiltering(names, "C:/Users/Owner/CLionProjects/secondtest/inputs", "C:/Users/Owner/CLionProjects/secondtest/outputs", "txt", 3);
			cout << "Finished filtering\n";
		}
		else if(userSelection == 'q') break;
		else {
			cout << "Invalid selection. Try Again\n";
		}
	}while (userSelection != 'q');


    return 0;
}