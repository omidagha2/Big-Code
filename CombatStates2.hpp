#pragma once

class State{
public:
  virtual void entranceAction()=0;
  virtual void toggleAction()=0;
  virtual void exitAction()=0;
  virtual ~State(){};
};

namespace cs2{
  class PlayerTurn: public State{
    void entranceAction() override{
      //let player make choices until they run out of tokens or attack.
    }
    void toggleAction() override{

    }
    void exitAction() override{
      // change state, idk. extra show stuff maybe i guess.
    }
  };
  class EnemyTurn: public State{

  };
  
  
}
