#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

string CharValue;
string operand[3];
time_t start, endt;

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

bool testSum() {
    // simple-ver
    return (str2int(operand[0]) + str2int(operand[1])) == str2int(operand[2]);
}

bool solve(int idx_C, int idx_Ops) {
    char CC = operand[idx_Ops][idx_C];

    if (CC == '\0') 
    {
        if (idx_Ops == 2) 
        {
            return testSum(); // base-case
        } 
        else 
        {
            return solve(0, idx_Ops+1); // recurence-case, go to next operand
        }
    } 
    // recurence-case
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
                // cout << CharValue <<'\n' ;
                solved = solve(idx_C+1, idx_Ops);
                if (!solved) {
                    dropCharValue(CC);
                    // cout << CC << '\n';
                }
            }
            i++;
        }

        return solved;
    }
}

void setup() {
    // simple-ver
    //CharValue = "OMY00ENDRS";

    CharValue = "0000000000";
    operand[0] = "SEND";
    operand[1] = "MORE";
    operand[2] = "MONEY";

    time(&start);
}

void setdown() {
    cout << CharValue << '\n';
    
    time(&endt);

    double time_taken = double(endt - start); 
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5) ; 
    cout << " sec " << endl; 
}

int main() {
    
    setup();

    solve(0,0);

    setdown();

    return 0;
}