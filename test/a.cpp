#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int main(){
  string s = "a";
  cout << (s.find("a") == string::npos);
}