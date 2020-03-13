#include <iostream>
using namespace std;
#include <fstream>
#include <cmath>
#include <stdlib.h> // used for rand
#include <thread>   // std::this_thread::sleep_for needed for pause
#include <chrono>  // std::chrono::seconds needed for pause
#include "myGrid.h"

int generateRow(int row);
int generateColumn(int col);
void outputGrid(string gridFile);
int main(int argc, char **argv)
{
  // keeps count of the generation numbers from grid generated
   int generationNumber = 0;
   // holds user choice of whether they want a random configuration or file configuration
   char userInput = '\0';
   // holds the fileName
   string fileName = "";
   // inFS - object of ifstream to read from a file
   ifstream inFS;
   // holds the user's choice for the row
   int row = 0;
   // holds the user's choice for the column
   int column = 0;
   // holds the user's choice for the density population
   float userDecimalValue = 0;
   //holds the newly generated row position for existing cell
   int genRow = 0;
   //holds the newly generated column position for existing cell
   int genCol = 0;
   // number of occupied cells
   int occupiedCell = 0;
   // number of unoccupied cells
   int unoccupiedCell = 0;
   // counts number of rows
   int countRows = 0;
   // counts number of columns
   int countColumns = 0;
   // user's choice of mode to run
   int userMode = 0;
   // total number of cells
   int totalCells = 0;
   // holds the total number of occupied cells if user chooses random configuration
   float occupiedCells = 0;
   // rounded occupied cells
   int roundedOccupiedCells = 0;
   // file name of map containing random configuration
   string randomConfig = "randomConfig.txt";
   // onFS - object of fstream to write to file
   ifstream onFS;
   // stores all the string from file configuration
   string fileConfig = "";
   int outputOption = 2;
   myGrid *pGrid;


   cout << "Welcome to the Game of Life!"<< endl;
   cout << "Do you wish to start a random configuration(R) or specify a file configuration(F)? (R/F)"<< endl;
   cin >> userInput;
   userInput = toupper(userInput);
   cout << "Choose an ouput option: " << endl;
   cout << "1. Brief pause between generations (1, 2, 3)" << endl;
   cout << "2. press “Enter” to display the next generation" << endl;
   cout << "3. output everything to a file" << endl;
   cin >> outputOption;

   cout << "Which of the following Modes would you like to run? (1, 2, or 3)" << endl;
   cout << "1. Classic Mode "<< endl;
   cout << "2. Doughnut Mode "<< endl;
   cout << "3. Mirror Mode "<< endl;
   cout << "Enter: ";
   cin  >> userMode;
   // TODO: add a debugger to check if user entered 1, 2, 3, 4

   // if the user has the file configuration
   if(userInput == 'F')
   {
      // prompt the user for the filepath that holds the map
      cout << "Enter the filepath: " << endl;
      cin >> fileName;
       inFS.open(fileName);
       if(!inFS.is_open())
        {
             cout << "could not open file"<< endl;
             return 1;

        }
        while(!inFS.eof())
        {
          inFS >> fileConfig;
          countColumns = fileConfig.length();
          countRows++;
        }
        // closing the file
        inFS.close();
        // to not count the extra line given from fileConfig.txt
        countRows = countRows - 1;
        cout << "|Dimensions| row: "<< countRows << " cols: "<< countColumns << endl;
        pGrid = new myGrid(countRows,countColumns,userMode);
        char c = '\0';
        pGrid->populateGridFromFile(fileName);
        pGrid->printCurrentGrid();
   }
   // if the file wants a random configuration
   else if(userInput == 'R')
   {
     cout << "Enter the dimensions " << endl;
     cout << "row(s): ";
     cin >> row;
     cout << "column(s): ";
     cin >> column;
     cout << "Enter a decimal value for the initial population density of the world (greater than or equal to 1): ";
     cin >> userDecimalValue;
    pGrid = new myGrid(row,column,userMode);
    // populate the current grid using rand()
    pGrid->populateGridRandomly(userDecimalValue);
    pGrid->printCurrentGrid();
  }
//Brief pause 
// handle the three ouput options
  if(outputOption == 1)
  {
    char userChoice = '\0';
    int generationNumber = 0;
    const int maxGenerationNUmber = 50;
     // call the Classic class
     cout << "calling the Classic Mode class" << endl;
     bool isStable = false;
     bool isEmpty = false;
     cout << "Generation: " << generationNumber << endl;
     // now we need to set it to 1 so it can start the next one correctly
     // in the loop
     generationNumber = 1;
     pGrid->printCurrentGrid();
     do{
       cout << "Generation: " << generationNumber << endl;
       pGrid->populateAllNextGen();
       cout << "printing: " << endl;
       pGrid->printNextGenGrid();
       isStable = pGrid->isCurrentGenEqualToNextGen();
       pGrid->updateCurrentGenFromNextGen();
       isEmpty = pGrid->isCurrentGridEmpty();
       if(isStable)
       {
          cout << "Generation is stable: Press 'x' to exit"<< endl;
          cin >> userChoice;
          userChoice = tolower(userChoice);
       }
       else if(isEmpty)
       {
         cout <<"Generation is empty: Press 'x' to exit" << endl;
         cin >> userChoice;
         userChoice = tolower(userChoice);
       }
       else
       {
         // sleep for 1 second
         this_thread::sleep_for (std::chrono::seconds(1));
       }
       generationNumber++;
     }while((userChoice != 'x') && (generationNumber < maxGenerationNUmber));
     cout << "exiting"<< endl;
     // delete pointer of myGrid type
     delete pGrid;
  }
  else if(outputOption == 2)
  {
  // TODO: delete the couts
  // call the class for as many generations as needed
  // prompt user if they would like to use the pause function
       char userChoice = '\0';
       int generationNumber = 0;
        // call the Classic class
        cout << "calling the Classic Mode class" << endl;
        bool isStable = false;
        bool isEmpty = false;
        cout << "Generation: " << generationNumber << endl;
        // now we need to set it to 1 so it can start the next one correctly
        // in the loop
        generationNumber = 1;
        pGrid->printCurrentGrid();
        do{
          cout << "Generation: " << generationNumber << endl;
          pGrid->populateAllNextGen();
          cout << "printing: " << endl;
          pGrid->printNextGenGrid();
          isStable = pGrid->isCurrentGenEqualToNextGen();
          pGrid->updateCurrentGenFromNextGen();
          isEmpty = pGrid->isCurrentGridEmpty();
          if(isStable)
          {
             cout << "Generation is stable: Press 'x' to exit"<< endl;
             cin >> userChoice;
             userChoice = tolower(userChoice);
          }
          else if(isEmpty)
          {
            cout <<"Generation is empty: Press 'x' to exit" << endl;
            cin >> userChoice;
            userChoice = tolower(userChoice);
          }
          else
          {
            cout << "Press 'c' to continue and 'x' to exit" << endl;
            cin >> userChoice;
            userChoice = tolower(userChoice);
          }
          generationNumber++;
        }while(userChoice == 'c');
        cout << "exiting"<< endl;
        // delete pointer of myGrid type
        delete pGrid;
  }
  else if(outputOption == 3)
  {
    string fileToOutput = "";
    ofstream onFS;
    cout << "Enter the output filepath: " << endl;
    cin >> fileToOutput;
    // Open the file and truncate. File must be empty at start
    onFS.open(fileToOutput);
    if(!onFS.is_open())
      {
        cout << "could not open file: "<<fileToOutput<< endl;
        return 1;
      }
      else
      {
        onFS.close();
      }
    //char userChoice = '\0';
    int generationNumber = 0;
    const int maxGenerationNUmber = 50;
     // call the Classic class
     cout << "calling the file output option" << endl;
     bool isStable = false;
     bool isEmpty = false;
     do{
       cout << "Generation: " << generationNumber << endl;
       onFS.open(fileToOutput, ofstream::out | ofstream::app);
       if(onFS.is_open())
       {
          onFS << "Generation: "<< generationNumber << endl;
          onFS.close();
       }
       pGrid->populateAllNextGen();
       cout << "printing: " << endl;
       pGrid->writeCurrentGridToFile(fileToOutput);
       isStable = pGrid->isCurrentGenEqualToNextGen();
       pGrid->updateCurrentGenFromNextGen();
       isEmpty = pGrid->isCurrentGridEmpty();
       if(isStable)
       {
          cout << "Generation is stable: exiting"<< endl;
          // break out of do-while loop
          break;
       }
       else if(isEmpty)
       {
         cout <<"Generation is empty: exiting" << endl;
         // break out of do-while loop
         break;
       }
       generationNumber++;
     }while(generationNumber < maxGenerationNUmber);
     onFS.open(fileToOutput, ofstream::out | ofstream::app);
     if(onFS.is_open())
     {
        onFS << "Last Generation" << endl;
        onFS.close();
     }
     pGrid->writeCurrentGridToFile(fileToOutput);
     cout << "exiting"<< endl;
     // delete pointer of myGrid type
     delete pGrid;

  }

  return 0;
}
int generateRow(int row)
{
    // use rand to randomly generate a row
    int newRow = 0;
    newRow = rand() % row;
    return newRow;
}
int generateColumn(int col)
{
   // use rand to randomly generate a column
   int newCol = 0;
   newCol = rand() % col;
   return newCol;
}
void outputGrid(string gridFile)
{
  ifstream infile;
  string letsRead = "";
  infile.open(gridFile);
  if(!infile.is_open())
   {
     cout << "could not open file"<< endl;
   }
  while(!infile.eof())
   {
    letsRead = "";
    infile >> letsRead;
    cout <<letsRead<< endl;
   }
  infile.close();
}
