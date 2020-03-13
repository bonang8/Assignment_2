#include <iostream>
#include <cmath>
#include <stdlib.h> // used for rand
#include <fstream>
#include <string>
#include "myGrid.h"
using namespace std;

myGrid::myGrid()
{
  columns = 5;
  rows = 5;
  extendedRows = rows + 2;
  extendedColumns = columns + 2;
  int mode = 1;
  // currentGrid
  currentGrid = new char*[rows];
  for( int i = 0; i < rows; ++i)
  {
    currentGrid[i] = new char[columns];
  }
  // next generation
  nextGenGrid = new char*[rows];
  for( int j = 0; j < rows; ++j)
  {
    nextGenGrid[j] = new char[columns];
  }
  // extended grid that includes 2 extra columns and rows
  extendedCurrentGrid = new char*[extendedRows];
  for(int j = 0; j < extendedRows; ++j)
  {
    extendedCurrentGrid[j] = new char[extendedColumns];
  }

}
myGrid::myGrid(int rows, int columns, int mode)
{
  this->rows = rows;
  this->columns = columns;
  this->mode = mode;
  extendedRows = rows + 2;
  extendedColumns = columns + 2;
  currentGrid = new char*[rows];
  // given the rows and columns from main(), have both grids be the specified size
  for( int i = 0; i < rows; ++i)
  {
    currentGrid[i] = new char[columns];
  }
  nextGenGrid = new char*[rows];
  for( int j = 0; j < rows; ++j)
  {
    nextGenGrid[j] = new char[columns];
  }
  // extended grid that includes 2 extra columns and rows
  extendedCurrentGrid = new char*[extendedRows];
  for(int j = 0; j < extendedRows; ++j)
  {
    extendedCurrentGrid[j] = new char[extendedColumns];
  }

}
myGrid::~myGrid()
{
  // TODO: delete 2D array here
}

void myGrid::updateCurrentGenFromNextGen()
{
  for(int i = 0; i < this->rows; ++i)
  {
    for(int j = 0; j < this->columns; ++j)
    {
      currentGrid[i][j] = nextGenGrid[i][j];
    }
  }
}

bool myGrid::isCurrentGenEqualToNextGen()
{
  bool isEqual = true;
  for(int i = 0; i < this->rows; ++i)
  {
    for(int j = 0; j < this->columns; ++j)
    {
      if(currentGrid[i][j] != nextGenGrid[i][j])
      {
        isEqual = false;
        break;
      }

    }
  }
      return isEqual;
}

bool myGrid::isCurrentGridEmpty()
{
  bool isEmpty = true;
  for(int i = 0; i < this->rows; ++i)
  {
    for(int j = 0; j < this->columns; ++j)
    {
      // if it finds any 'X' then its not empty
      if(currentGrid[i][j] == 'X')
      {
        isEmpty = false;
      }

    }
  }
  return isEmpty;
}


// populate the whole next generation grid
void myGrid::populateAllNextGen()
{
  // Classic Mode
  if(this->mode == 1)
   for( int i = 0; i < this->rows; ++i)
   {
     for(int j = 0; j < this->columns; ++j)
     {
       populateNextGenGrid(i,j);
     }
   }
   // Doughnut Mode
   else if(this->mode == 2)
   {
     for( int i = 0; i < this->rows; ++i)
     {
       for(int j = 0; j < this->columns; ++j)
       {
         populateNextGenGrid(i,j);
       }
     }
   }
   // Mirror Mode
   else if(this->mode == 3)
   {
     //cout << "diag: in populateAllNextGen, Mirror Mode" << endl;
      populateExtendedCurrentGrid();
      for( int i = 1; i < extendedRows-1; ++i)
      {
        for(int j = 1; j < extendedColumns-1; ++j)
        {
          populateNextGenGridFromExtended(i,j);
        }
      }
   }
   else
   {
     cout << "Error: wrong mode selected" << endl;
   }
}

void myGrid::populateNextGenGridFromExtended(int i, int j)
{
  //cout << "diag: in populateNextGenGridFromExtended, Mirror Mode" << endl;
  bool containsCell = false;
  //cout << "diag: populateNextGenGrid[" << i << "]" << "[" << j << "]"<< endl;
  containsCell = liveOrDie(i, j);
  //cout << "diag: live or die completed for i and j. Contains cell: " << containsCell<< " a[" << i << "]" << "[" << j << "]"<< endl;
  if(containsCell == true)
  {
    //translate back to normal rows and columns from extended
    nextGenGrid[i-1][j-1] = 'X';
  }
  else
  {
    //translate back to normal rows and columns from extended
    nextGenGrid[i-1][j-1] = '-';
  }

}

// populateNextGenGrid - populate the next generation grid
//                       From the live or die, we are able to populate next
//                       generation grid with X's and '-'s
void myGrid::populateNextGenGrid(int i, int j)
{
  bool containsCell = false;
  //cout << "diag: populateNextGenGrid[" << i << "]" << "[" << j << "]"<< endl;
  containsCell = liveOrDie(i, j);
  //cout << "diag: live or die completed for i and j. Contains cell: " << containsCell<< " a[" << i << "]" << "[" << j << "]"<< endl;
  if(containsCell == true)
  {
    nextGenGrid[i][j] = 'X';
  }
  else
  {
    nextGenGrid[i][j] = '-';
  }

}
// liveOrDie - returns true if cell lives or false if cell dies
//             based on number of neighbors
bool myGrid::liveOrDie(int row, int column)
{
  int neighbors = 0;
  bool live = true;
  bool die = false;
   // get the amount of neighbors from determineNumOfNeighbors()
  neighbors = determineNumOfNeighbors(row, column);
  //cout << "diag: called determineNumOfNeighbors"<< endl;
  //cout << "diag: number of neighbors: " << neighbors <<" row: " << row << " col: "<< column<< endl;
  // ClassicMode
  if(mode == 1 || mode == 2)
  {
      if(neighbors <= 1){
         // no need to check for 'X' and '-' because whether that cell contains an 'X' or '-' it dies
         return die;
       }
      else if(neighbors == 2){
         if(currentGrid[row][column] == 'X'){
             return live;
           }
         else if(currentGrid[row][column] == '-'){
             return die;
           }
      }
     else if(neighbors == 3){
          // whether 'X' or '-', a new cell is born
          return live;
        }
     else if(neighbors >= 4){
         // no need to check for 'X' and '-' because whether that cell contains an 'X' or '-' it dies
         return die;
       }
   }
   // Mirror Mode
   else if(mode == 3)
   {
     //cout << "diag: in liveOrDie, MirrorMode" << endl;
     if(neighbors <= 1){
        // no need to check for 'X' and '-' because whether that cell contains an 'X' or '-' it dies
        return die;
      }
     else if(neighbors == 2){
        if(extendedCurrentGrid[row][column] == 'X'){
            return live;
          }
        else if(extendedCurrentGrid[row][column] == '-'){
            return die;
          }
     }
    else if(neighbors == 3){
         // whether 'X' or '-', a new cell is born
         return live;
       }
    else if(neighbors >= 4){
        // no need to check for 'X' and '-' because whether that cell contains an 'X' or '-' it dies
        return die;
      }
   }


}

int myGrid::determineNumOfNeighbors(int row, int column)
{
    int numberOfNeighbors = 0;

    if (1 == this->mode)
    {
        // Classic Mode
        // returns number of neighbors for Classic Mode
        numberOfNeighbors = ClassicMode(row,column);

    }
    else if (2 == this->mode)
    {
        // Doughnut Mode (Torus Mode)
        numberOfNeighbors = DoughnutMode(row, column);

    }
    else if (3 == this->mode)
    {
        // Mirror Mode
        numberOfNeighbors = MirrorMode(row, column);

    }

    return numberOfNeighbors;
}
// returns the number og neighbors by the rules of mirror mode
void myGrid::populateExtendedCurrentGrid()
{
  // counts the number of neighbors
  int countNeighbors = 0;
  // clear out the X's from the current extended grid in preparation for
  // the extended grid being populated from the current grid
   clearExtendedCurrentGrid();
   // populate the extended grid with the currentGrid's elements
   // since extended row has 2 extra columns and rows, all the positions
   // will need to be adjusted.
   //cout << "diag: populateExtendedCurrentGrid, Mirror Mode, 1 " << endl;
   for(int i = 0; i < rows; ++i)
   {
     for(int j = 0; j < columns; ++j)
     {
       extendedCurrentGrid[i+1][j+1] = currentGrid[i][j];
     }
   }
   //cout << "diag: populateExtendedCurrentGrid, Mirror Mode, 2 " << endl;
   // Now, we will need to populate outer most parts of extended array according
   // to mirror mode.
   // To do so, look for corner and sides of original array


   // top left corner
   if(currentGrid[0][0] == 'X')
   {
     extendedCurrentGrid[0][0] = 'X';
     extendedCurrentGrid[0][1] = 'X';
     extendedCurrentGrid[1][1] = 'X';
   }
   // top right corner
   else if(currentGrid[0][columns-1] == 'X')
   {
      extendedCurrentGrid[0][extendedColumns-1] = 'X';
      extendedCurrentGrid[0][extendedColumns-2] = 'X';
      extendedCurrentGrid[1][extendedColumns-1] = 'X';
   }
   // bottom right corner
   else if(currentGrid[rows-1][columns-1] == 'X')
   {
     extendedCurrentGrid[extendedRows - 2][0];
     extendedCurrentGrid[extendedRows - 1][0];
     extendedCurrentGrid[extendedRows - 1][1];
   }
   // bottom left corner
   else if(currentGrid[rows-1][0] == 'X')
   {
      extendedCurrentGrid[extendedRows - 2][extendedColumns - 1] = 'X';
      extendedCurrentGrid[extendedRows - 1][extendedColumns - 1] = 'X';
      extendedCurrentGrid[extendedRows - 1][extendedColumns - 2] = 'X';
   }
   //cout << "diag: populateExtendedCurrentGrid, Mirror Mode, 3 " << endl;
   for( int j = 0; j < columns; ++j)
   {
   // top side
   if(currentGrid[0][j] == 'X')
   {
      extendedCurrentGrid[0][j+1] = 'X';
   }
   // bottom sides
   else if(currentGrid[rows-1][j] == 'X')
   {
      extendedCurrentGrid[extendedRows-1][j+1] = 'X';
   }
 }
   //cout << "diag: populateExtendedCurrentGrid, Mirror Mode, 3.5 " << endl;
  for( int i = 0; i < rows; ++i)
  {
   // right side
   if(currentGrid[i][columns-1] == 'X')
   {
      extendedCurrentGrid[i+1][extendedColumns-1] = 'X';
   }
   // left side
   else if(currentGrid[i][0] == 'X')
   {
     extendedCurrentGrid[i+1][0] = 'X';
   }
 }
//cout << "diag: exiting populateExtendedCurrentGrid, Mirror Mode, 4" << endl;

}
// DoughnutMode
int myGrid::DoughnutMode(int i, int j)
{
  int countNeighbors = 0;

  //cout << "diag: in DoughnutMode, beginning "<< " i: " << i << ", j: " << j << endl;

  // Corners
   //If the cell position is the right corner
   // check if the cell to its left is occupied
   // check if the cell diagonal to it is occupied
   // check if the cell below it is occupied

   // top right corner
  if((i == 0) && (j == (columns-1)))
  {
    //cout << "diag: top right corner"<< endl;
    // main 3
      // left
      if (currentGrid[0][columns-2] == 'X')
      {
         countNeighbors++;
      }
      //left down
      if(currentGrid[1][columns-2] =='X')
      {
        countNeighbors++;
      }
      //down
      if(currentGrid[1][columns-1] == 'X')
      {
        countNeighbors++;
      }
    //The remaining 5
      // bottom 2 (straight down)
      if(currentGrid[rows -1][columns-1] == 'X')
      {
        countNeighbors++;
      }
      if(currentGrid[rows-1][columns-2]== 'X')
      {
        countNeighbors++;
      }
      // 1 diagonal
      if(currentGrid[rows-1][0]=='X')
      {
        countNeighbors++;
      }
      // 2 sides
      if(currentGrid[0][0] == 'X')
      {
        countNeighbors++;
      }
      if(currentGrid[0][1] == 'X')
      {
        countNeighbors++;
      }
      //cout << "diag: in DoughnutMode, top right corner "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // top left corner
  else if((i == 0) && (j == 0))
  {
    //cout << "diag: top left corner"<< endl;
    // main three
     // right
    if(currentGrid[0][1] == 'X')
    {
      countNeighbors++;
    }
    //diagonal
    if(currentGrid[1][1] == 'X')
    {
      countNeighbors++;
    }
    //down
    if(currentGrid[1][0] == 'X')
    {
      countNeighbors++;
    }
    // remaining 5
      // bottom two(straight down)
      if(currentGrid[rows-1][0] == 'X')
      {
        countNeighbors++;
      }
      if(currentGrid[rows-1][1] == 'X')
      {
        countNeighbors++;
      }
      // 1 diagonal
      if(currentGrid[rows-1][columns-1])
      {
        countNeighbors++;
      }
      // 2 sides (parallel)
      if(currentGrid[0][columns-1])
      {
        countNeighbors++;
      }
      if(currentGrid[1][columns-1])
      {
        countNeighbors++;
      }
      //cout << "diag: in DoughnutMode, top left corner "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // bottom right corner
  else if((i == (rows-1)) && (j == (columns-1)))
  {
    //cout << "diag: bottom right corner"<< endl;
    // main 3
    if(currentGrid[rows-1][columns-2] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[rows-2][columns-2] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[rows-2][columns-1] == 'X')
    {
      countNeighbors++;
    }
    // 2 top
    if(currentGrid[0][columns-1] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[0][columns-2] == 'X')
    {
      countNeighbors++;
    }
    // 2 sides (//)
    if(currentGrid[rows-1][0] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[rows-2][0] == 'X')
    {
      countNeighbors++;
    }
    // diagonal
    if(currentGrid[0][0] == 'X')
    {
      countNeighbors++;
    }
    //cout << "diag: in DoughnutMode, bottom right corner "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // bottom left corner
  else if((i == (rows-1)) && (j == 0))
  {
    //cout << "diag: bottom left corner"<< endl;
    // main three
    if(currentGrid[rows-1][1] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[rows-1][1] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[rows-2][0] == 'X')
    {
      countNeighbors++;
    }
    // 2 top
    if(currentGrid[0][0] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[0][1]== 'X')
    {
      countNeighbors++;
    }
    // 2 sides (//)
    if(currentGrid[rows-1][columns-1] == 'X')
    {
      countNeighbors++;
    }
    if(currentGrid[rows-2][columns-1] == 'X')
    {
      countNeighbors++;
    }
    // 1 diagonal
    if(currentGrid[0][columns-1] == 'X')
    {
      countNeighbors++;
    }
    //cout << "diag: in DoughnutMode, bottom left corner "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // Check top,down, sides : for non-corners and not in middle of grid
  // top part
  else if((i == 0) && (j < columns-1) && (j!=0))
  {
    //cout << "diag: top part"<< endl;
    if(currentGrid[i][j] == 'X' || currentGrid[i][j] == '-')
    {
      // check main 5
        // right
        if(currentGrid[i][j+1] == 'X')
        {
          countNeighbors++;
        }
        // left
        if(currentGrid[i][j-1] == 'X')
        {
          countNeighbors++;
        }
        // right diagonal
        if(currentGrid[i+1][j+1] == 'X')
        {
          countNeighbors++;
        }
        // below it
        if(currentGrid[i+1][j] == 'X')
        {
          countNeighbors++;
        }
        // left diagonal
        if(currentGrid[i+1][j-1]== 'X')
        {
          countNeighbors++;
        }
      // check the 3 phantoms
        if(currentGrid[rows-1][j] == 'X')
        {
          countNeighbors++;
        }
        if(currentGrid[rows-1][j+1] == 'X')
        {
          countNeighbors++;
        }
        if(currentGrid[rows-1][j-1] == 'X')
        {
          countNeighbors++;
        }
    }
    //cout << "diag: in DoughnutMode, top part "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // bottom part
  else if((i == rows-1) && (j < columns-1) && (j!=0))
  {
    //cout << "diag: bottom part"<< endl;
    if(currentGrid[i][j] == 'X' || currentGrid[i][j] == '-')
    {
      // check main 5
        // right
        if(currentGrid[i][j+1] == 'X')
        {
          countNeighbors++;
        }
        // left
        if(currentGrid[i][j-1] == 'X')
        {
          countNeighbors++;
        }
        // right up
        if(currentGrid[i-1][j+1] == 'X')
        {
          countNeighbors++;
        }
        // Up
        if(currentGrid[i-1][j] == 'X')
        {
          countNeighbors++;
        }
        // left up
        if(currentGrid[i-1][j-1]== 'X')
        {
          countNeighbors++;
        }
      // check the 3 phantoms
       // phantom left down
        if(currentGrid[0][j-1] == 'X')
        {
          countNeighbors++;
        }
        //phantom down
        if(currentGrid[0][j] == 'X')
        {
          countNeighbors++;
        }
        // phatom right down
        if(currentGrid[0][j+1] == 'X')
        {
          countNeighbors++;
        }
    }
    //cout << "diag: in DoughnutMode, bottom part "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // left side
  else if((i < rows-1) && (j == 0) && (i!=0))
  {
    //cout << "diag: left side"<< endl;
    // check main 5
      // up
      if(currentGrid[i-1][0] == 'X')
      {
        countNeighbors++;
      }
      // down
      if(currentGrid[i+1][0] == 'X')
      {
        countNeighbors++;
      }
      // right down
      if(currentGrid[i+1][j+1] == 'X')
      {
        countNeighbors++;
      }
      // right
      if(currentGrid[i][j+1] == 'X')
      {
        countNeighbors++;
      }
      // right up
      if(currentGrid[i-1][j+1]== 'X')
      {
        countNeighbors++;
      }
    // check the 3 phantoms
      // phantom left
      if(currentGrid[i][columns-1] == 'X')
      {
        countNeighbors++;
      }
      //phantom left up
      if(currentGrid[i-1][columns-1] == 'X')
      {
        countNeighbors++;
      }
      //phantom down
      if(currentGrid[i+1][columns-1] == 'X')
      {
        countNeighbors++;
      }
      //cout << "diag: in DoughnutMode, left side "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // right side
  else if((i < rows-1) && (j == columns -1) && (i!=0))
  {
    //cout << "diag: right side"<< endl;
    // check main 5
      // up
      if(currentGrid[i-1][j] == 'X')
      {
        countNeighbors++;
      }
      // left down
      if(currentGrid[i+1][j-1] == 'X')
      {
        countNeighbors++;
      }
      //left up
      if(currentGrid[i-1][j-1] == 'X')
      {
        countNeighbors++;
      }
      // down
      if(currentGrid[i+1][j] == 'X')
      {
        countNeighbors++;
      }
      //left
      if(currentGrid[i][j-1]== 'X')
      {
        countNeighbors++;
      }
    // check the 3 phantoms
     // phantom right
      if(currentGrid[i][0] == 'X')
      {
        countNeighbors++;
      }
      // phantom right up
      if(currentGrid[i-1][0] == 'X')
      {
        countNeighbors++;
      }
      // phantom right down
      if(currentGrid[i+1][0] == 'X')
      {
        countNeighbors++;
      }
    //cout << "diag: in DoughnutMode, right side "<< " count Neighbors: " << countNeighbors<< endl;
  }
  // not a corner or side
  // follows Mirror mode
  else
  {
  //cout << "diag: interior elements Classic Mode"<< endl;
    // classic mode will count the standard 8
   countNeighbors = ClassicMode(i,j);
   //cout << "diag: in DoughnutMode, Classic Mode "<< " numberOfNeighbors: " << countNeighbors<< endl;

  }
  return countNeighbors;
}
int myGrid::MirrorMode(int i, int j)
{
   //cout << "diag: in MirrorMode, Mirror Mode" << endl;
  int countNeighbors = 0;
  // TODO: delete comments
  if(extendedCurrentGrid[i][j] == 'X' || extendedCurrentGrid[i][j] == '-')
   {
       // Left up (corner)
       if(((i-1) >= 0 && (i-1) < extendedRows) && ((j-1) >= 0 && (j-1) < extendedColumns)){
         if(extendedCurrentGrid[i-1][j-1] == 'X')
          {
            //cout << "{-1, -1}" << endl;
            //cout << "a["<< i-1 << "]" << "[" << j-1<< "]"<< endl;
            countNeighbors++;
           }
       }
       //Left
        if(((i-1) >= 0 && (i-1) < extendedRows) && ((j) >= 0 && (j) < extendedColumns))
        {
           if(extendedCurrentGrid[i-1][j] == 'X')
           {
            //cout << "{-1, 0}" << endl;
            //cout << "a["<< i-1 << "]" << "[" << j << "]"<< endl;
            countNeighbors++;
           }
       }
        // Left Down
        if(((i-1) >= 0 && (i-1) < extendedRows) && ((j+1) >= 0 && (j+1) < extendedColumns))
       {
          if(extendedCurrentGrid[i-1][j+1] == 'X')
          {
            //cout << "{-1, 1}" << endl;
            //cout << "a["<< i-1 << "]" << "[" << j+1 << "]"<< endl;
            countNeighbors++;
           }
       }
       // Up
       if(((i) >= 0 && (i) < extendedRows) && ((j-1) >= 0 && (j-1) < extendedColumns))
       {
           if(extendedCurrentGrid[i][j-1] == 'X')
           {
             //cout << "{0, -1}" << endl;
             //cout << "a["<< i << "]" << "[" << j-1 << "]"<< endl;
             countNeighbors++;
           }
       }
        // Down
        if(((i) >= 0 && (i) < extendedRows) && ((j+1) >= 0 && (j+1) < extendedColumns))
       {
            if(extendedCurrentGrid[i][j+1] == 'X')
            {
             //cout << "{0, 1}" << endl;
             //cout << "a["<< i << "]" << "[" << j+1 << "]"<< endl;
             countNeighbors++;
            }
       }

      // Right Up
      if(((i+1) >= 0 && (i+1) < extendedRows) && ((j-1) >= 0 && (j-1) < extendedColumns))
       {
           if(extendedCurrentGrid[i+1][j-1] == 'X')
           {
            //cout << "{1, -1}" << endl;
            //cout << "a["<< i+1 << "]" << "[" << j-1 << "]"<< endl;
            countNeighbors++;
           }
       }
        // Right
        if(((i+1) >= 0 && (i+1) < extendedRows) && ((j) >= 0 && (j) < extendedColumns))
       {
            if(extendedCurrentGrid[i+1][j] == 'X')
           {
             //cout << "{1, 0}" << endl;
             //cout << "a["<< i+1 << "]" << "[" << j << "]"<< endl;
             countNeighbors++;
           }
       }
       // Right Down
       if(((i+1) >= 0 && (i+1) < extendedRows) && ((j+1) >= 0 && (j+1) < extendedColumns))
       {
            if(extendedCurrentGrid[i+1][j+1] == 'X')
            {
             //cout << "{1, 1}" << endl;
             //cout << "a["<< i+1 << "]" << "[" << j+1 << "]"<< endl;
             countNeighbors++;
            }
       }
  }
    return countNeighbors;
}

// returns the number of neighbors by the rules of classic mode
int myGrid::ClassicMode(int i, int j)
{
  int countNeighbors = 0;
  // TODO: delete comments
  if(currentGrid[i][j] == 'X' || currentGrid[i][j] == '-')
   {
       // Left up (corner)
       if(((i-1) >= 0 && (i-1) < rows) && ((j-1) >= 0 && (j-1) < columns)){
         if(currentGrid[i-1][j-1] == 'X')
          {
            //cout << "{-1, -1}" << endl;
            //cout << "a["<< i-1 << "]" << "[" << j-1<< "]"<< endl;
            countNeighbors++;
           }
       }
       //Left
        if(((i-1) >= 0 && (i-1) < rows) && ((j) >= 0 && (j) < columns))
        {
           if(currentGrid[i-1][j] == 'X')
           {
            //cout << "{-1, 0}" << endl;
            //cout << "a["<< i-1 << "]" << "[" << j << "]"<< endl;
            countNeighbors++;
           }
       }
        // Left Down
        if(((i-1) >= 0 && (i-1) < rows) && ((j+1) >= 0 && (j+1) < columns))
       {
          if(currentGrid[i-1][j+1] == 'X')
          {
            //cout << "{-1, 1}" << endl;
            //cout << "a["<< i-1 << "]" << "[" << j+1 << "]"<< endl;
            countNeighbors++;
           }
       }
       // Up
       if(((i) >= 0 && (i) < rows) && ((j-1) >= 0 && (j-1) < columns))
       {
           if(currentGrid[i][j-1] == 'X')
           {
             //cout << "{0, -1}" << endl;
             //cout << "a["<< i << "]" << "[" << j-1 << "]"<< endl;
             countNeighbors++;
           }
       }
        // Down
        if(((i) >= 0 && (i) < rows) && ((j+1) >= 0 && (j+1) < columns))
       {
            if(currentGrid[i][j+1] == 'X')
            {
             //cout << "{0, 1}" << endl;
             //cout << "a["<< i << "]" << "[" << j+1 << "]"<< endl;
             countNeighbors++;
            }
       }

      // Right Up
      if(((i+1) >= 0 && (i+1) < rows) && ((j-1) >= 0 && (j-1) < columns))
       {
           if(currentGrid[i+1][j-1] == 'X')
           {
            //cout << "{1, -1}" << endl;
            //cout << "a["<< i+1 << "]" << "[" << j-1 << "]"<< endl;
            countNeighbors++;
           }
       }
        // Right
        if(((i+1) >= 0 && (i+1) < rows) && ((j) >= 0 && (j) < columns))
       {
            if(currentGrid[i+1][j] == 'X')
           {
             //cout << "{1, 0}" << endl;
             //cout << "a["<< i+1 << "]" << "[" << j << "]"<< endl;
             countNeighbors++;
           }
       }
       // Right Down
       if(((i+1) >= 0 && (i+1) < rows) && ((j+1) >= 0 && (j+1) < columns))
       {
            if(currentGrid[i+1][j+1] == 'X')
            {
             //cout << "{1, 1}" << endl;
             //cout << "a["<< i+1 << "]" << "[" << j+1 << "]"<< endl;
             countNeighbors++;
            }
       }
  }
    return countNeighbors;
}


// populateGridFromFile - reads from the file and populates the grid.
void myGrid::populateGridFromFile(string fileName)
{
  ifstream myfile;
  int countRows = 0;
  string fileConfig = "";
  myfile.open(fileName);
  if(!myfile.is_open())
   {
        cout << "could not open file"<< endl;
        return;

   }
   cout << "diag: the file opened" << endl;
   myfile >> fileConfig;
   while(!myfile.eof())
   {
     cout << "diag: fileConfig " << fileConfig << endl;
     for( int i = 0; i < fileConfig.length(); ++i)
     {
       if(fileConfig[i] == 'X' || fileConfig[i] == '-')
       {
         // read a single row by row count and i for columns then assign
         // to each character from file
          currentGrid[countRows][i] = fileConfig[i];
        }

     }
       myfile >> fileConfig;
       countRows++;
   }
  myfile.close();
}
// outputGridFromFile - append everything from currentGrid and output it like a 2D grid
void myGrid::writeCurrentGridToFile(string myFileName)
{
  ofstream onFS;
  // use to append and output to the file
  onFS.open(myFileName, ofstream::out | ofstream::app);
  if(!onFS.is_open())
  {
    cout << "could not open file" << endl;
    return;
  }
  // if open, append everything from currentGrid and output it like a 2D grid
  if(onFS.is_open())
  {
    for( int i = 0; i < this->rows; ++i)
    {
      for(int j = 0; j < this->columns; ++j)
      {
        onFS << currentGrid[i][j] << " ";
      }
      onFS << endl;
    }
  }
  onFS.close();
}

void myGrid::writeNextGenGridToFile(string myFileName)
{
  ofstream onFS;
  // use to append and output to the file
  onFS.open(myFileName, ofstream::out | ofstream::app);
  if(!onFS.is_open())
  {
    cout << "could not open file" << endl;
    return;
  }
  // if open, append everything from currentGrid and output it like a 2D grid
  if(onFS.is_open())
  {
    for( int i = 0; i < this->rows; ++i)
    {
      for(int j = 0; j < this->columns; ++j)
      {
        onFS << nextGenGrid[i][j] << " ";
      }
      onFS << endl;
    }
  }
}

// populateGridRandomly - populates the grid based on the population density from user input in main.
void myGrid::populateGridRandomly(float populationDensity)
{
  // counts number of occupied cells
  int countOC = 0;
  int totalCells = 0;
  int occupiedCells = 0;
  int roundedOccupiedCells = 0;
  int genRow = 0;
  int genCol = 0;
  totalCells = this->rows * this->columns;
  cout << "diag: total cells" << totalCells << endl;
  occupiedCells = totalCells*populationDensity;
  roundedOccupiedCells = round(occupiedCells);
  cout << "diag: rounded occupied cells: " << roundedOccupiedCells << endl;
  // call initializeCurrentGrid to set all grid elements to '-'
  this->initializeCurrentGrid();
  cout << "diag: initializeCurrentGrid" << endl;
  // while countOC is less then the number of occupied cells
  // add 'X' to the randomly generated cell position
  while(countOC < roundedOccupiedCells){
      cout << "generating row and columns" << endl;
      genRow = generateRow(this->rows);
      cout << "row: " << genRow;

      genCol = generateColumn(this->columns);
      cout << " column: " << genCol;
      cout << endl;
      // check if this grid position has already been occupied.
      if(currentGrid[genRow][genCol] == 'X')
      {
        //cout << endl;
        //cout << "Row: " << genRow << "Col: " << genCol << endl;
        //cout << "already has an X" << endl;
        genRow = generateRow(this->rows);
        //cout << "row: " << genRow;
        genCol = generateColumn(this->columns);
        //cout << " column: " << genCol;
        //cout << endl;
        currentGrid[genRow][genCol] = 'X';
      }
      else{
        currentGrid[genRow][genCol] = 'X';
        //cout << "From grid: " << randomGrid[genRow][genCol] << endl;
      }
      countOC++;
        //cout << "Count:" << countOC << endl;
    }

}
int myGrid::generateRow(int row)
{
    // use rand to randomly generate a row
    int newRow = 0;
    newRow = rand() % row;
    return newRow;
}
int myGrid::generateColumn(int column)
{
   // use rand to randomly generate a column
   int newCol = 0;
   newCol = rand() % column;
   return newCol;
}

void myGrid::printCurrentGrid()
{
  for( int i = 0; i < this->rows; ++i)
  {
    for(int j = 0; j < this->columns; ++j)
    {
      cout << currentGrid[i][j]<< " ";
    }
      cout << endl;
  }
}

void myGrid::printNextGenGrid()
{
  for( int i = 0; i < this->rows; ++i)
  {
    for(int j = 0; j < this->columns; ++j)
    {
      cout << nextGenGrid[i][j]<< " ";
    }
      cout << endl;
  }
}

void myGrid::initializeCurrentGrid()
{
  // The following for loop populates the positions that don't hold an 'X'
  // with a '-' to represent an unoccupied cell.

  cout << "ROWS: " << this->rows << endl;
  cout << "COLS: " << this->columns << endl;

   for(int i = 0; i < this->rows; ++i)
   {
     for(int j = 0; j < this->columns; ++j)
      {
        cout << " diag: a[" << i << "][" << j << "]: ";
        currentGrid[i][j] = '-';
        cout << "diag: " << currentGrid[i][j] << endl;
      }
    }
}
void myGrid::clearExtendedCurrentGrid()
{
   //cout << "diag: clearExtendedCurrentGrid, MirrorMode" << endl;
   for(int i = 0; i < this->extendedRows; ++i)
   {
     for(int j = 0; j < this->extendedColumns; ++j)
      {
        //cout << " diag: a[" << i << "][" << j << "]: ";
        extendedCurrentGrid[i][j] = '-';
        //cout << "diag: " << extendedCurrentGrid[i][j] << endl;
      }
    }
    //cout << "diag: exiting clearExtendedCurrentGrid, MirrorMode" << endl;

}
