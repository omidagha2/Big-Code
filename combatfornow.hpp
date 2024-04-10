#include "objects.hpp"




int Player::atkBar(){
  int score = 0;
  int way = 1;
   while(true){
    if (kbhit() && getch() == ' '){
      cout << "yeah boi";
      return score;
    }
    score+=way;
    if (score >= 10 || score <= 0){
      way = -1*way;
    }
    cout << (way < 0 ? "\b \b\b^" : "\b ^");
    // cout << (way < 0 ? "\b \b\b^" : "\b ^ ");
    Sleep(80);
   }
}