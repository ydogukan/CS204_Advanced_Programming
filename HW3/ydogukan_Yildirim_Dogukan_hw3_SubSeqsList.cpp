#include <iostream>
#include "ydogukan_Yildirim_Dogukan_hw3_SubSeqsList.h"

using namespace std;

SubSeqsList::SubSeqsList() { // default constructor that creates an empty list
	hHead = NULL;
}

bool SubSeqsList::numberExistsInList(int number) {
	// Given a number, returns true if the number exists in the list

	SubSeqHeadNode* head = hHead;

	while (head != NULL && head->size == 1) { // checking only the size 1 subsequences is enough
		if (numberExistsInSubSeq(number, head)) { // checks if the number exists in a given subsequence
			cout << number << " is already in the list!" << endl;
			return true;
		}

		head = head->next;
	}

	return false;
}

void SubSeqsList::insertSubSeqs(int number) {
	// Given a number, inserts one or more subsequences to the list in a sorted way

	if (hHead == NULL) { // if the list is empty
		SubSeqNode* subSeq = new SubSeqNode(number, NULL);
		hHead = new SubSeqHeadNode(1, subSeq, NULL);
	}

	else {

		// Inserting the given number to the list first as a subsequence with size 1
		SubSeqNode* subSeq = new SubSeqNode(number, NULL);
		SubSeqHeadNode* subSeqHead = new SubSeqHeadNode(1, subSeq, NULL);
		hHead = addSorted(subSeqHead);

		// Inserting other subsequences with sizes other than 1
		SubSeqHeadNode* head = hHead;

		while (head != NULL) {
			if (numberIsLargerThanEntireSubSeq(number, head)) {
				hHead = addSorted(getSubSeq(number, head));
			}
			head = head->next;
		}
	}

	cout << "Subsequence(s) containing " << number << " has/have been added" << endl;
}

void SubSeqsList::deleteSubSeqs(int number) {
	// Given a number, deletes all subsequences that include this number

	SubSeqHeadNode* head = hHead;
	bool deleted = false;

	while (head != NULL) {
		SubSeqHeadNode* nextSubSeqHead = head->next;
		if (numberExistsInSubSeq(number, head)) { // if number exists in the given subsequence
			deleteSubSeqNodes(head->sHead); // deletes the contents of the subsequence
			deleteSubSeqHeadNode(head, hHead); // deletes the head of the subsequence
			deleted = true;
		}

		head = nextSubSeqHead;
	}

	if (!deleted) {
		cout << "There is no subsequence that contains " << number << " to be deleted" << endl;
	}

	else {
		cout << "All subsequence(s) containing " << number << " has/have been deleted" << endl;
	}
}

void SubSeqsList::displayList() { // displays the whole content of the list
	SubSeqHeadNode* head = hHead;

	cout << endl << "FINAL CONTENT" << endl;

	if (head == NULL) {
		cout << "List is empty!" << endl;
	}

	else {
		while (head != NULL) {
			cout << head->size << " | ";
			SubSeqNode* subSeq = head->sHead;
			cout << subSeq->value;
			subSeq = subSeq->next;

			while (subSeq != NULL) {
				cout << " --> " << subSeq->value;
				subSeq = subSeq->next;
			}

			cout << endl;
			head = head->next;
		}
	}
}

void SubSeqsList::deleteList() { // deletes the whole list
	SubSeqHeadNode* subSeqHead;

	while (hHead != NULL) {
		subSeqHead = hHead;
		hHead = hHead->next;
		deleteSubSeqNodes(subSeqHead->sHead);
		delete subSeqHead;
	}
}

bool SubSeqsList::numberExistsInSubSeq(int number, SubSeqHeadNode* head) {
	// Given a subsequence, returns true if a given number exists in that subsequence

	SubSeqNode* subSeq = head->sHead;

	while (subSeq != NULL) {
		if (subSeq->value == number) {
			return true;
		}

		subSeq = subSeq->next;
	}

	return false;
}

/* Begin: code taken and updated from ptrfunc.cpp */
SubSeqHeadNode* SubSeqsList::addSorted(SubSeqHeadNode* subSeq) {
	// Given a subsequence, insert it into the sorted sub sequence list
	// while keeping the list sorted, then return the head of the new list

	if (hHead == NULL) { // if the subsequence list is empty
		return subSeq;
	}

	SubSeqHeadNode* loopSubSeq = hHead; // loop subsequence
	SubSeqHeadNode* prev = NULL; // to point to the previous subsequence

	while (loopSubSeq != NULL && loopSubSeq->size <= subSeq->size) {
		// loop until one of these conditions: the loop subsequence is empty or
		// loop subsequence has more elements than the subsequence that is going to be inserted
		// or the subsequence that is going to be inserted is smaller than the loop subsequence

		if (loopSubSeq->size == subSeq->size && firstSubSeqIsLargerInValue(loopSubSeq->sHead, subSeq->sHead)) {
			break;
		}

		prev = loopSubSeq;
		loopSubSeq = loopSubSeq->next;
	} // postcondition: given sub sequence to be inserted between prev and loopSubSeq

	if (prev == NULL) {
		subSeq->next = hHead;
		return subSeq;
	}

	prev->next = subSeq;
	subSeq->next = loopSubSeq;

	return hHead;
}
/* End: code taken and updated from ptrfunc.cpp */

bool SubSeqsList::firstSubSeqIsLargerInValue(SubSeqNode* firstSubSeq, SubSeqNode* secondSubSeq) {
	// Given two subsequences that have the same number of elements, 
	// return true if the first subsequence is larger in value, else return false
	// Being larger in value means that 1 -> 2 -> 3 is larger than 1 -> 1 -> 3
	// You can think of it as comparing numbers, i.e. 123 is larger than 113

	while (firstSubSeq != NULL && secondSubSeq != NULL) {
		if (firstSubSeq->value > secondSubSeq->value) {
			return true;
		}

		else if (firstSubSeq->value < secondSubSeq->value) {
			return false;
		}

		else {
			firstSubSeq = firstSubSeq->next;
			secondSubSeq = secondSubSeq->next;
		}
	}
}

bool SubSeqsList::numberIsLargerThanEntireSubSeq(int number, SubSeqHeadNode* head) {
	// Given a subsequence, returns true if a given number is larger than all the
	// numbers in the subsequence

	SubSeqNode* ptr = head->sHead;

	while (ptr != NULL) {
		if (ptr->value >= number) {
			return false;
		}

		ptr = ptr->next;
	}

	return true;
}

SubSeqHeadNode* SubSeqsList::getSubSeq(int number, SubSeqHeadNode* head) {
	// Given a subsequence, makes a copy of the subsequence and returns the copy
	// of that subsequence with a given number added to the end of it

	SubSeqNode* ptr = head->sHead;
	SubSeqNode* subSeq = new SubSeqNode(ptr->value, NULL);
	SubSeqNode* subSeqHead = subSeq;

	while (ptr->next != NULL) {
		subSeq->next = new SubSeqNode(ptr->next->value, NULL);
		subSeq = subSeq->next;
		ptr = ptr->next;
	}

	subSeq->next = new SubSeqNode(number, NULL);

	return new SubSeqHeadNode(head->size + 1, subSeqHead, NULL);
}

/* Begin: code taken and updated from linkedList.cpp */
void SubSeqsList::deleteSubSeqNodes(SubSeqNode* head) { // deletes the contents of the subsequence
	SubSeqNode* ptr;

	while (head != NULL) {
		ptr = head;
		head = head->next;
		delete ptr;
	}
}
/* End: code taken and updated from linkedList.cpp */

/* Begin: code taken from ptrfunc.cpp */
void SubSeqsList::deleteSubSeqHeadNode(SubSeqHeadNode* toBeDeleted, SubSeqHeadNode*& head) { // deletes the head of the subsequence
	SubSeqHeadNode* ptr;

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