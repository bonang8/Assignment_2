# Assignment_2
Clarisse Bonang
2298162
# Game of Life 

The game of Life was designed in the 1970s by the mathematician J.H. Conway. The game gained popularity after appearing in a Scientific American article, and took <br>  the computing world by storm. The game is a simulation that models the life cycle of bacteria, providing entertainment wrapped up in what some would call <br>  mathematical elegance. (For some history on the game, as well as the rise of computing in general, I highly recommend the book Hackers, by S. Levy.) <br> 

The game itself is played on a two-dimensional grid. Each grid location is either empty or occupied by a single cell (X). A location’s neighbors are any of the <br>  cells in the surrounding eight adjacent locations. <br> 
# Rules of the Game:
The simulation starts with an initial pattern of cells and computes successive generations according to the following rules: <br> 
1. A location that has one or fewer neighbors will be empty in the next generation. If a cell was in that location, it dies of loneliness. (The fate of many a computer scientist...)
2. A location with two neighbors remains stable. If there was a cell, there’s still a cell. If it was empty, it’s still empty.
3. A location with three neighbors will contain a cell in the next generation. If it currently has a cell, the cell lives on. If it’s empty, a new cell is born.
4. A location with four or more neighbors will be empty in the next generation due to overcrowding.
5. The births and deaths that take one generation to the next must all take place simultaneously. When computing a new generation, the births and deaths in that <br>  generation can not affect other births and deaths in that generation. <br> Not adhering to this guideline will really mess up your simulation, so be careful. <br> An easy way to get around this is to have 2 versions of the grid. <br> One is for the current generation, and the other is for computing the next generation (based on the current generation) without side effects. <br>  When you are done computing the next generation you can either copy it into the current generation grid, or just switch a reference. (In the database community, this little hack is called shadow paging.) <br> 
# Changes made for grader:
 Instead of having it loop infinitely, my program is able to detect whether its stable or empty and prompt the user <br> 
 Press ‘x’ to exit instead of enter <br> 
 Capped max generation at 50 for pause mode on file output mode <br> 
 Note: lifeOne.txt, lifeTwo.txt, lifeThree.txt are my sample output files from early runs <br> 
       fileConfig.txt is the file I used to test input <br> 
       please ignore myGrid.h.gch <br> 

# References:
Notes from CPSC 298, Lecture covering reading and writing to a file <br> 
Data Structures book: p.113, 3.1 using arrays <br> 
How to display a 2D array like a grid in c++ <br> 
https://stackoverflow.com/questions/46896779/2d-array-output-x-and-y-axes-on-grid <br> 
2D array from file <br> 
https://stackoverflow.com/questions/36708370/reading-from-txt-file-into-two-dimensional-array-in-c <br> 
 Got sleep function from stack overflow <br> 
http://www.cplusplus.com/reference/thread/this_thread/sleep_for/ <br> 
