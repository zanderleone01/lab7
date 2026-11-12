/////////////////////////////////////////////////////////////////////
// Your name: Zander Leone
// Date: 11/11/2026
// Class: CSCI 1470.04
// Semester: Fall 2026
// CSCI 1470 Instructor: Dr. Jonatan Reyes
// Program Description: Loads an array from a dictionary text file to
//                      spell check a user's input. Based on the
//                      settings text file used, it changes how many
//                      mistakes are allowed and what type of search
//                      is used. With const DEBUG on, it prints how
//                      long it takes for funtions to run.
/////////////////////////////////////////////////////////////////////  

#include<iostream>
#include <string>
#include<fstream>
#include <algorithm>
#include<iomanip>
#include <chrono>
using namespace std;
using namespace chrono;


void fillArray(string dictionArr[]);
void loadArray(string dictionArr[], bool& flag);
bool spellCheck(string dictionArr[], string userWord, string searchType);

const bool DEBUG = true;
const int MAX_WORDS = 466551;
const string LINEAR_SEARCH_UNSORTED = "LINEAR_UNSORTED";
const string LINEAR_SEARCH_SORTED = "LINEAR_SORTED";
const string BINARY_SEARCH = "BINARY";


int main() {
    ifstream fin("settings.txt");
    int mistakes = 0;
    string searchType;
    string* dictionArr = new string[MAX_WORDS];
    bool flag = true;
    string userWord;
    char yesNo = 'Y';
    int misCount = 0;

    fin >> mistakes;
    fin >> searchType;

    fillArray(dictionArr);
    loadArray(dictionArr, flag);

    if (!flag) {
        fin.close();
        return 0;
    }

    cout << "-----------------------------" << endl;
    cout << " Hello! I'm a Spell Checker! " << endl;
    cout << "-----------------------------" << endl;

    do {
        cout << endl << "Please enter a word: ";
        cin >> userWord;

        auto start = high_resolution_clock::now();
        if (spellCheck(dictionArr, userWord, searchType)) {
            auto end = chrono::high_resolution_clock::now();
            misCount = 0;
            cout << "The word " << userWord << " is spelled correctly!" << endl;
            if (DEBUG) {
                duration<double> elapsed = end - start;
                cout << setprecision(2) << fixed << showpoint;
                if (searchType == LINEAR_SEARCH_UNSORTED) {
                    cout << "Linear search took " << elapsed.count() << " microseconds." << endl;
                }
                else if (searchType == LINEAR_SEARCH_SORTED) {
                    cout << "Linear search took " << elapsed.count() << " microseconds." << endl;
                }
                else if (searchType == BINARY_SEARCH) {
                    cout << "Binary search took " << elapsed.count() << " microseconds." << endl;
                }
            }
            cout << endl << "Do you want to continue (Y/N): ";
            cin >> yesNo;
        }
        else {
            cout << "Oops! It looks like '" << userWord << "' isn't quite right. No worries, you're doing great-let's try spelling it again." << endl;
            misCount++;
        }
    } while (misCount < mistakes && yesNo == 'Y');

    if (misCount == mistakes) {
        cout << endl << "You have reached the maximum number (" << mistakes << ") of misspelled words allowed." << endl;
    }

    cout << "Have a nice day!" << endl;

    fin.close();
    return 0;
}

void fillArray(string dictionArr[]) {
    for (int i = 0; i < MAX_WORDS; i++) {
        dictionArr[i] = "";
    }
}

void loadArray(string dictionArr[], bool& flag) {
    ifstream fin("dictionary.txt");

    if (fin) {
        for (int i = 0; i < MAX_WORDS; i++) {
            fin >> dictionArr[i];
        }
    }
    else {
        cout << "Error: No dictionary file found." << endl;
        flag = false;
    }

    fin.close();
}

bool spellCheck(string dictionArr[], string userWord, string searchType) {
    if (searchType == LINEAR_SEARCH_UNSORTED) {
        for (int i = 0; i < MAX_WORDS; i++) {
            if (userWord == dictionArr[i]) {
                return true;
            }
        }
    }
    else if (searchType == LINEAR_SEARCH_SORTED) {
        sort(dictionArr, dictionArr + MAX_WORDS);
        for (int i = 0; i < MAX_WORDS; i++) {
            if (userWord == dictionArr[i]) {
                return true;
            }
        }
    }
    else if (searchType == BINARY_SEARCH) {
        sort(dictionArr, dictionArr + MAX_WORDS);
        int first = 0;
        int last = MAX_WORDS - 1;
        int middle = 0;
        while (first <= last) {
            middle = (first + last) / 2;
            if (userWord == dictionArr[middle]) {
                return true;
            }
            else if (userWord < dictionArr[middle]) {
                last = middle - 1;
            }
            else {
                first = middle + 1;
            }
        }
    }

    return false;
}