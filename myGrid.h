#include<iostream>
#include<string>
using namespace std;
class myGrid
{
public:
     // constructor
     myGrid();
     // overloaded constructor
     myGrid(int rows, int columns, int mode);
     // destructor
     ~myGrid();
     int determineNumOfNeighbors(int row, int column);
     // MODES
      // classic mode
      int ClassicMode(int i, int j);
      // doughnut mode
      int DoughnutMode(int i, int j);
      // mirror mode
      int MirrorMode(int i, int j);
      // general rules: determines if cell lives or dies based on number of neighbors
      bool liveOrDie(int row, int column);

     // POPULATE
      // once we know whether cell lives or dies from liveOrDie() then we can populate the next generation grid
      void populateNextGenGrid(int i, int j);
      // set all the elements of the current grid to dashes
      void initializeCurrentGrid();
      // populateGridRandomly - populates the grid based on the population density from user input in main.
      void populateGridRandomly(float populationDensity);
      //populateGridFromFile - populates the grid from the file the user provided
      void populateGridFromFile(string fileName);


     // PRINT GRID
      // printCurrentGrid - prints the current grid
      void printCurrentGrid();
      // printNextGenGrid - prints the next generation grid
      void printNextGenGrid();
      // printGridFromFile - output and append grid to file
      void writeCurrentGridToFile(string myFileName);
      // printNextGenGridFromFile
      void writeNextGenGridToFile(string myFileName);

     // GENERATES RANDOM ROW AND COLUMN POSITIONS
      // generateRow - generates a new row
      int generateRow(int row);
      // generateColumn - generates a new column
      int generateColumn(int col);

      void populateAllNextGen();
      // copy elements from nextGen into Current Gen array
      void updateCurrentGenFromNextGen();
      // to check if the current grid is equal to the next currentGrid
      // This is useful in detecting stabalization
      bool isCurrentGenEqualToNextGen();
      bool isCurrentGridEmpty();
      // Populates the extended current Grid
      void populateExtendedCurrentGrid();
      void populateNextGenGridFromExtended(int i, int j);
      // set all elements of extended current Grid to dashes 
      void clearExtendedCurrentGrid();

   private:
     // holds the number of rows from grid
     int rows;
     // holds the number of columns from grid
     int columns;
     // holds the number of rows for expanded grid
     int extendedRows;
     // holds the number of columns for expanded grid
     int extendedColumns;
     // holds the mode#
     int mode;
     // holds the current grid
     char ** currentGrid;
     // holds the next generation grid
     char ** nextGenGrid;
     // holds the extended current array, used for mirror mode
     char ** extendedCurrentGrid;
     // holds the extended next generation array, used for mirror mode
     //char ** extendedNextGenGrid;
};
