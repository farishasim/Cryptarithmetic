#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono> 
#include <bits/stdc++.h>

using namespace std;

//****** GLOBAL VARIABLE ******//
string CharValue;
vector<string> operand;
chrono::_V2::system_clock::time_point start, endt;
int countf;

//****** Time-related function ******//
void StartTime() {
    start = chrono::high_resolution_clock::now();
}

void EndTime() {
    endt = chrono::high_resolution_clock::now(); 

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(endt - start).count(); 

    time_taken *= 1e-9; 

    cout << "Time taken by program is : " << fixed << time_taken << setprecision(9) ; 
    cout << " sec " << endl; 
}

//****** Support Function ******//
int getCharValue(char c) {
    return CharValue.find(c);
}

void setCharValue(char c, int i) {
    CharValue[i] = c;
}

bool hasCharValue(char c) {
    return getCharValue(c) != -1;
}

void dropCharValue(char c) {
    CharValue[CharValue.find(c)] = '0';
}

bool isValueTaken(int i) {
    return CharValue[i] != '0';
}

int str2int(string str) {
    int val = 0, i = 0;
    
    char CC = str[i];

    while (CC != '\0') {
        val *= 10;
        val += getCharValue(CC);
        CC = str[++i];
    }
    return val;
}

string removePlus(string str) {
    string output;
    output.reserve(str.size()); 
    for(size_t i = 0; i < str.size(); ++i)
        if(str[i] != '+') output += str[i];
    return output;
}

bool testSum() {
    int sum = 0, n = operand.size(), i;

    for (i = 0; i < n-1; i++) {
        sum += str2int(operand[i]);
    }

    bool solved = (sum == str2int(operand[i]));
    
    if (!solved) {
        countf++;
    }

    return solved;
}

//****** I/O Function ******//
void inputFile() {
    ifstream infile("input.txt");
    string line;

    while (getline(infile, line)) {
        operand.push_back(line);
        if (line.find('+') != -1) {
            operand[operand.size() - 1] = removePlus(operand[operand.size() - 1]);
            getline(infile, line);
        }
    }
}

void printSolution() {
    int i,n = operand.size();

    cout << "-- QUESTION --";
    for (i = 0; i < n-1; i++) {
        cout << '\n' << (operand[i]);
    }
    cout << " +" << '\n' << "------\n";
    cout << operand[i] << '\n';

    cout << "\n-- ANSWER --";
    for (i = 0; i < n-1; i++) {
        cout << '\n' << str2int(operand[i]);
    }
    cout << " +" << '\n' << "------\n";
    cout << str2int(operand[i]) << '\n';
}

//****** Solving Algorithm ******//
bool solve(int idx_C, int idx_Ops) {
    char CC = operand[idx_Ops][idx_C];

    if (CC == '\0') 
    {
        if (idx_Ops == operand.size()-1) 
        {
            return testSum(); // base-case
        } 
        else 
        {
            return solve(0, idx_Ops+1); // recurrence-case, go to next operand
        }
    } 
    // recurrence-case
    else if (hasCharValue(CC))
    {
        if ((idx_C == 0) && (getCharValue(CC) == 0)) {
            return false;  // it's forbidden if the value of the first char is zero
        } 

        // if curent character has a value already, go to next char
        return solve(idx_C+1, idx_Ops); 
    }
    else 
    {
        // try value from 0 to 9
        int i = 0;
        bool solved = false;

        if (idx_C == 0) {
            i++; // first char start from 1
        }

        while (i <= 9 && !solved) 
        {
            if (isValueTaken(i))
            {
                // do nothing
            }
            else 
            {
                setCharValue(CC, i);
                solved = solve(idx_C+1, idx_Ops); // after assign value to CC, 
                                                  // proceed to next char recursively
                
                if (!solved) {
                    dropCharValue(CC); // if next char failed, remove value from CC
                }
            }
            i++;
        }

        return solved;
    }
}

//****** Setup Function ******//
void setup() {
    CharValue = "0000000000";
    countf = 0;

    inputFile();

    StartTime();
}

void setdown() {
    printSolution();
    
    EndTime();

    cout << "Number of tests tried is : " << countf << " times\n";
}

//****** Main Program ******//
int main() {

    setup();
  
    solve(0,0); 

    setdown();
  
    return 0; 
}