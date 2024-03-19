//this sucks don't adopt anything from it.

#include <iostream>
#include <string>
//#include "Array.h"


class Monster       // Declares monster class
{
public:
     int m_x;
     int m_y;
     int m_hitpoints;
};

class Player                //Declares player class
{
public:
Player() {p_x=9;p_y=9;}  //constructor for player class
int p_x;
int p_y;
};


const int blankspace = 0;  // constants for player, monster, and blankspace display
const int  player = 2;
const int monster = 1;

const int ROW = 10;  // array to hold level
const int COL = 10;

         int level[ROW][COL] = {{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0}};
  
using namespace std; // declares usage of standard namespace


    char in;             // declares variable 'in' used for player movement
std::string name;    // declares "name" as a string
int response;        // declares response variable
int oldX,oldY;       // declares variables for storing old x and y co-ordinates
    Player p;            // declares player Variable
   
    bool addmonster()
{
        int r;
for(int i=0;i<10;i++) {
for(int j=0;j<10;j++) {
if(level[i][j]==player)        // function for adding monsters
continue;
else {
r=rand()%10;
if(r==1) {
level[i][j]=monster;
}
}
}
}
return true;

}


   void game()
   {
   
    oldX=p.p_x;
oldY=p.p_y;
cin >> in;
if(in=='w') {     // Upward movement for player
p.p_y--;
level[p.p_y][p.p_x]=2;
level[oldY][oldX]=0;
}

if (in=='a') {   //Downward movement for player
p.p_x--;
level[p.p_y][p.p_x]=2;
level[oldY][oldX]=0;
}

if (in=='s') {  // Left movement for player
p.p_y++;
level[p.p_y][p.p_x]=2;
level[oldY][oldX]=0;
}

if (in=='d') {  // Right movement for player
p.p_x++;
level[p.p_y][p.p_x]=2;
level[oldY][oldX]=0;
}



cout << string(50, '\n');
//cout << "\n";

addmonster();



for (int row=0;row<ROW;row++) {               //Displays the level map on the screen and refreshes it with each input
for (int col=0;col<COL;col++) {
if (level[row][col]==0) cout << " . ";
if (level[row][col]==1) cout << " M ";
if (level[row][col]==2) cout << " P ";
}


cout << "\n";
}

   }





    int main()
{
cout << "           ...............WELCOME TO MONSTER HUNTER...............   " << endl;
cout << "\n";
cout << "Press 1 to hunt some monsters! Or press 2 to run to the exit! " << endl;    // Asks player to start game or exit game

cin >> response;
    if (response == 1) cout << "Welcome Monster Hunter please enter your name!"  <<endl; // Prompts player for their name
    if (response == 2) exit (0);

cin >> name;
    cout << "Right then "  << name << " it's time to hunt some monsters! " << endl;  // Displays player name and indicates
                                                                                     // begining of game
cout << "Press W to move up" << endl;
cout << "Press S to move down" << endl;
cout << "Press A to move left" << endl;
cout << "Press D to move right" << endl;
cout << "\n";
cout << "To begin move Left with A , or Up with W " << endl;
cout << "\n";

int counter = 0;


do
{
 game();
 counter++;
 cout << "\n";
 cout << "You have " << 20 - counter << " tries left" << endl;
}while(counter < 20);
  
   
return 0;
}