#include <iostream>
#include <iomanip>
#include <string>
#include "parallel_tracks.h"

using std::string;

using std::cin;

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_runner_data( double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  //TODO
  // Update function to return the correct boolean values based on the parameters


	unsigned int index;
	double times; 
	string countries;
	unsigned int jerseyNumbers;
	string lastNames;		

	// reading in the data and then adding it to the respective array
	for (index = 0; index < SIZE; index++) {
		cin >> times >> countries >> jerseyNumbers>> lastNames;
		timeArray[index] = times;
		countryArray[index] = countries;
		numberArray[index] = jerseyNumbers;
		lastnameArray[index] = lastNames;
	}



	// checking to see if any of the times are negative 
  	for (index = 0; index < SIZE; ++index) {
		if (timeArray[index] <= 0)
			return false;
  }

	// check if any of the country name characters are not a-z
	// check if the country length is shorter or longer than 3
	for (index = 0; index < SIZE; index++) {
		if (countryArray[index].size() != 3)
			return false;
		else {
			for (unsigned int counter = 0; counter < 3; counter++) {
			char letter = countryArray[index][counter];
			if (isalpha(letter) == 0)
				return false;
			if (isupper(letter) == 0)
				return false;

		}

		}
	}

	// jerseyNumber containes either 1 or two digits
	// JERSEYNUMBER NOT WORKING

	for (index = 0; index < SIZE; index++) {
		if ((numberArray[index] > 99))
			return false;
		}

	
	// lastName only has a-z
	// trim any whitespace at beginning or end
	// contains more than one character
	for (index = 0; index < SIZE; index++) {
		trim(lastnameArray[index]);

		
		if (lastnameArray[index].size() < 2)
			return false;			
		else {
			for (unsigned int counter = 0; counter < lastnameArray[index].size(); counter++) {
			char letter = lastnameArray[index][counter];
			if (isalpha(letter) == 0)
				return false;
		}
		

		}
	}

	
  return true; // set so it will compile
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
  //TODO
  for (unsigned int i = 0; i < SIZE; ++i) {
	ary[i] = 0.0;
  }
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	//TODO
	for (unsigned int i = 0; i < SIZE; ++i) {
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	//TODO
	for (unsigned int i = 0; i < SIZE; ++i) {
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	//TODO
	unsigned int index;
	unsigned int count;
	double lowestTime = timeArray[0];
	// find the first place time 
	for (index = 0; index < SIZE; index++) {
		if (timeArray[index] < lowestTime)
			lowestTime = timeArray[index];
	}

	// set the correct index in rankArray to 1
	for (index = 0; index < SIZE; index++) {
		if (timeArray[index] == lowestTime)
			rankArray[index] = 1;
	}

	// assign lowestTime to the first available value in timeArray
	unsigned int i = 0;
	while (true) {
		if (rankArray[i] == 0) {
			lowestTime = timeArray[i];
			break;
		}
		else
			i++;
	}
	
	// find the correct rankings for the rest of the times
	for (count = 2; count < SIZE + 1; count++) {
		for (index = 0; index < SIZE; index++) {
			if (rankArray[index] == 0){
				if (timeArray[index] < lowestTime)
				lowestTime = timeArray[index];
			}
		}
		for (index = 0; index < SIZE; index++) {
			if (timeArray[index] == lowestTime)
				rankArray[index] = count;
		}
		unsigned int i = 0;
		while (true) {
			if (rankArray[i] == 0) {
				lowestTime = timeArray[i];
				break;
			}
			else
				i++;
	}


	}



}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}