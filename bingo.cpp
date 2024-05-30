// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
/*
File: bingo.cpp
Author: Shreya Sivakumar
Date: 9/12/2023
Lab Section:
Email: shreyas7@umbc.edu
Description:  This program is a bingo game
*/
//Default constructor
// Name: Default Constructor
// Desc: Setting to default values
// Preconditions: the values weren't initialized
// Postconditions: the values were set
Bingo::Bingo(){
    m_card = nullptr;
    m_numRows =0;
    m_numCols= 0;
    m_maxBallVal = MAXVAL;
    m_minBallVal = MINVAL;
    m_helperSize = BALLS;
    m_trackCols = nullptr;
    m_trackRows = nullptr ;
    m_helper = nullptr;

}

// Name: Copy Constructor
// Desc: Setting to default values and making object
// Preconditions: the values weren't initialized
// Postconditions: Allocating memory
Bingo::Bingo(int rows, int columns, int min, int max){

    //Conditions to check whether it works under these circumstances
    if ((rows >= 2 && rows <= 15) && (columns == CARDCOLS) &&((min >= MINVAL) && (max <= MAXVAL)) && ((max -min +1 )% columns == 0)){
        m_numRows = rows; //Initialize the rows and columns to 0;setting all to default values
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;
        m_card = new Cell * [m_numRows];
        for (int j = 0; j < m_numRows; j++){ //going through the loop to allocate memory for the columns
            m_card[j] = new Cell [m_numCols];

        }
        m_helperSize = max-min +1;
        m_helper= new Cell[m_helperSize];
        m_trackCols = new int [m_numCols];
        m_trackRows=new int [m_numRows];
    }
    else{ //set them to default values if the conditions doesn't work
        m_card = nullptr;
        m_numRows =0;
        m_numCols= 0;
        m_maxBallVal = MAXVAL;
        m_minBallVal = MINVAL;
        m_helperSize = BALLS;
        m_trackCols = nullptr;
        m_trackRows = nullptr ;
        m_helper = nullptr;
    }

}

// Name: Recreate Card
// Desc: recreating the bingo game
// Preconditions: deallocating the memory
// Postconditions: recreating from the begginning using the values
bool Bingo::reCreateCard(int rows, int columns, int min, int max) {
    clear(); //Calling clear to deallocate the memory that has been created before
    if ((rows >= 2 && rows <= 15) && (columns == CARDCOLS) &&((min >= MINVAL) && (max <= MAXVAL)) && ((max -min +1 )% columns == 0)){ //Setting the conditons exactly from the constructor

        //Setting it to default values and created allocating memory for the m_card and m-helper
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;
        m_helperSize = max-min+1;
        m_card = new Cell * [m_numRows];
        for (int j = 0; j < m_numRows; j++){
            m_card[j] = new Cell [m_numCols];
        }

        m_helper = new Cell[m_helperSize];
        m_trackRows = new int[m_numRows];
        m_trackCols = new int[m_numCols];
        initCard(); //Calling Init function at the end of the if condtion
        return true;
    }

        //Setting them to default values if they do not meet the requirements
    m_card = nullptr;
    m_numRows =0;
    m_numCols= 0;
    m_maxBallVal = 0;
    m_minBallVal = 0;
    m_helperSize = 0;
    m_trackCols = nullptr;
    m_trackRows = nullptr ;
    m_helper = nullptr;
    return false;

}

// Name: Destructor
// Desc: Deallocating memory
// Preconditions: The values were allocated
// Postconditions: Calls the clear function to deallocate
Bingo::~Bingo(){
    //Callling clear function to deallocate the memory
    clear();
}

// Name: Clear
// Desc: Deallocating memory
// Preconditions: The values were allocated
// Postconditions: Deallocate each variable, arrays
void Bingo::clear(){
    //Deleting the track rows and colums
    if (m_trackRows!= nullptr){
        delete [] m_trackRows;
    }
    if (m_trackCols!= nullptr){
        delete [] m_trackCols;
    }

    delete[] m_helper;
    //if the m_card is used deallocate the memory
    if(m_card){
        for (int i = 0; i < m_numRows; i++) {
            delete [] m_card[i];
        }
        delete[] m_card;
    }//Setting m_card to nullptr and setting other values to deafult values in the destructor
    m_card = nullptr;
    m_numRows =0;
    m_numCols= 0;
    m_maxBallVal = MAXVAL;
    m_minBallVal = MINVAL;
    m_helperSize = BALLS;
    m_trackCols = nullptr;
    m_trackRows = nullptr ;
    m_helper = nullptr;
}
//Name: Initcard Function
// Desc: Using this function to create rows and columns and alligning them correspondingly
// Preconditions: The values were allocated
// Postconditions:Allocates the m_helper using the values of the vector
bool Bingo::initCard(){
    //Check to see if the m_helper and m_card is not empty
    if(m_helper!=nullptr || m_card!=nullptr) {
        for(int i = 0;i < m_numCols; i++){
            m_trackCols[i]=0;
        }
        for(int i = 0;i < m_numRows; i++){
            m_trackRows[i]=0;
        }
        //intialize total ball vales and balls per column
        int totalballvalues =(m_maxBallVal -m_minBallVal)+1  ;
        int ballspercolumn = totalballvalues / m_numCols;
        //ballspercolumn should equal to 15
        vector<int> ballsShuffle; //initialize a vector
        //
        int beginvalue = m_minBallVal; //begin value is equal to the min Ball value
        int endvalue = beginvalue + ballspercolumn - 1;
        Random randomaccess(beginvalue,endvalue, SHUFFLE); //shuffling the values for the first column
        randomaccess.getShuffle(ballsShuffle);
        for (int i = 0; i < m_numCols; i++) { //going through the column loop to randomize numbers for
            int beginvalue = m_minBallVal +( ballspercolumn * i);
           // if (beginvalue <=endvalue){
           int endvalue = beginvalue + ballspercolumn - 1;
            //}
            Random randomaccess(beginvalue,endvalue, SHUFFLE);
            randomaccess.getShuffle(ballsShuffle); //shuddle the ball values of the vector
            for (int j = 0; j < m_numRows; j++) {
                    // Assign the shuffled value to the card cell.
                    m_card[j][i] = Cell(j,i,ballsShuffle[j]);
                    //Initialize the values to the m_helper function
                    m_helper[ballsShuffle[j]-m_minBallVal] = m_card[j][i]; //assign the ball values to the m_helper
            }
            int rowArea = m_numRows;
            int colArea = m_numCols;
            if(rowArea>=2 && rowArea<=15){ //Checking to see if the numrows are greater or equal to 2
                m_helperSize = rowArea * colArea; //if it meets the conditon multiply and set the m_helpersize to the total area
            }
        }
        return true;//return true at the end if works
    }
    return false;//return false if it doesnt meet the condtions
}
//Name: Draw Balls function
// Desc: Vector of ball values
// Preconditions: The values were allocated
// Postconditions: return the vector of values
vector<int> Bingo::drawBalls(){
    //Initialize a vector to store the values of balls
    vector<int> ballvalues;
    //Randomize the values
    Random randomaccess(m_minBallVal,m_maxBallVal, SHUFFLE);
    //Shuffle the values of balls from the min to max Ball values
    randomaccess.getShuffle(ballvalues);
    //return the vector
    return ballvalues;
}
//Name: play function
// Desc: Deallocating memory
// Preconditions: The values were allocated
// Postconditions: Returns the matchballs
int Bingo::play(int numDraws, vector<int> rndBalls){
    //Initialzing a variable matchball
    int matchball = 0;
    //looping through vector
    for (unsigned int i = 0; i < rndBalls.size(); i++) {
        int ball = rndBalls.at(i); //Assigning an index of the vector to a variable ball
        if (ball>=m_minBallVal && ball<=m_maxBallVal){ //using the condititon to check whether the ball
            for (int k = 0; k < m_numRows; k++) {
                for (int j = 0; j < m_numCols; j++) {
                    // Check if the drawn ball matches the value in the Bingo card.

                    if (m_card[k][j].getVal()==ball) {

                        m_helper[ball-m_minBallVal]=m_card[k][j];
                        m_card[k][j].setVal(EMPTYCELL);
                        // Increment the corresponding element in m_trackRows and m_trackCols.
                        matchball++;
                        //Incrementing trackrows and columns after they found the matchball
                        m_trackRows[k]++;
                        m_trackCols[j]++;

                        if(m_trackRows[k] ==CARDCOLS || m_trackCols[j] ==m_numRows){

                            return matchball;
                        }
                    }
                }
            }
        }//if the matchball is greater than the numdraws return the matchball
        if (matchball>=numDraws){
          return matchball;
       }
    }
    return matchball;

}
//Name: Assignment operator
// Desc: Assingning to the object
// Preconditions: The values were allocated
// Postconditions: Assigns values and equal them to together
const Bingo & Bingo::operator=(const Bingo & rhs){
    if(this !=&rhs) {//to check if it is trying to allocate the object for itself

        //Entering to clear function to deallocate the memory
        clear();
        //shallow copying from rhs object to lhs
        m_numRows = rhs.m_numRows;
        m_numCols = rhs.m_numCols;
        m_minBallVal = rhs.m_minBallVal;
        m_maxBallVal = rhs.m_maxBallVal;
        m_helperSize = rhs.m_helperSize;
        //Allocating a new cell for m_helper since m_helper holds the cell values


        if (rhs.m_card!= nullptr){
            m_helper= new Cell[m_helperSize];
            //Allocating memory for trackrows,colms and m_card
            m_trackRows = new int[m_numRows];
            m_trackCols = new int[m_numCols];
            for (int i = 0; i < m_helperSize; i++) {

                m_helper[i] = rhs.m_helper[i];//setting the values of the rhs to m_helper[i]
            }
            m_card = new Cell *[m_numRows];
            for (int i = 0; i < m_numRows; i++) {//looping through to allocate memory for columns
                m_card[i] = new Cell[m_numCols];
                for (int j = 0; j < m_numCols; j++) {
                    m_card[i][j] = rhs.m_card[i][j];
                }
            }
            //going through the loop to do shallow copy for each trackRows
            for (int i = 0; i < m_numRows; i++) {
                m_trackRows[i] = rhs.m_trackRows[i];

            }
            //going through the loop to do shallow copy for each trackcolumns
            for (int i = 0; i < m_numCols; i++) {
                m_trackCols[i] = rhs.m_trackCols[i];

            }
        }

        return *this; //return this after shallo copying
    }
    return *this;//else return this object

}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard(){
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j=1;j<=m_numCols;j++){
            if (m_card[i-1][j-1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i-1][j-1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i-1][j-1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell & lhs, const Cell & rhs){
    return ((lhs.m_col == rhs.m_col) &&
            (lhs.m_row == rhs.m_row) &&
            (lhs.m_value == rhs.m_value));
}
