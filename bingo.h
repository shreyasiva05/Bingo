// UMBC - CMSC 341 - Fall 2023 - Proj0
// UMBC - CMSC 341 - Fall 2023 - Proj0
#ifndef BINGO_H
#define BINGO_H
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class
const int CARDROWS = 5;     // default number of rows
const int CARDCOLS = 5;     // default number of columns
const int MINVAL = 11;      // default min value in a cell
const int MAXVAL = 85;      // default max value in a cell
const int EMPTYCELL = 99;   // empty cell (already drawn)
const int BALLS = MAXVAL - MINVAL + 1; // the number of balls that we can draw

class Cell{
public:
    friend class Grader;
    friend class Tester;
    /* calling constructor with default params creates an empty object*/
    Cell(int row=0, int col=0, int val=EMPTYCELL){
        m_row = row, m_col = col, m_value = val;
    }
    ~Cell(){}
    int getRow(){return m_row;}
    int getCol(){return m_col;}
    int getVal(){return m_value;}
    void setRow(int row){m_row=row;}
    void setCol(int col){m_col=col;}
    void setVal(int val){m_value=val;}
    bool isEmpty(){
        if (m_value == EMPTYCELL) return true;
        else return false;
    }
    friend bool operator==(const Cell & lhs, const Cell & rhs);
private:
    int m_row;
    int m_col;
    int m_value;
};

class Bingo{
public:
    friend class Grader;
    friend class Tester;
    Bingo();
    Bingo(int rows, int columns, int min, int max);
    ~Bingo();
    void clear();           // deallocates all memory, re-initialize all members
    bool reCreateCard(int rows, int columns, int min, int max);
    bool initCard();        // initializes the card to random numbers
    int play(int numDraws, vector<int> rndBalls);
    vector<int> drawBalls();//returns a randomly populated list
    const Bingo & operator=(const Bingo & rhs);
    void dumpCard();        // for debugging purposes
private:
    int * m_trackCols;  // use this to keep track & check if a column is complete
    int * m_trackRows;  // use this to keep track & check if a row is complete
    Cell * m_helper;    // the array to store cells in which index numbers are the cell values
    int m_helperSize;
    Cell **m_card;     // the 2d structure to store card information
    int m_numRows;
    int m_numCols;
    int m_minBallVal;   // min value in a cell
    int m_maxBallVal;   // max value in a cell

    /******************************************
    * Private function declarations go here! *
    ******************************************/

};

// The following class is an auxiliary class to facilitate the random number generation
// The UNIFORMINT type generates random integer numbers in a range
//      if the range is small there might be duplicate numbers
// The UNIFORMREAL type generates random floating point numbers in a range
// The NORMAL type generates a set of random numbers with normal distribution
// The SHUFFLE type generates a list of randomly distributed integer numbers without duplicates
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL, SHUFFLE};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else if (type == UNIFORMREAL) { //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
        else { //the case of SHUFFLE to generate every number only once
            m_generator = std::mt19937(m_device());
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    void getShuffle(vector<int> & array){
        // the user program creates the vector param and passes here
        // here we populate the vector using m_min and m_max
        for (int i = m_min; i<=m_max; i++){
            array.push_back(i);
        }
        shuffle(array.begin(),array.end(),m_generator);
    }

    void getShuffle(int array[]){
        // the param array must be of the size (m_max-m_min+1)
        // the user program creates the array and pass it here
        vector<int> temp;
        for (int i = m_min; i<=m_max; i++){
            temp.push_back(i);
        }
        std::shuffle(temp.begin(), temp.end(), m_generator);
        vector<int>::iterator it;
        int i = 0;
        for (it=temp.begin(); it != temp.end(); it++){
            array[i] = *it;
            i++;
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};
#endif