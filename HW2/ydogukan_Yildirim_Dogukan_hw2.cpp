#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct node { // linked list as main data structure
	int value;
	node* next;

	node(){}

	node(int number, node* link) {
		value = number;
		next = link;
	}
};

/* Begin: code taken and updated from linkedList.cpp */
bool existsInList(node* head, int number) { // checks whether a given value exists in a given list
	while (head != NULL) {
		if (head->value == number) {
			return true;
		}
		head = head->next;
	}
	return false;
}
/* End: code taken and updated from linkedList.cpp */

/* Begin: code taken from ptrfunc.cpp */
void deleteNode(node* toBeDeleted, node*& head) { // deletes a given node from a given list
	node* ptr;

	if (toBeDeleted == head) { // if the node to be deleted is the first node
		head = head->next;
		delete toBeDeleted;
	}

	else { // if the node to be deleted is in the middle or at the end
		ptr = head;

		while (ptr->next != toBeDeleted) {
			ptr = ptr->next;
		}
		// after while ptr point to the node just before toBeDeleted

		// connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}
/* End: code taken from ptrfunc.cpp */

void deleteNodesWithOrder(node*& head, int number, string order) { // deletes multiple nodes in a given list with respect to the order
	cout << "Deleted nodes:";
	node* ptr = head;
	bool deleted = false; // no node is deleted

	if (order == "A") { // if the order is 'ascending'
		while (ptr != NULL) {
			node* nextNode = ptr->next; // saving the next node temporarily, as the next node won't be accessible from the current node after deletion
			if (ptr->value > number) { // if the value of the node is larger than the given number
				deleted = true; // at least one node is deleted from the list
				cout << " " << ptr->value;
				deleteNode(ptr, head);
			}
			ptr = nextNode; // pointer points to the next node
		}
	}

	else { // if the order is 'descending'
		while (ptr != NULL) {
			node* nextNode = ptr->next; // saving the next node temporarily, as the next node won't be accessible from the current node after deletion
			if (ptr->value < number) { // if the value of the node is smaller than the given number
				deleted = true; // at least one node is deleted from the list
				cout << " " << ptr->value;
				deleteNode(ptr, head);
			}
			ptr = nextNode; // pointer points to the next node
		}
	}

	if (!deleted) { // if none of the nodes is deleted
		cout << " None";
	}

	cout << endl;
}

void addNodeToEnd(node* & head, int number) { // given a value, adds a node with that value to the end of a given list
	node* nodeToBeAdded = new node(number, NULL); // constructing a new node with the given number
	node* tail = head;

	if (head == NULL) { // if the list is empty
		head = nodeToBeAdded;
	}

	else { // if the list is not empty
		while (tail->next != NULL) { // go to end of the list
			tail = tail->next;
		}

		tail->next = nodeToBeAdded; // add the node to the end of the list
	}

	cout << "Appended: " << number << endl;
}

/* Begin: code taken and updated from ptrfunc.cpp */
void displayList(node* head) { // displays the contents of a given list
	cout << "List content: ";
	node* ptr = head;
	while (ptr != NULL) {
		cout << ptr->value << " ";
		ptr = ptr->next;
	}
	cout << endl << endl;
}
/* End: code taken and updated from ptrfunc.cpp */

/* Begin: code taken and updated from linkedList.cpp */
void deleteList(node* head) { // Deletes all elements of a given list
	cout << "All the nodes are deleted at the end of the program:";
	node* ptr;

	while (head != NULL){
		ptr = head;
		cout << " " << head->value;
		head = head->next;
		delete ptr;
	}
	
	cout << endl;
}
/* End: code taken and updated from linkedList.cpp */

int main()
{
	string order;
	cout << "Please enter the order mode (A/D): ";
	cin >> order;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (order != "A" && order != "D") {
		cout << "Please enter the order mode again (A/D): ";
		cin >> order;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	string line;
	cout << "Please enter the numbers in a line: ";
	getline(cin, line);
	cout << endl;

	// Creating temporary stringstream and integer variable to check whether the given line is empty
	// i.e. checking if the given line has no numbers
	istringstream temp(line);
	int tempNumber;

	if (!(temp >> tempNumber)) { // if no integer could be put into the integer variable, i.e. if it was empty, print the error line
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
		return 0;
	}

	istringstream numbers(line);
	int number;
	node* head = NULL; // creating an empty list

	while (numbers >> number) { // number by number from the sstream
		cout << "Next number: " << number << endl;

		if (!existsInList(head, number)) { // if the given number does not exist in the list
			deleteNodesWithOrder(head, number, order); // delete nodes according to the ascending/descending order rules
			addNodeToEnd(head, number); // add a note with the given number to the end
		}

		else {
			cout << number << " is already in the list!" << endl;
		}

		displayList(head); // display the contensts of the list
	}

	deleteList(head); // delete the list at the end of the program so my grades are not lowered

	return 0;
}