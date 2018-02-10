/*
This small program swaps two variables without a temp variable using a void function
Made by Attila Fekete at the University of Debrecen in 2018
*/

#include <iostream>

using namespace std;

void swap(int& a,int& b);

int main(){

    int a,b;
    
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;

    cout << "a = " << a << " b = " << b << "\n SWAP\n";
    swap(a,b);
    cout << "a = " << a << " b = " << b << "\n";

    return 0;

}

void swap(int& a,int& b){

  a = a - b;
  b = a + b;
  a = b - a;

}
