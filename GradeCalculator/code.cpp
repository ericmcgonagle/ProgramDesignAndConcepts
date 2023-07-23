// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin;
using std::cout; 
using std::endl;
using std::string; 
using std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double totalScoreHw = 0;
    int numHw = 0;
    double totalExamScore = 0;
    int numExams = 2;
    double totalLw = 0;
    int numLw = 0;
    double totalReadingScore = 0;
    int numReading = 0;
    double totalEngagementScore = 0;
    int numEngagement = 0;
    int compileCheck = 0;
    int numCompile = 0;
    double finalExam = 0;
    int numFinal = 1;
    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            // TODO(student): process exam score
            totalExamScore = totalExamScore + score;

        } else if (category == "final-exam") {
            // TODO(student): process final score
            finalExam = score;
            
        } else if (category == "hw") {
            // TODO(student): process hw score
            numHw +=1;
            totalScoreHw = totalScoreHw + score;
        } else if (category == "lw") {
            // TODO(student): process lw score
            numLw += 1;
            totalLw = totalLw + score;

        } else if (category == "reading") {
            // TODO(student): process reading score
            numReading += 1;
            totalReadingScore = totalReadingScore + score;

        } else if (category == "engagement") {
            // TODO(student): process engagement score
            numEngagement += 1;
            totalEngagementScore = totalEngagementScore + score;

        }else if  (category == "compile-check") {
            // TODO(student): process compile-check score
            numCompile += 1;
            compileCheck += score;

        }else {
            cout << "ignored invalid input" << endl;
        }


        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double exam_average = 0;
    double hw_average = 0;
    double lw_average = 0;
    double reading = 0;
    double engagement = 0;
    //double compileCheck_average = 0;

    // exam_average = (totalExamScore + finalExam) / (numExams + numFinal);
    if (numExams != 0) {
        exam_average = (totalExamScore + finalExam) / (numExams + numFinal);
    }
    if (numHw != 0) {
        hw_average = totalScoreHw / numHw;
    }
    if (numLw != 0) {
        lw_average = (totalLw / numLw) * 100;
    }
    if (numReading != 0) {
        reading = totalReadingScore / numReading;
    }
    if (numEngagement != 0) {
        engagement = totalEngagementScore / numEngagement;
    }
    // checking to see if the final exam score is greater than the average exam score
    if (finalExam > exam_average)
        exam_average = finalExam;

    if (compileCheck == 0)
        lw_average = 0;
    else if (compileCheck == 1)
        lw_average = lw_average * .5;

    reading = reading + 15;
    engagement = engagement + 15;
    if (reading > 100)
        reading = 100;
    if (engagement > 100)
        engagement = 100;
    

    // TODO(student): compute weighted total of components
    double weighted_total = 0;
    weighted_total = (exam_average * .4) + (hw_average * .4) + (lw_average * .1) + (reading * .05) + (engagement * .05);
    int final_grade = (int)(weighted_total + 0.5);
    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if ((final_grade >= 90) && (final_grade <= 100))
        final_letter_grade = 'A';
    else if ((final_grade >= 80) && (final_grade < 90))
        final_letter_grade = 'B';
    else if ((final_grade >= 70) && (final_grade < 80))
        final_letter_grade = 'C';
    else if ((final_grade >= 60) && (final_grade < 70))
        final_letter_grade = 'D';
    else if (final_grade < 60)
        final_letter_grade = 'F';

    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement | compile-check" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
