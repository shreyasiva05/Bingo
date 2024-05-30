// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
/*
File: mytest.cpp
Author: Shreya Sivakumar
Date: 9/12/2023
Lab Section:
Email: shreyas7@umbc.edu
Description:  This program is a bingo game
*/

class Tester{
public:
    // This function is a sample test function
    // It shows how to write a test case
    bool assignmentNormal(Bingo & lhs, Bingo & rhs){
        // we expect that lhs object is an exact copy of rhs object
        bool result = true;
        // we expect that the corresponding cells in lhs and rhs
        //      cards carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numRows;i++){
            for (int j=0;j<rhs.m_numCols;j++){
                result = result && (lhs.m_card[i][j] == rhs.m_card[i][j]);
            }
        }
        // we expect that the corresponding cells in lhs and rhs
        //      m_helper carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_helperSize;i++){
            result = result && (lhs.m_helper[i] == rhs.m_helper[i]);
        }
        // we expect that the corresponding cells in lhs and rhs
        //      m_trackRows carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numRows;i++){
            result = result && (lhs.m_trackRows[i] == rhs.m_trackRows[i]);
        }
        // we expect that the corresponding cells in lhs and rhs
        //      m_trackCols carry the same cell information (exact same copy)
        for (int i=0;i<rhs.m_numCols;i++){
            result = result && (lhs.m_trackCols[i] == rhs.m_trackCols[i]);
        }
        result = result && (lhs.m_minBallVal == rhs.m_minBallVal);
        result = result && (lhs.m_maxBallVal == rhs.m_maxBallVal);
        return result;
    }
    bool assignmentEdge(){
        Bingo lhs(5, 5, 1, 75);
        Bingo rhs;
        lhs=rhs;
        bool result = true;
        result = result && (lhs.m_numRows == 0);
        result = result && (lhs.m_numCols == 0);

        // Check min and max ball values
        result = result && (lhs.m_minBallVal == MINVAL);
        result = result && (lhs.m_maxBallVal == MAXVAL);

        // Check helper size
        result = result && (lhs.m_helperSize == BALLS);
//        for (int i=0;i<rhs.m_helperSize;i++){
//            result = result && (lhs.m_helper[i] == rhs.m_helper[i]);
//        }

        // Check card, trackCols, and trackRows pointers
        result = result && (lhs.m_card == nullptr);
        result = result && (lhs.m_trackCols== nullptr);
        result = result && (lhs.m_trackRows == nullptr);

        // Check helper pointer
        result = result && (lhs.m_helper == nullptr);

        return result;
    }
    bool constructorerror(const Bingo &obj){
        Bingo lhs(-5, -10, MINVAL, MAXVAL);
        bool result = true; //return true if it works
        //Check to see if the num rows are greater than 0
        result = result && (obj.m_numRows >= 0);

        //Check to see if the num Columns are greater than 0
        result = result && (obj.m_numCols >= 0);

        //Checking whether it works for min,max ball values and m_card
        result = result && (obj.m_minBallVal  >= 0);
        result = result && (obj.m_maxBallVal >= 0);
        result = result && (obj.m_helperSize >= 0);
        result = result && (obj.m_card!= nullptr);

        //Check to see the track adn track cols
        result = result && (obj.m_trackRows!= nullptr);
        result = result && (obj.m_trackCols != nullptr);
        result = result && (obj.m_helper != nullptr);
        return result;

    }
    bool constructornormal(const Bingo &obj){
        Bingo lhs(10, 5, MINVAL, MAXVAL);
        bool result = true; //return true if it works
        //Check to see if the num rows are greater than 0
        result = result && (obj.m_numRows >= 0);

        //Check to see if the num Columns are greater than 0
        result = result && (obj.m_numCols >= 0);

        //Checking whether it works for min,max ball values and m_card
        result = result && (obj.m_minBallVal  >= 0);
        result = result && (obj.m_maxBallVal >= 0);
        result = result && (obj.m_helperSize >= 0);
        result = result && (obj.m_card!= nullptr);

        //Check to see the track adn track cols
        result = result && (obj.m_trackRows!= nullptr);
        result = result && (obj.m_trackCols != nullptr);
        result = result && (obj.m_helper != nullptr);
        return result;

    }
    bool recreateror(Bingo &obj) {

            // Check if the object is created with the expected parameters
            bool result = true;
            result = result && !(obj.reCreateCard(-5, -10, MINVAL, MAXVAL));
            result = result && (obj.m_numRows >=0);
            result = result && (obj.m_numCols >=0);
            result = result && (obj.m_minBallVal == 0);
            result = result && (obj.m_maxBallVal == 0);
            result = result && (obj.m_helperSize == 0);


            // Check if memory is allocated for m_card and m_helper
            result = result && (obj.m_card == nullptr);
            result = result && (obj.m_helper == nullptr);

            // Check if m_trackCols and m_trackRows are nullptr
            result = result && (obj.m_trackCols == nullptr);
            result = result && (obj.m_trackRows == nullptr);

            return result;


    }
    bool recreatenormal(Bingo &obj) {

        if (obj.reCreateCard(10, 5, MINVAL, MAXVAL)) {
            // Check if the object is created with the expected parameters
            bool result = true;
            result = result && (obj.m_numRows == 10);
            result = result && (obj.m_numCols == 5);
            result = result && (obj.m_minBallVal == MINVAL);
            result = result && (obj.m_maxBallVal == MAXVAL);
            //result = result && (obj.m_helperSize == BALLS);

            // Check if memory is allocated for m_card and m_helper
            result = result && (obj.m_card != nullptr);
            result = result && (obj.m_helper != nullptr);

            // Check if m_trackCols and m_trackRows are nullptr
            result = result && (obj.m_trackCols != nullptr);
            result = result && (obj.m_trackRows != nullptr);

            return result;
        }
        return false;
    }
    bool inticardnormal(Bingo &obj){
        bool result = true;
        if(obj.m_helper != nullptr && obj.m_card!= nullptr){
            for(int i=0;i<obj.m_numRows;i++){
                for(int j=0;j<obj.m_numCols;j++){
                    if (obj.m_card[i][j].getVal() ==0 && obj.m_card[i][j].getCol() ==0){
                        return false;
                    }
                }
            }
        }
        return result;
    }
    //bool testplayfunction

private:

    /**********************************************
    * If we need helper functions to be reused in *
    *   test functions they can be declared here!
    **********************************************/
};
int main(){
    Tester tester;
    Bingo obj1(CARDROWS,CARDCOLS,MINVAL,MAXVAL);
    vector<int> balls = obj1.drawBalls();
    if (obj1.initCard()){
        obj1.dumpCard();
        cout << "\ngame over after " << obj1.play(BALLS,balls) << " hits!\n" << endl;
        obj1.dumpCard();
    }

    Bingo obj2;
    obj2 = obj1;
    // test whether the assignment operator normal case works correctly
    cout << "Following is the test message for testing assignment operator:\n" << endl;
    if (tester.assignmentNormal(obj2,obj1))
        cout << "Test msg: Assignment operator test for normal case passed!\n" << endl;
    else
        cout << "Test msg: Assignment operator test for normal case failed!\n" << endl;

    // Re-initialize the object to a card of 10x5
    cout << "Following is the result of re-initializing the object and re-play:\n" << endl;
    //
    cout<<"*****************Constructor error testfunction*************"<<endl;
    cout << "Following is the test message for testing the constructor for errorcases :\n" << endl;
    if (tester.constructorerror(obj1))
        cout << "Test msg: Constructor test for error cases passed!\n" << endl;
    else
        cout << "Test msg: Constructor test for error cases failed!\n" << endl;

    cout<<"*****************Constructor normal testfunction*************"<<endl;
    cout << "Following is the test message for testing the constructor for normal cases :\n" << endl;
    if (tester.constructornormal(obj1))
        cout << "Test msg: Constructor test for normal cases passed!\n" << endl;
    else
        cout << "Test msg: Constructor test for normal cases failed!\n" << endl;


    cout<<"*****************Assignment Edge testfunction*************"<<endl;
    if (tester.assignmentEdge())
        cout << "Test msg: Assignment operator test for edge cases passed!\n" << endl;
    else
        cout << "Test msg: Assignment operator test for edge cases failed!\n" << endl;


    cout<<"*****************Recreate Error function*************"<<endl;
    cout << "Following is the test message for testing the Recreate for error cases :\n" << endl;
    if (tester.recreateror(obj1))
        cout << "Test msg: Recreate operator test for error cases passed!\n" << endl;
    else
        cout << "Test msg: Recreate operator test for error cases failed!\n" << endl;

    cout<<"*****************Recreate normal function*************"<<endl;
    cout << "Following is the test message for testing the Recreate for edge cases :\n" << endl;
    if (tester.recreatenormal(obj1))
        cout << "Test msg: Recreate operator test for normal cases passed!\n" << endl;
    else
        cout << "Test msg: Recreate operator test for normal cases failed!\n" << endl;

    cout<<"*****************Init Normal function*************"<<endl;
    obj1.initCard();
    if (tester.inticardnormal(obj1))
        cout << "Test msg: initCard test for normal cases passed!\n" << endl;
    else
        cout << "Test msg: initCard test for normal cases failed!\n" << endl;


    obj1.clear();
    if (obj1.reCreateCard(2*CARDROWS,CARDCOLS,MINVAL,MAXVAL)){
        obj1.initCard();
        obj1.dumpCard();
        balls = obj1.drawBalls();
        //obj1.dumpCard();
        cout << "\ngame over after " << obj1.play(BALLS,balls) << " hits!\n" << endl;
        obj1.dumpCard();
    }

    cout << "The following is the dump of object created by overloaded assignment operator:\n" << endl;
    obj2.dumpCard();

    return 0;
}