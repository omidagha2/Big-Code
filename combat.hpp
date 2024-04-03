#include "items.hpp"

//enemy combat fsm 1:
//this implementation allows each enemy to be in a certain enum state. in each rendition of the machine, the enemy 
//checks what state it's in, then performs accordingly.
namespace combat1{
  class Entity{

  };
  class EnemyModel1: public Entity{
    
    enum class State{
      Entry,


      Low_HP, //checks if it has consumables that restore hp. if so, creates a list of the consumables and uses the one with the highest usepercentage. 
              //the enemy doesn't go to this mode if it's only missing a few points of hp. so it's safe to say it won't be considering using any high percent low recovering items.
      
      Dangerously_Low_HP, //here they really want to use a hp recovering item. here, the amount restored also comes into play (the amount restored beyond what is effective doesn't count, like if it exeeds the enemy's hp limit)
                          //they sort it based on what can bring him up to / closest to 90 percent of their hp. if there are multiple best answers, uses the highest usepercent.

      Low_STA, //the enemy just uses what restores it's hp closest
      Fine, //enemy goes to this state if it doesn't enter any other states.

      //at the end of the states above, a use item has been selected in the enemy's hand. here the enemy uses it, and if there are 
      //two or more tokens left, the enemy repeats the cycle. they need one token to attack, so they won't be using that.

      Use_Item,
      Attack //enemy choses the best weapon to attack with.
    };
  
    public:
    
  };

  class EnemyModel2: public Entity{
    enum class State{
      //simply checks if it can use an item to a good efficiency, if so, it does.
    };

  };
  
}

//enemy combat fsm 2:
//this implementation is based on a version I found on the internet. The idea is that every state is a singleton
//instead of an enum. every state has a set of actions it calls upon an object entering that state, a set of actions 
//it calls upon an object exiting the state, and a special toggle action, which makes it possible to incorporate
//other types of fsm systems, like the one above. 
namespace combat2{
  #include "EnemyStates2.hpp"
}

//enemy combat fsm 3:
//this implementation uses a third party library. There are many things implemented, including events, 
//
namespace combat3{

}

//in this implementation, each enemy has multiple parameters that can be in different states. 
namespace combat4{

}