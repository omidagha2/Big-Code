#include <iostream>
#include "objects.hpp"
using namespace std;


int main(){
    item a("a gun", 10, 10, 1);
    vector<item> v;
    v.push_back(a);
    human n("michael", 12, "male", v);
    cout << n.getname();
//assume combat.


}

