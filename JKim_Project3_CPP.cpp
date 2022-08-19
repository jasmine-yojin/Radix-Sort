#include <iostream>
#include<fstream>
#include <string.h>

using namespace std;

class ListNode {	
	
	int data;
	ListNode *next;
	
	friend class LLStack;
	friend class LLQueue;
	friend class RadixSort;
	
	public:
	
	ListNode (){
		data = 0;
		this->next = NULL;
	}
	
	ListNode(int n){
		data = n;
		this->next = NULL;
	}
	
	void printNode (ListNode *node, fstream& outFile1){
		if(node->next == NULL){
			outFile1<<"("<<node->data<<",NULL)->NULL";
		}else{
			outFile1<<"("<<node->data<<","<<node->next->data<<")->";	
		}
	}
};

class LLStack {

	ListNode *top;
	friend class RadixSort;

	public:
	LLStack (int number){
		top = new ListNode (number);		
	}
	
	bool isEmpty (){
		return top->next==NULL;
	}
	
	void push (ListNode *newNode){
		newNode->next = top->next;
		top->next = newNode;
	}
	
	void buildStack (ifstream& inFile, int offSet){
		int num;
		while (!inFile.eof()){
			inFile>>num;
			num= num + offSet;
			ListNode* newNode = new ListNode(num);
			push (newNode);						
		}
	}
	
	ListNode *pop (){
		if (isEmpty()) return NULL;
		else{
			ListNode* toRemove = top->next;
			top->next = toRemove->next;
			toRemove->next = NULL;
			
			
			return toRemove; 
		}
	}
	
	void printStack (fstream& outFile2){
		
		ListNode* p = top;
		outFile2<<"Top->";
		while (p!=NULL){
			p->printNode (p, outFile2);
			
			
			p= p->next;
		}
		
	}
	
};

class LLQueue {
	 
	ListNode *head;
	ListNode *tail;
	int size =0;
	
	friend class RadixSort;
	
	public:
	LLQueue (int number){
		head = new ListNode (number);
		tail = head;
		
	}
	
	void insertQ (ListNode *newNode){
		tail->next = newNode;
		tail = newNode;	
		size++;	
	}
	
	void buildQueue (int num){
				
		
		ListNode* newNode = new ListNode(num);
		insertQ (newNode);
			
		
	}
	
	ListNode *deleteQ (){
		if (isEmpty()) return NULL;
		else{
			ListNode* toRemove = head->next;
			head->next = toRemove->next;
			toRemove->next = NULL; 
			
			size--;
			//***OMG***
			if (head->next==NULL) tail= head;
			return toRemove;		
		}
	
	}
	
	bool isEmpty (){
		return size==0;
	}
	
	void printQueue (int whichTable, int index, fstream& outFile2){
		ListNode* p = head;
		outFile2<<"\nTable["<<whichTable<<"]["<<index<<"]: ";
		while (p!=NULL){
			p->printNode(p, outFile2);
			p= p->next; 
		}
	}
	
};

class RadixSort {
	int tableSize =10;
	LLQueue* hashTable[2][10];
	int data;
	int currentTable;
	int previousTable;
	int numDigits;
	int offSet;
	int currentPosition;
	int currentDigit;	
	
	public:
	RadixSort (){
				
		for (int i = 0; i<2; i++){
			for (int j=0; j<10; j++){
				hashTable[i][j] = new LLQueue (-9999);
			}
		}
	}	
	
	void printTable (int whichTable, fstream& outFile2){
		LLQueue* queue;
		outFile2<<endl;
		for (int j=0; j<10; j++){
				queue = hashTable [whichTable][j];
			if (!queue->isEmpty()){
				queue = hashTable [whichTable][j];
				queue->printQueue(whichTable, j, outFile2);
			}
		}
				
	}
	
	void RSort (LLStack *s, fstream& outFile2, fstream& outFile1){
		outFile2<<"\n\n***Performing RSort"<<endl;
		currentPosition =0;
		currentTable =0;
		int currentQueue=0;
		//Step2- moving the stack to the first table 0 based on the rightmost digit
		moveStack (s, currentPosition, currentTable);
		//Step3
		outFile2<<"Initial hashTable:";
		printTable (currentTable, outFile2);
		//Step4
		currentPosition++;
		currentTable =1;
		previousTable=0;
		currentQueue=0;
		int hashIndex;
		LLQueue* cqueue;
		LLQueue* targetQueue;
		ListNode* newNode;
		
		
		while(currentPosition<numDigits) {	
			while (currentQueue<tableSize){
				cqueue= hashTable[previousTable][currentQueue];
				while(!(cqueue->isEmpty())){ 
				 	newNode = cqueue->deleteQ();
					hashIndex = getDigit (newNode->data, currentPosition);
					targetQueue = hashTable[currentTable][hashIndex];
					targetQueue->buildQueue(newNode->data);
				}
				
				currentQueue++;
			}
			
			printTable (currentTable, outFile2);
			previousTable = currentTable;
			currentTable = (currentTable+1)%2;
			currentPosition++;
			currentQueue=0;
			
		}
			
		printSortedData (previousTable, outFile1);
			
	}
	
	void printSortedData (int whichTable, fstream& outFile1){
		ListNode* p;
		int finalNumber;
		for(int i=0;i<10;i++){
			if(hashTable[whichTable][i]->head->next!=NULL){
				p = hashTable[whichTable][i]->head->next;
				while (p!=NULL){
					finalNumber = p->data - offSet;
					outFile1<<finalNumber<<endl;
					p= p->next;
				}	
			}           	
		}
	}
	
	void firstReading (ifstream& inFile, fstream& outFile2){
		// Read from input file; determine the largest and smallest integers in the file
		// and establishes offset
		outFile2<<"\n***Performing firstReading"<<endl;
		int smallest = 0;
		int largest =0;
		
		while (!inFile.eof()){
			inFile>>data;
			if (data < smallest) smallest = data;
			if (data > largest) largest = data; 
		}
		
		if (smallest < 0){
			offSet = abs (smallest);
		}else {
			offSet =0;
		}
		
		largest = largest + offSet;
		numDigits = getLength (largest);
		
		outFile2<<"Largest: "<<largest<<" Smallest: "<<smallest<<" Offset: "<<offSet<<" Number of Digits: "<<numDigits<<endl;
		
	}
	
	
	
	LLStack *loadStack (ifstream& inFile, fstream& outFile2){
		outFile2<<"\n***Performing loadStack"<<endl;
		LLStack* s = new LLStack (-9999);
		s->buildStack(inFile, offSet);
		
		return s;
		
	}
	
	
	
	void moveStack (LLStack*s, int currentPosition, int currentTable){
		int hashIndex;
		ListNode* newNode;
		int poppedNumber;
		
		while (!s->isEmpty()){
			poppedNumber = s->pop()->data;
			newNode = new ListNode (poppedNumber);
			hashIndex = getDigit (newNode->data, currentPosition);
			hashTable[currentTable][hashIndex]->insertQ(newNode);
		}
	}
	
	int getLength (int data){
		int count =0;
		char buffer [10];
		
		itoa(data, buffer,10);
		
		while (buffer[count]!= '\0'){
			count++;
		}
		
		return count;
	}	
	
	int getDigit (int data, int currentPosition){
		int mirrorDigit;
		char buffer [10];
		int number;
		char letter;
		
		itoa (data, buffer, 10);
		if (currentPosition+1 > strlen(buffer)){
			return 0;
		}else{
			mirrorDigit = strlen(buffer)- currentPosition - 1;
			letter = buffer[mirrorDigit];
			number =letter - '0';
			
			return number;	
		}
				
}
	
	
	
	
};

int main(int argc, const char *argv[]){
	//parameter Data1.txt outFile1(Data1).txt outFile2(Data1).txt
	//parameter Data2.txt outFile1(Data2).txt outFile2(Data2).txt
	//outFile1: result
	//outFile2: debugging
	
	//Step 0: 	
	ifstream inFile;
	inFile.open(argv[1]);
	
	fstream outFile1;
	fstream outFile2;
	outFile1.open(argv[2], ios::out);
	outFile2.open(argv[3], ios::out);
	
	RadixSort test;
		
	//Step 1: firtReading (inFile, outFile2)
	test.firstReading(inFile, outFile2); 
	//Step 2:
	inFile.close();
	//Step 3: inFile <- Open the input file//open the file second time
	inFile.open(argv[1]);
	//STep 4: S <- loadStack (inFile, outFile2)
	LLStack * s = test.loadStack (inFile, outFile2);
	inFile.close();
	//Step 5: printStack (S,outFile2)
	s->printStack (outFile2);
	//Step6: RSort (S,outFile2);
	test.RSort (s,outFile2, outFile1);
	
	//Close all files
	outFile1.close();
	outFile2.close();

	return 0;	
}

