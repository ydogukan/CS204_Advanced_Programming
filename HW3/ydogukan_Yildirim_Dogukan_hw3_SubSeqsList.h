#ifndef _SUBSEQSLIST_H
#define _SUBSEQSLIST_H

using namespace std;

struct SubSeqNode {
	int value;
	SubSeqNode* next;

	SubSeqNode()
	{}

	SubSeqNode(int number, SubSeqNode* link)
		: value(number), next(link)
	{}
};

struct SubSeqHeadNode {
	int size; // number of elements in the subsequence
	SubSeqNode* sHead; // head of the subsequence list
	SubSeqHeadNode* next;

	SubSeqHeadNode()
	{}

	SubSeqHeadNode(int number, SubSeqNode* subSeq, SubSeqHeadNode* link)
		: size(number), sHead(subSeq), next(link)
	{}
};

class SubSeqsList {
	public:
		SubSeqsList(); // default constructor that creates an empty list
		bool numberExistsInList(int number); // checks if a given number exists in the list
		void insertSubSeqs(int number); // insert subsequence(s) that have the given number
		void deleteSubSeqs(int number); // deletes subsequence(s) that have the given number
		void displayList(); // displays the contents of the list
		void deleteList(); // deletes the contents of the list
	private:
		SubSeqHeadNode* hHead;
		bool numberExistsInSubSeq(int number, SubSeqHeadNode* head);
		SubSeqHeadNode* addSorted(SubSeqHeadNode* subSeq);
		bool firstSubSeqIsLargerInValue(SubSeqNode* firstSubSeq, SubSeqNode* secondSubSeq);
		bool numberIsLargerThanEntireSubSeq(int number, SubSeqHeadNode* head);
		SubSeqHeadNode* getSubSeq(int number, SubSeqHeadNode* firstSubSeq);
		void deleteSubSeqNodes(SubSeqNode* head);
		void deleteSubSeqHeadNode(SubSeqHeadNode* toBeDeleted, SubSeqHeadNode*& head);
};

#endif