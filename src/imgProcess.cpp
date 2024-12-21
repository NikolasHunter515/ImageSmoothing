//
// Created by Nikolas on 12/11/2024.
//
#include "imgProcess.h"
using namespace std;

//TODO consider writing method to filter color images.
//method may use struct or object, in a threaded enviornment.

//jpg to pgm to txt.
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

//extension of a file does not need to be pass.
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
        	//writes to PGM file
            file << data[i][j] << " ";

        }

        file << endl;
    }
}

void medianFilter(vector<vector<int>>& input, int windowSize, double& step){
	int startDex = floor(windowSize / 2); // needs better name
	int median;

	//uses sliding window, and random pivot to filter.
	for (int i = 0; i < input.size(); i++) {
		for(int j = 0; j < input[i].size(); j++) {
			vector<int> v2;
			for (int k = i; k < i + windowSize && k < input.size(); k++) {
				for (int l = j; l < j + windowSize && l < input[i].size(); l++) {
					v2.push_back(input[k][l]);
				}
			}
			median = randomMedian(v2);
			input[i][j] = median;
		}
	}
}

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

//TODO consider writing method to filter image multiple times, or overload existing method.