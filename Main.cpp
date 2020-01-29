#include<queue>
#include<iostream>
#include<algorithm>
#include "Main.h"

// Process @3: 2 5 8 7 4
// Process @5: 4
// Process @6: 8 2 10 2 7 5 6


int main(){
  Processor War;
  int temp[5]={2,5,8,7,4};
  Process NOW(temp, 5, 1);
  cout << NOW.pop().id << endl;
  cout << NOW.pop().id << endl;
  cout << NOW.pop().id << endl;
  cout << NOW.pop().id << endl;
  cout << NOW.pop().id << endl;
  cout << NOW.pop().id << endl;
  cout << NOW.pop().id << endl;
  
}
