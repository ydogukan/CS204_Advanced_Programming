#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string getSuccessMsg(string word, int rowIndex, int colIndex, string direction, string orientation) {		// Returns the message for a word successfully put into a matrix
	return '\"' + word + '\"' + " was put into the matrix with given starting point: " + to_string(rowIndex) + ',' + 
		to_string(colIndex) + " direction: " + direction + " orientation: " + orientation;
}

string getErrorMsg(string word, int rowIndex, int colIndex, string direction, string orientation) {		// Returns the message for a word that could not be put into a matrix
	return '\"' + word + '\"' + " could not be put into the matrix with given starting point: " + to_string(rowIndex) + ',' + 
		to_string(colIndex) + " direction: " + direction + " orientation: " + orientation;
}

void displayMat(const vector<vector<char>>& mat) {		// Prints a given matrix
	for (unsigned int i = 0; i < mat.size(); i++) {
		for (unsigned int j = 0; j < mat[0].size(); j++) {
			cout << mat[i][j] << '\t';
		}
		cout << endl;
	}
}

int main() {

	// Getting the name of the file, opening it, checking if opening the said file failed etc.
	string fileName;
	cout << "Please enter the name of the file: ";
	cin >> fileName;

	ifstream input;
	input.open(fileName);
	
	while (input.fail()) {
		cout << "File name is incorrect, please enter again: ";
		cin >> fileName;
		input.open(fileName);
	}

	// Getting the number of rows and columns for the matrix that is going to be initialized, while also checking whether they are negative
	string line;
	getline(input, line);
	istringstream nums(line);
	int rows, cols;
	nums >> rows >> cols;

	if (rows <= 0 || cols <= 0) {
		cout << "Invalid number for row and/or column!" << endl;
		return 0;
	}

	vector<vector<char>> mat(rows, vector<char>(cols, '-'));

	// Reading the file line by line
	while (getline(input, line)) {
		// Streaming the line to 5 elements that will be used for letter placement
		istringstream elements(line);
		string word, orientation, direction;
		int rowIndex, colIndex;

		elements >> word >> rowIndex >> colIndex >> direction >> orientation;

		// If less than 5 elements are in the line (which would mean that stringstream failed) OR there are more than 5 elements:
		if (elements.fail() || !elements.eof()) {
			cout << "Invalid line! Number of values is different than 5." << endl;
			continue;
		}

		// Checking if the starting indexes are out of range
		if (rowIndex < 0 || rowIndex >= rows || colIndex < 0 || colIndex >= cols) {
			cout << "Starting point is out of range! Point: " << rowIndex << ',' << colIndex << endl;
			continue;
		}

		// Input checking the direction
		if (direction.length() > 1 || (direction != "r" && direction != "l" && direction != "u" && direction != "d")) {
			cout << "Invalid input for direction! Direction: " << direction << endl;
			continue;
		}

		// Input checking the orientation
		if (orientation != "CW" && orientation != "CCW") {
			cout << "Invalid input for orientation! Orientation: " << orientation << endl;
			continue;
		}

		// Creating the success and error messages with the given starting elements (starting points, direction and orientation) for future use
		string successMsg = getSuccessMsg(word, rowIndex, colIndex, direction, orientation);
		string errorMsg = getErrorMsg(word, rowIndex, colIndex, direction, orientation);

		// Initializing a copy of the original matrix so that we can go back to the previous matrix if a word could not fit to the original matrix
		vector<vector<char>> preMat(rows, vector<char>(cols));
		preMat = mat;

		// Checking if the starting point is empty
		if (mat[rowIndex][colIndex] != '-') {
			cout << errorMsg << endl;
			displayMat(mat);
			continue;
		}

		// Assigning the first letter of the word to the starting point, then initializing the variables needed for the placement algorithm
		mat[rowIndex][colIndex] = word.at(0);
		unsigned int letterIndex = 1, errorCount = 0;
		string startDirection = direction;

		// The Placement Algorithm, starting from the second letter
		// If the errorCount is equal to 4, that would mean that all four directions are unavailable for letter placement
		while (letterIndex < word.length() && errorCount < 4) {
			if (direction == "r") {
				// If the next right position is out of range OR next right position is non-empty, change the direction according to the orientation
				// Each time there is a change of direction, the errorCount is incremented
				if (colIndex + 1 > cols - 1 || mat[rowIndex][colIndex + 1] != '-') {
					errorCount++;
					if (orientation == "CW") {
						direction = "d";
					}

					else {
						direction = "u";
					}
				}

				// If everything went the way as it's supposed to, i.e. a letter can be placed to the next right position, then 
				// the letter is placed to the next right position, and the error count is reset.
				else {
					colIndex++;
					mat[rowIndex][colIndex] = word.at(letterIndex);
					letterIndex++;
					errorCount = 0;
					
					// Since the letter placement is PREFERRED in the original/starting direction, if the current direction is not the original direction
					// the letter placement will be retried with the original direction, thus, the direction updated to the original/starting direction
					if (startDirection != direction) {
						direction = startDirection;
					}
				}
			}

			else if (direction == "l") {
				// If the next left position is out of range OR next left position is non-empty, change the direction according to the orientation
				if (colIndex - 1 < 0 || mat[rowIndex][colIndex - 1] != '-') {
					errorCount++;
					if (orientation == "CW") {
						direction = "u";
					}

					else {
						direction = "d";
					}
				}

				else {
					colIndex--;
					mat[rowIndex][colIndex] = word.at(letterIndex);
					letterIndex++;
					errorCount = 0;

					if (startDirection != direction) {
						direction = startDirection;
					}
				}
			}

			else if (direction == "u") {
				// If the next up position is out of range OR next up position is non-empty, change the direction according to the orientation
				if (rowIndex - 1 < 0 || mat[rowIndex - 1][colIndex] != '-') {
					errorCount++;
					if (orientation == "CW") {
						direction = "r";
					}

					else {
						direction = "l";
					}
				}

				else {
					rowIndex--;
					mat[rowIndex][colIndex] = word.at(letterIndex);
					letterIndex++;
					errorCount = 0;

					if (startDirection != direction) {
						direction = startDirection;
					}
				}
			}

			else if (direction == "d") {
				// If the next down position is out of range OR next down position is non-empty, change the direction according to the orientation
				if (rowIndex + 1 > rows - 1 || mat[rowIndex + 1][colIndex] != '-') {
					errorCount++;
					if (orientation == "CW") {
						direction = "l";
					}

					else {
						direction = "r";
					}
				}

				else {
					rowIndex++;
					mat[rowIndex][colIndex] = word.at(letterIndex);
					letterIndex++;
					errorCount = 0;

					if (startDirection != direction) {
						direction = startDirection;
					}
				}
			}
		}

		// If there are no errors, i.e. all letters could be placed without all four directions becoming unavailable, display success message
		// NOTE: The error count can only be 0 or 4 at this stage
		if (errorCount == 0) {
			cout << successMsg << endl;
		}

		// If the error count is 4, meaning if all four directions were unavailable for letter placement, display error message
		// Then all the letters of the said word placed so far are deleted from the matrix by going back to the previous matrix, 
		// which is the matrix before any changes were made according to the current line
		else if (errorCount >= 4) {
			cout << errorMsg << endl;
			mat = preMat;
		}

		displayMat(mat);
	}

	input.close();

	// Written by Dogukan Yildirim
	return 0;
}