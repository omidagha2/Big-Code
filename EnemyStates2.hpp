#pragma once

class EnemyState{
public:
  virtual void entranceAction()=0;
  virtual void toggleAction()=0;
  virtual void exitAction()=0;
  virtual ~EnemyState(){};
};

class LowHp: public EnemyState{
  
};  