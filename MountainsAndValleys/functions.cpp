#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if ((a >= 10) && (a <= b) && (b < 10000))
		return true;
	return false;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	int i = number;
	int numDigits = 1;
	int divisor = 1;
	int currentVal;
	int nextVal;
	int tempVal = number;
	// creating a variable to store how many digits the number has 
	while ((i / 10) > 0) {
		numDigits += 1;		// need to count the divisor and numDigits correct
		divisor *= 10;
		i = i / 10;
	}

	// get the values of currentVal and nextVal to see which loop to enter
	currentVal = tempVal / divisor;
	tempVal = tempVal % divisor;
	divisor = divisor / 10;
	nextVal = tempVal / divisor;

	// mountain loop
	if (currentVal < nextVal) {
		for (int k = 1; k < numDigits - 1; ++k) {
			currentVal = tempVal / divisor;
			tempVal = tempVal % divisor;
			divisor = divisor / 10;
			nextVal = tempVal / divisor;
			if (k % 2 != 0) {
				if (currentVal <= nextVal) {
					return 'N';
					break;
				}
			}
			if (k % 2 == 0) {
				if (currentVal >= nextVal) {
					return 'N';
					break;
				}
			}
		}

		return 'M';
	}

	// valley loop
	else if (currentVal > nextVal) {
		for (int k = 1; k < numDigits - 1; ++k) {
			currentVal = tempVal / divisor;
			tempVal = tempVal % divisor;
			divisor = divisor / 10;
			nextVal = tempVal / divisor;
			if (k % 2 != 0) {
				if (currentVal >= nextVal) {
					return 'N';
					break;
				}
			}
			if (k % 2 == 0) {
				if (currentVal <= nextVal) {
					return 'N';
					break;
				}
			}
		}
		
		return 'V';
	}

	return 'N';
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int numMountains = 0;
	int numValleys = 0;
	int index = a;
	while (index <= b) {
		if (classify_mv_range_type(index) == 'M') {
			numMountains += 1;
		}
		if (classify_mv_range_type(index) == 'V') {
			numValleys += 1;
		}

		index += 1;
	}

	cout << "There are " << numMountains << " mountain ranges and " << numValleys << " valley ranges between " << a << " and " << b << "." << endl;

}