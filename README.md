# Radix-Sort
This program uses radix sort to sort data in Linked List, Stack, and Queue data structures.

<h2>Algorithm Steps for Implementing Radix Sort</h2>

<b>Step 0:</b> Create a ListNode class, LLStack class, LLQueue class, and RadixSort class. The stack will store the
data directly from the text file. The RadixSort class will contain a hash table that stores two arrays of
pointers to LinkedList queues. The arrays have 10 slots, with indexes from 0 to 9. The hash function is
identify function, so the index represent the digit that correspond to the current position. I have
mirrored the codes for LLStack and LLQueue from the project1. The major difference is that I have
removed the operator character action from the buildStack and buidQueue functions.<br>
<b>Step 1:</b> Define the RadixSort class. The RadixSort has the following fields: tableSize of 10 (to reflect digits
of 0 to 9), hash table (explained in step 2), data to hold the number read from the text file, currentTable
(0 or 1), previousTable (0 or1), numDigits (the length of the longest integer), offset (absolute value of
the smallest/most negative integer), currentPosition, and currentDigit. The following steps will specify
the major methods inside the RadixSort.<br>
<b>Step 2:</b> RadixSort () constructor. HashTable is a nested array of pointers to LLQueues. The first “layer”
represents two tables. Every time the sorting happens, the data will be moved from one table to
another and back and forth. The second layer is the pointers to the head pointer to the 10 queues.
Queue represent the digits from 0 to 9. To initialize the arrays, I used the key word “new” by using
nested loops.<br>
<b>Step 3:</b> void firstReading () This function determines the largest and smallest integers. The largest
integer determines how frequently the table will be changed and the smallest integer, when negative,
determines the offset. This absolute value of the negative integer “handles” the negative numbers so
the sorting algorithm could still work without modification.<br>
<b>Step 4:</b> int getLength(int data) This function determines the length of the largest integer. Strlen function
would also have done the trick. I just created an array of characters and stored the digits converted into
char from int. Then I had a counter increment in a while loop until the loop reached the end of the
length of the data or ‘0’.<br>
<b>Step 5:</b> int getDigit(int data, currentPosition) Since the RadixSort sort from the rightmost digit of the
integer to the left, this function takes the current position and returns the right digit from right to left. I
converted the number into a character array. Then I calculated the “reverse” of the position to find the
right index of the character array. Then convert the character back to an integer. If the number is
shorter than the position, return 0 to symbolize the “padding of the zeroes” in front of the number to
the left.<br>
<b>Step 6: </b>LLStack *loadStack loadStack obtains the list of numbers from the text file and pushes the data
onto the stack data structure. I modified the Stack class to take the offset as the parameter to be added
to each number. Void moveStack (LLStack*s, int currentPosition, int currentTable) This function pops the
data off the stack and store it inside the first hash table.<br>
<b>Step 7: </b>void RSort (LLStack *s, fstream& outFile2, fstream& outFile1) First, move the numbers into the
first hash table. Then the three while loops begin. The first while loop initiates the sorting of the entire
table as often as the length of the longest integer. The second loop looks at the each of the 10 queues
inside the table. The third while loop deletes the number from each queue then add it to the respective
queue of the next table until the queue is empty.<br>
<b>Step 8:</b> In main, open the data file and create and open two output files. Start the RadixSort class. Call
the first reading function, then loadStack function. Print out the stack to see if the data transferred
correctly from the text file. Then perform the sorting by calling the RSort method. Print out the result.
Then close all files. 

<h2>Illustration for Data 1</h2>

![](images/Ilustration.gif)

<h2>Illustration for Data 2</h2>
![](images/Ilustration2.gif)
![](images/Ilustration3.gif)
