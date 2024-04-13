#include <iostream>
#include "1m.cpp"

int main()
{
    string name, namee;  int choice;
    char y;
    cout << "enter your name: ";
    getline(cin , name);
    setConsoleColor(1);
    cout << "\nWELLCOME TO ";
    setConsoleColor(2);
    cout << "IUSTZ ";
    setConsoleColor(1);
    cout << "GAME " << name << "\n\n";
    setConsoleColor(15);
    
    Game startGame;
}
    // cout << "1.existed" << "\n2.customize\n" << "(press \"1\" for choosing amoung existed characters and for customizing press \"2\")";
    // cin >> y;
    // characters ch;
    // if (y=='1')
    // {
    //     human* selectedCharacter = ch.choice();
    //     if (selectedCharacter) {
    //         StoryHandler story;
    //         while (true)
    //         {
    //             story.displayStory();
    //         }
            
    //     }
        
    // } else if (y=='2'){
    //     string gender;
    //     cout << "choose a name for your character:\n";
    //     getline(cin ,namee);
    //     cout << "\n1.Male\n2.Female\n";
    //     cin >> gender;
    //     cout << "how strong you like to be?!\n" << "1.noob\n2.normal\n3.pro\n";
    //     cin >> choice;
    //     if (choice==1)
    //     {
    //         human player(namee,10 ,gender ,1 ,20 ,10 ,20);

    //     } else if (choice==2)
    //     {
    //         /* code */
    //     } else
    //     {
    //         /* code */
    //     }
        
        
        

    // } else {
    //     cout << "unvalid choice\n";
    // }
    //}
//     int main() {
//     GameModel model;
//     GameView view;
//     GameController controller;

//     // Game loop
//     while (true) {
//         view.displayGameState(model);
//         controller.handleInput(model);
//         // Update the game state
//     }

//     return 0;
// }

    

   