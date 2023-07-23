#include "TemperatureDatabase.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string &filename)
{
	// Implement this function for part 1
	records = LinkedList();
	// check if file can open
	// ifstream ifs(filename);
	string location;
	int year;
	double month;
	double temperature;
	ifstream ifs(filename);
	if (!ifs.is_open())
	{
		cout << "Failed to open file" << filename << endl;
	}

	string inputData;

	// read input using getline by taking input as a string line by line
	// each line should have the same format so read in variables one by one
	// error check any of the variables to make sure the file format is correct
	while (getline(ifs, inputData))
	{
		istringstream tempInput(inputData);
		tempInput >> location;
		if (tempInput.fail())
		{
			cout << "Error: invalid year input" << endl;
		}
		tempInput >> year;
		if (tempInput.fail())
		{
			cout << "Error: Invalid year " << year << endl;
		}
		else if ((year < 1800) || (year > 2022))
		{
			cout << "Error: Invalid year " << year << endl;
		}
		tempInput >> month;
		if (tempInput.fail())
		{
			cout << "Error: Invalid month " << month << endl;
		}
		else if ((month < 1) || (month > 12))
		{
			cout << "Error: Invalid month " << month << endl;
		}
		else if (month - (int)month != 0) {
			cout << "Error: Invalid month " << month << endl;
		}
		tempInput >> temperature;
		if (tempInput.fail())
		{
			cout << "Error: Invalid temperature " << temperature << endl;
		}
		else if ((temperature < -50) || (temperature > 50))
		{
			// 99.99 is accepted for missing information
			if (temperature == -99.99)
			{
				break;
			}
			cout << "Error: Invalid temperature " << temperature << endl;
		}

		records.insert(location, year, month, temperature);
	}

	// cout << records.print() << endl;
}

// Do not modify
void TemperatureDatabase::outputData(const string &filename)
{
	ofstream dataout("sorted." + filename);

	if (!dataout.is_open())
	{
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string &filename)
{
	// Implement this function for part 2
	//  Leave it blank for part 1
}
