#include <iostream>
#include <sstream>
#include <string>
#include "ydogukan_Yildirim_Dogukan_hw3_SubSeqsList.h"

using namespace std;

int main() {

	string line;
	cout << "Please enter the numbers in a line: ";
	getline(cin, line);
	cout << endl;

	// Creating temporary stringstream and integer variable to check whether the given line is empty
	// i.e. checking if the given line has no numbers
	istringstream temp(line);
	int tempNumber;

	if (!(temp >> tempNumber)) { // if no integer could be put into the integer variable, i.e. if it was empty, print the error line
		SubSeqsList tempList;
		tempList.displayList();
		return 0;
	}

	SubSeqsList list;
	istringstream numbers(line);
	int number;
	
	while (numbers >> number) { // number by number from the sstream
		if (number >= 0) {
			if (!list.numberExistsInList(number)) {
				list.insertSubSeqs(number); // insert one or more subsequences
			}
		}
		
		else {
			list.deleteSubSeqs(-number); // delete one or more subsequences
		}
	}

	list.displayList(); // print the whole list
	list.deleteList(); // delete the whole list

	return 0;
}