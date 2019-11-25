/*
Name: Carlos Castillo
Date: 11/19/19
Due Date: 11/20/19
Class: CIS 161 ME1
Project Name: Student Grade Analyzer
Program Explanation: This program analyzes
a classroom of students and their test scores.
It reads in the student IDs and their test scores from a file.  
It calculates their averages then it displays
all of the IDs, test scores, and averages.  Next, it displays
only the averages that are greater than 70. Next, it
sorts the students based on their averages, then searches for
values of 85, and displays only the students IDs with averages 
equal to or greater than 85.  It sorts the students based on 
their IDs and then allows the user to request an ID
which is searched for.  Finally, the program displays the
requested students ID, their test scores, and average and
asks the user if they want to look for another students
ID or not.*/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int SIZE = 20;

typedef struct Student
{
	int id_number;
	int test_score1;
	int test_score2;
	int test_score3;
	float test_average;
}Stud[SIZE];

void setData(Student *);
void displayAvgs(const Student *);
void bubbleSort(Student *);
int binarySearch(const Student *, const float &);
void displayHighAvgs(Student *);
void selectionSort(Student *);
void requestIDs(const Student *);

int main()
{
	Stud pccc_students; // defined an array of Student structures

	setData(pccc_students); 
	displayAvgs(pccc_students);
	displayHighAvgs(pccc_students);
	selectionSort(pccc_students);
	requestIDs(pccc_students);
	
	return 0;
}


/* This function is void because
it doesn't return a value.  It contains
one parameter which is a pointer that
points to an array of Student structures. A file
is opened and the pointer is used to read 
ID number and three test scores into each 
structure of the array. The file is closed
then the average for each student is calculated
and the pointer places each average in each 
structure of the array.  Finally, the pointer 
is used to display every students ID number, 
test scores, and average in each structure 
of the array. */
void setData(Student *ptr)
{
	ifstream ifile("pr2data.txt");
	int test_total = 0; // initialize accumulator to 0
	

	if(!ifile)
		cout << "ERROR!" << endl; // display error if file cannot be opened
	else
	{
		while(ifile>>ptr->id_number)
		{
			ifile >> ptr->test_score1;
			ifile >>ptr->test_score2;
			ifile >>ptr->test_score3;
			ptr++; // increment the pointer at the end of each iteration of the loop
		}
		ifile.close();	// close the file after all values are read 
	}
	
	for(int count = 0; count < SIZE; count++)
	{
		--ptr; // decrement the pointer
		test_total = (ptr->test_score1 + ptr->test_score2 + ptr->test_score3); // the sum of the scores
		ptr->test_average = (test_total / 3.00); // calculate each test average using the sum divided by 3	
	}
	

	cout << "ID\tTEST 1\tTEST 2\tTEST 3\tTEST AVERAGES" << endl;
	cout << fixed << showpoint << setprecision(2);
	for(int count = 0; count < SIZE; count++, ptr++)
	{
		cout << ptr->id_number << "\t" << ptr->test_score1 << "\t" << ptr->test_score2 << "\t" << ptr->test_score3;
		cout << "\t"<< ptr->test_average << endl;
	}
	cout << endl;
}


/* This function is void because it doesn't
return any values.  It contains one parameter
which is a pointer that points to a constant array 
of Student structures. It displays the student averages
that are greater than 70.00.*/
void displayAvgs(const Student *ptr)
{
	cout << "\nSTUDENTS WITH AN AVERAGE GREATER THAN 70.00" << endl;
	cout << "ID\tAVERAGES" << endl;
	for(int count = 0; count < SIZE; count++, ptr++)
	{
		if(ptr->test_average > 70.00) // allows only averages greater than 70 to be displayed
			cout << ptr->id_number << "\t" << ptr->test_average << endl;
	}
	cout << endl;
}

/* This function is void because it doesn't return
any values.  It contains one parameter which is a 
pointer that points to an array of Student structures.
The function uses a bubble sort to sort every structure 
in the array in ascending order based on test averages.*/
void bubbleSort(Student *ptr)
{
	bool sort;
	Student temp;
	
	do
	{
		sort = false;
		for(int count = 0; count < SIZE - 1; count++)
		{
			if(ptr[count].test_average > ptr[count + 1].test_average)
			{
				temp = ptr[count];
				ptr[count] = ptr[count +1];
				ptr[count + 1] = temp;
				sort = true; // sort is true after one element is switched with the next element
			}
		}
	}while(sort); // loop is true as long as sorting occurs
}


/* This function is int type because it
returns the subscript of an element or -1. The 
function contains two parameters.  One parameter
which is a pointer that points to a constant array of Student 
structures.  The other parameter is a float that is 
passed by const reference. The function performs a 
binary search to find the location of the given value
,if it cannot be located then -1 is returned.*/
int binarySearch(const Student *ptr, const float &val)
{
	int first, last, middle;
	first = 0;
	last = SIZE - 1;
	
	while(first <= last)
	{
		middle = ((first + last) / 2); 
		
		if(ptr[middle].test_average == val)
			return middle; // the subscript is returned if the current element contains the value
		else
			if(ptr[middle].test_average > val)
				last = middle - 1;
			else
				first = middle + 1;
	}
	return -1; // -1 is returned if the value wasnt found in the array
}


/* This function is a void type because it returns
no value.  It contains one parameter which is a 
pointer that points to an array of Student structures.  
It calls a sort function to sort the array based on test
averages. Next, it calls a search function which returns the position
of the element that contains 85 or returns -1 if not found. The 
position is adjusted until the current and previous elements
no longer have matching averages. Finally, all student IDs 
and test averages greater than or equal to 85.00 are 
displayed.*/
void displayHighAvgs(Student *ptr)
{	
	int pos;
	const Student *ptr2; // ptr2 is a pointer to const which prevents id numbers and averages from being changed

	bubbleSort(ptr);
	
	pos = binarySearch(ptr, 85.00); // the subscript of the element where 85 was located
	while(ptr[pos].test_average == ptr[pos - 1].test_average)
		pos--; // decrements pos until the two elements no longer share the same average
	
	ptr += pos; // change the value of the pointer by adding pos to it
	ptr2 = ptr; // ptr2 holds the same address as ptr now
	
	cout << "\nSTUDENTS WITH AN AVERAGE OF 85.00 OR GREATER\nID\tAVERAGES" << endl;
	for(int x = pos; x < SIZE; x++, ptr2++)
		cout << ptr2->id_number << "\t" << ptr2->test_average << endl;
	cout << endl;
}



/* This function is a void type because it does not return
any values.  It contains one parameter which is a pointer
that points to an array of Student structures.  It uses
a selection sort with the pointer to sort the array of
Student structures by their IDs in ascending order. A
pointer to const is given the address of the original pointer.
The pointer to const is used to protect the array and data.
It displays every students ID, test scores, and averages.*/
void selectionSort(Student *ptr)
{
	Student minVal;
	int minIndex;
	int swapCount; // keeps track of number of swaps made by the function
	const Student *ptr2; // ptr2 is a pointer to const which prevents id numbers and averages from being changed
	
	swapCount = 0; // initialize counter to 0
	
	for(int x = 0; x < SIZE - 1;x++)
	{
		minVal = ptr[x];
		minIndex = x;
		for(int y = x + 1; y < SIZE; y++)
		{
			if(ptr[y].id_number < minVal.id_number)
			{
				minVal = ptr[y];
				minIndex = y;
			}
			
		}
		
		if(ptr[x].id_number != minVal.id_number)
		{
			swapCount++; // increase the swap count by 1 if a swap was made
			ptr[minIndex] = ptr[x]; 
			ptr[x] = minVal;
		}
	}
	
	ptr2 = ptr; // ptr2 holds the same address as ptr now
	
	cout << "\nSTUDENT IDS IN ASCENDING ORDER" << endl;
	cout << "ID\tTEST 1\tTEST 2\tTEST 3\tTEST AVERAGES" << endl;
	for(int count = 0; count < SIZE; count++,ptr2++)
	{
		cout << ptr2->id_number << "\t" << ptr2->test_score1 << "\t" << ptr2->test_score2;
		cout << "\t" << ptr2->test_score3 << "\t" << ptr2->test_average << endl;	
	}
	cout << "\nNumber of swaps to sort the IDs : " << swapCount << endl; // display the swap count
}


/* This function is a void type because it does not
return a value.  It contains one parameter which is a 
pointer that points to a constant array of Student structures.
It allows the user to input an ID to search for. The function
uses a binary search to find the requested ID in the array
of structures. If the ID is not found then a message is displayed.
If an ID is found then the function displays the students ID,
test scores, and test average.  Finally, it asks the user
if they want to search for another students ID. */
void requestIDs(const Student *ptr)
{
	char choice;
	int id, first, last, middle;
	bool foundID;
	
	cout << endl;
	
	do
	{
		first = 0;
		last = SIZE - 1;
		foundID = false;
		
		cout << "Enter an ID you wish to look for :"; cin >> id; // ask user for a student ID to search for

		while(first <= last && !foundID)
		{		
			middle = ((first + last) / 2);
			
			if(ptr[middle].id_number == id)
			{
				ptr += middle;
				cout << ptr->id_number << "\t" << ptr->test_score1 << "\t" << ptr->test_score2;
				cout << "\t" << ptr->test_score3 << "\t" << ptr->test_average << endl;
				ptr -= middle;
				foundID = true;
				
			}
			else
				if(ptr[middle].id_number > id)
					last = middle - 1;
				else
					first = middle + 1;
		}
		
		if(!foundID)
		{
			cout << "ID WAS NOT FOUND!!!" << endl;	// notifies the user that the ID was not found
		}
		
		cout << "Would you like to search for another ID (Y/N)? "; cin >> choice;
		choice = toupper(choice);
			
	}while(choice == 'Y'); // the loop continues to run as long as the user enters Y for choice
	
	cout << "THANK YOU FOR USING THIS PROGRAM! GOOD BYE!" << endl; // displays a footer message
}

