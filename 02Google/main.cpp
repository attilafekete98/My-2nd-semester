#include <iostream>

using namespace std;

int main(){

  int intLength = 1 ;
  int bitSzam = 1;

  while(bitSzam = bitSzam << 1){
    intLength++;
  }

  cout << "A szóhossz: " << intLength << " bites\n";

  return 0;
}
