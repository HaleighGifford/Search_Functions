//*****************************************************************************************************
//
//		File:			    results.cpp
//		
//		Student:			Haleigh Cates
//
//		Assignment:	 	    Program  #7
//
//		Course Name:		Data Structures II  
//
//		Course Number:		COSC 3100 - 01
//
//		Due:			    February 13, 2019 
//
//
//		This program compares the relative efficiency of several searches.
//
//		Other files required:
//                       1.   searches.cpp
//						 2.	  ordered.txt
//						 3.	  unordered.txt
//						 4.	  searchNums.txt
//		
//*****************************************************************************************************

#ifndef RESULTS_H
#define RESULTS_H

//****************************************************************************************************

struct Results
{
	int numSuccesses;
	int totalCompares;
	double percSuccesses;
	double avgNumCompares;

	Results();
};

//****************************************************************************************************

Results:: Results()
{
	numSuccesses = 0;
	totalCompares = 0;
	percSuccesses = 0;
	avgNumCompares = 0;
}

//****************************************************************************************************

#endif
