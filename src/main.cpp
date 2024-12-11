#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "getMedian.h"
#include "imgProcessHelp.h"
#include "imgProcess.h"

using namespace std;
using namespace chrono;

/*
void swap(int &a, int &b){ // three steps every time.
	int temp = b;
	b = a;
	a = temp;
}

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
*/
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

	double randSteps[6] = {0}; // steps to sort a random order array

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
struct img{
	vector<vector<int>> pixels;
	int width, height, initial, range;
	string color;
	string hexa;
};

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

/*
// retruns int values converted to hex(capital chars), and returns values of length 6(3 bytes).
string toHex(int num) {
	//TODO consider adding parameter to allow user to decide how long hex string should be.
	stringstream ss;
	string hex;
	ss << std::hex << num;
	hex = ss.str();
	if (hex[0] >= 48 && hex[0] <= 57 || hex[1] >= 48 && hex[1] <= 57) {
		return hex = hex + hex + hex;
	}
	else {
		hex[0] = (char)(hex[0] - 32);
		hex[1] = (char)(hex[1] - 32);
	}

	return hex = hex + hex + hex;
}


//not sure if this is being used.
double findMedian(vector<int> a,
				  int n)
{

	// If size of the arr[] is even
	if (n % 2 == 0) {

		// Applying nth_element
		// on n/2th index
		nth_element(a.begin(),
					a.begin() + n / 2,
					a.end());

		// Applying nth_element
		// on (n-1)/2 th index
		nth_element(a.begin(),
					a.begin() + (n - 1) / 2,
					a.end());

		// Find the average of value at
		// index N/2 and (N-1)/2
		return (double)(a[(n - 1) / 2]
						+ a[n / 2])
			   / 2.0;
	}

	// If size of the arr[] is odd
	else {

		// Applying nth_element
		// on n/2
		nth_element(a.begin(),
					a.begin() + n / 2,
					a.end());

		// Value at index (N/2)th
		// is the median
		return (double)a[n / 2];
	}
}

//need to change to sliding window, travels window size by window size, instead of centered on pixel.
//also consider using random pivot, or keep the window size at 5.


//new alg
int randomMedian(vector<int>& window) {
	sort(window.begin(), window.end());
	int n = window.size();
	return window[n / 2];
}

// starting from a pixel, convert it to a 1D vector with size n,

// if the window size excess the column size, alter the size to be the difference between the potential end of window and the size of width
// do the same for the bottom
// then take the median of the window, replace pixel with the median.
void medianFilter(vector<vector<int>>& input, int windowSize, double& step){
	// write code to get a pixel window of size n with the current pixel as the center.
	// this pixel window should consider the row and column numbers.
	int startDex = floor(windowSize / 2); // needs better name
	int median;

	//NEW idea
	for (int i = 0; i < input.size(); i++) {
		for(int j = 0; j < input[i].size(); j++) {
			vector<int> v2;
			/*if (j + windowSize <= input[i].size() || i + windowSize <= input[i].size()) {
				toVect(input, i, j, windowSize, v2);
			}
			else if(j + windowSize >= input[i].size()) {
				toVect(input, i, j, (windowSize + j) - input[i].size(), v2);
			}
			else if (i + windowSize > input.size()) {
				toVect(input, i, j, (windowSize + i) - input.size(), v2);
			}*/
/*
			for (int k = i; k < i + windowSize && k < input.size(); k++) {
				for (int l = j; l < j + windowSize && l < input[i].size(); l++) {
					v2.push_back(input[k][l]);
				}
			}
			//median = medOfMed(v2, v2.size(), windowSize, step);
			median = randomMedian(v2);
			input[i][j] = median;
		}
	}
*/
	/*for(int i = 0; i < input.size(); i++){
		for(int j = 0; j < input[i].size(); j++){
			if(i - startDex >= 0 && i + startDex <= input.size() && i + startDex > input.size() && j + startDex <= input[i].size() && j - startDex >= 0){
				// copy values from window to 1d vector
				toVect(input, i - startDex, j - startDex, windowSize, v2);
				// perform median of medians on the 1d vector
				median = medOfMed(v2, v2.size(), windowSize, step);
				//median = findMedian(v2, windowSize);
				// push the new median of medians to output vector.
				input[i][j] = median;
				//cout << i << "," << j << " = " << median << endl;
			}
			else if(i - startDex < 0 || j - startDex < 0){
			    toVect(input, 0, j, windowSize, v2);

			    median = medOfMed(v2, v2.size(), windowSize, step);
				//median = findMedian(v2, windowSize);
				// push the new median of medians to output vector.
				input[i][j] = median;
			}
			//bottom
			else if(i + startDex > input.size()){
			    if(j + startDex > input[i].size()){
			        toVect(input, i - startDex, j - startDex , windowSize, v2);
			    }
			    else if(j - startDex < 0){
			        toVect(input, i - startDex, 0, windowSize, v2);
			    }
			    else toVect(input, i - startDex, j , windowSize, v2);

				// perform median of medians on the 1d vector
				median = medOfMed(v2, v2.size(), windowSize, step);
				//median = findMedian(v2, windowSize);
				// push the new median of medians to output vector.
				input[i][j] = median;
			}
            //right side
            else if(j + startDex > input[i].size()){
                toVect(input, i, j, windowSize, v2);
				// perform median of medians on the 1d vector
				median = medOfMed(v2, v2.size(), windowSize, step);
            	//median = findMedian(v2, windowSize);
				// push the new median of medians to output vector.
				input[i][j] = median;
            }
            else if(j - startDex < input[i].size()){
                toVect(input, i, j, windowSize, v2);
				// perform median of medians on the 1d vector
				median = medOfMed(v2, v2.size(), windowSize, step);
            	//median = findMedian(v2, windowSize);
				// push the new median of medians to output vector.
				input[i][j] = median;
            }

			else{
			    v2.clear();
			}
		}
	}*/
//}


/*
//method officially works.
//works for smaller file sizes
//TODO if file is not txt file, throw an error and return.
//TODO should also remove now unessacary code.
//remember it is jpg to pgm to txt.
void parseFile(const string& filename, vector<vector<int>>& image, string& header) {
	ifstream file(filename);
	string line;
	vector<int> r;
	int count = 0;

	// Read the first line (header)
	if (getline(file, line)) {
		header = line;
	}

	// Extract width from header
	int width = stoi(line.substr(line.find(':') + 2, 1)); // Assuming the width is a single digit
	int numRows = 0;

	// Loop through each line in the file
	while (getline(file, line)) {
		// Extract the number inside the parentheses (substring between '(' and ')')
		string temp = line.substr(line.find('#'), line.size() - 1);
		string num = temp.substr(temp.find('(') + 1, temp.find(')') - temp.find('(') - 1);
		int  nume = stoi(num);

		size_t startPos = line.find('(');
		size_t endPos = line.find(')');

		// If parentheses are found, extract the number inside
		if (startPos != string::npos && endPos != string::npos) {
			string numberStr = line.substr(startPos + 1, endPos - startPos - 1);

			// Convert the string to an integer
			int number = std::stoi(numberStr);

			// Find the comma position to split row and column
			size_t commaPos = line.find(',');
			int row = stoi(line.substr(commaPos + 1)); // Parse row
			int col = stoi(line.substr(0, commaPos));  // Parse column

			// Ensure that the image vector has enough rows
			if (row >= image.size()) {
				image.resize(row + 1);
			}

			// Add the number to the appropriate row
			image[row].push_back(nume);

			// Manage row and column count for handling full rows
			count++;
			if (count == width) {
				count = 0;
				r.clear(); // Clear row after reaching width
			}
		}
	}
	file.close();
}

//for file name pass in full file path to storage location including the extension(txt).
//TODO consider possibly writing updated info directly to a pgm file. IT WORKS, IT WORKS!!!!

//only the name and the path and extension are needed.
void writeFile(const string fileName, const vector<vector<int>> data, const string header) {
	ofstream file(fileName);
	//file << header << endl;
	string input;
	// sample input.
	file << "P2" << endl;
	file << data[0].size() << " " << data.size() << endl;
	file << "255" << endl;

	for(int i = 0; i < data.size(); i++) {
		for(int j = 0; j < data[i].size(); j++) {
			/*string index = to_string(j) + "," + to_string(i);
			string value = to_string(data[i][j]) + "," + to_string(data[i][j]) + "," + to_string(data[i][j]);
			string hexa = toHex(data[i][j]);

			input = index + ": (" + value + ")  #" + hexa + "  gray(" + value + ")";
			file << input << endl;*/

			//sample writing to PGM test.

			/*file << data[i][j] << " ";

		}

		file << endl;
	}
}
*/
/*
void massFiltering(vector<string> names, string inFilePath, string outFilePath, string fileExtension, int windowSize){
	double step = 0;
	for(int i = 0; i < names.size(); i++) {
		vector<vector<int>> image;
		//call to parse file
		string header;
		parseFile(inFilePath + "/" + names[i] + "." + fileExtension,image, header);
		//call to median filtering
		medianFilter(image, windowSize, step);
		//call to file writing
		writeFile(outFilePath + "/" + names[i] + ".pgm",image, header);
	}
}
*/
//TODO remove commeted out code from this file.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
	//TODO convert chrystler2noise to jpg then pgm, to fix its problem.
	//TODO some images already had noise redu steps except for adding noise.
	//maybe consider running alg on already process images>
	vector<string> names = {"nose-noisedimage", "chrstler2noise", "chrystlernoised", "bbridgenoised", "ny80snoised", "archnoised", "spaceneedlenoise", "indy500noised", "overlookhotelnoised", "twilightzonenoised", "woodstock69noised", "titanicnoised", "oldmannoise", "oldcar", "oldtypewriter", "oldfarmhouse", "lamp", "shadows", "olympusnoisy", "cemetary"};
	vector<int> sizes = {5000, 8000, 10000};
	cout << names.size() << endl;
	auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";
	string header;
	vector<vector<int>> im;
	vector<int> rand;
	double s = 0;
	randomInput(rand, 50);
	sort(rand.begin(), rand.end());
	for (int i  = 0; i < rand.size(); i++) {
		cout << rand[i] << " ";
	}
	cout << endl;
	cout << selection(rand, 0, rand.size(), 3,s) << endl;
	//parseFile("C:/Users/Owner/CLionProjects/secondtest/test.txt",im, header);
	//massFiltering(names, "C:/Users/Owner/CLionProjects/secondtest/inputs", "C:/Users/Owner/CLionProjects/secondtest/outputs", "txt", 3);

	//medianFilter(im, 5, s);
	//writeFile("C:/Users/Owner/CLionProjects/secondtest/output.pgm", im, header);
	//instances(sizes, 5);

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

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.