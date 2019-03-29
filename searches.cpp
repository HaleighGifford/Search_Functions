#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#include "results.h"

//*****************************************************************************************************

void getData(const char fileName[], int list[], int size);
void process(int list[], int size, int searchNums[], Results & res, 
bool(*search) (int list[], int size, int target, int & numCompares));
bool ordSearch(int list[], int size, int target, int & numCompares);
bool unOrdSearch(int list[], int size, int target, int & numCompares);
bool binSearch(int list[], int size, int target, int & numCompares);
void updateStats(Results & res);
void displayResults(Results & unOrdRes, Results & ordRes, Results & binRes);

//*****************************************************************************************************

int main()
{
	int ordList[1000];
	int unOrdList[1000];
	int searchNums[500];

	Results ordRes;
	Results unOrdRes;
	Results binRes;

	getData("ordered.txt", ordList, 1000);
	getData("unordered.txt", unOrdList, 1000);
	getData("searchNums.txt", searchNums, 500);

	process(ordList, 1000, searchNums, ordRes, ordSearch);
	process(unOrdList, 1000, searchNums, unOrdRes, unOrdSearch);
	process(ordList, 1000, searchNums, binRes, binSearch);

	updateStats(ordRes);
	updateStats(unOrdRes);
	updateStats(binRes);

	displayResults(unOrdRes, ordRes, binRes);

	return 0;
}

//*****************************************************************************************************

void getData(const char fileName[], int list[], int size)
{
	ifstream file;
	file.open(fileName);

	for(int i = 0; i < size; i++)
	{
		file >> list[i];
	}

	file.close();
}

//*****************************************************************************************************

void process(int list[], int size, int searchNums[], Results & res,
	bool(*search) (int list[], int size, int target, int & numCompares))
{
	int numCom;

	for (int i = 0; i < 500; i++)
	{
		if (search(list, size, searchNums[i], numCom))
			res.numSuccesses++;
	
		res.totalCompares += numCom;
	}
} 

//*****************************************************************************************************

bool ordSearch(int list[], int size, int target, int & numCompares)
{
	bool found = false;
	int count = 0;

	while ((count < size - 1) && (++numCompares) && (list[count] < target))
	{
		count++;
	}

	if ((count < size) && (++numCompares) && (list[count] == target))
		found = true;

	numCompares = count + 2;
	
	return found;
}

//*****************************************************************************************************

bool unOrdSearch(int list[], int size, int target, int & numCompares)
{
	bool found = false;
	int count = 0;

	numCompares = 0;

	while ((count < size - 1) && (++numCompares) && (list[count] != target))
	{
		count++;
	}

	if ((count < size) && (++numCompares) && (list[count] == target))
		found = true;
	
	return found;
}

//*****************************************************************************************************

bool binSearch(int list[], int size, int target, int & numCompares)
{
	bool found = false;
	int first,
		last,
		middle,
		count;

	first = 0;
	last = size - 1;
	count = 0;

	while ((!found) && (first <= last))
	{
		middle = (first + last) / 2;

		if (list[middle] == target)
		{
			found = true;
			count++;
		}
		else if (list[middle] > target)
		{
			last = middle - 1;
			count += 2;
		}
		else
		{
			first = middle + 1;
			count += 2;
		}
	}

	numCompares = count;
	
	return found;
}

//*****************************************************************************************************

void updateStats(Results & res)
{
	res.percSuccesses = (res.numSuccesses / 500.0) * 100.00;
	res.avgNumCompares = res.totalCompares / 500.0;
}

//*****************************************************************************************************

void displayResults(Results & unOrdRes, Results & ordRes, Results & binRes)
{
	cout << setw(40) << "Unordered" << setw(14) << "Ordered" << endl
	     << setw(41) << "Sequential" << setw(15) << "Sequential"
	     << setw(14) << "Binary" << endl
	     << setw(39) << "Search" << setw(15) << "Search" 
	     << setw(16) << "Search" << endl << endl;
	cout << left << setw(34) << "# of Successfull Searches " 
	     << setw(15) << unOrdRes.numSuccesses << setw(16) 
	     << ordRes.numSuccesses << setw(15) << binRes.numSuccesses << endl;
	cout << left << setw(34) << "% of Searches Successfull " 
	     << setprecision(2) << fixed << unOrdRes.percSuccesses 
	     << setw(10) << "%" << ordRes.percSuccesses << setw(11) << "%" 
	     << binRes.percSuccesses << setw(8) << "%" << endl;
	cout << left << setw(34) << "Average Compares / Search" << setw(15) 
	     << setprecision(0) << fixed << unOrdRes.avgNumCompares << setw(16) 
	     << ordRes.avgNumCompares << setw(15) << binRes.avgNumCompares << endl;
}
