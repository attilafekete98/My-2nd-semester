/*
This small little program bounces a "ball" on four walls, without the use of if statements.
I implemented and "improved" (just some visually fancy stuff to make it prettier) some other codes in this work.
Made by Attila Fekete at the University of Debrecen in 2018
*/

#include <iostream>
#include <unistd.h> //to use "usleep"
#include <stdlib.h> //to use the "clear" command of the terminal
#include <math.h>   //to use the "pow" function

using namespace std;

int main(){
    int width = 64 , height = 32;   //the resolution of the box
    int x = 10, y = 10;   //current coordinates of the ball
    int x1 = x, y1 = y;

    for (int i = 1; i < 2; i=i+0){  //endless cycle

        usleep(50000);  //change speed here
        system("clear");

        //move the ball
        x += pow(-1, (x1-1)/(width-3));
        y += pow(-1, (y1-1)/(height-3));
        x1++;
        y1++;

        //upper wall
        for(int i = 0; i < width; i++){ //simply draws a line from 0 to the desired width
            cout <<"#";
        }
        cout << "\n";

        //wall above the ball
        for(int i = 0; i < y-1; i++){
            cout << "#";
            for(int j = 0; j < width-2; j++){   //draw the whitespaces just right before the desired width
                cout << " ";
            }
            cout << "#" << "\n";
        }

        //line of the ball
        cout << " ";    //shows the current x position of the ball visually (whitespace in the left wall)
        for(int i = 0; i < x-1; i++){   //whitespaces left to the ball
            cout << " ";
        }
        cout << "@"; //the ball
        for(int i = x+1; i < width-1; i++){ //whitespaces right to the ball
            cout << " ";
        }
        cout << "#" << "\n"; //wall + line break

        //wall below the wall (nearly the same logic as with the wall above the ball)
        for(int i = y; i < height-2; i++){
            cout << "#";
            for(int j = 0; j < width-2; j++){
                cout << " ";
            }
            cout << "#" << "\n";
        }

        //bottom wall
        for(int i = 0; i < x-1; i++){   //wall left to the ball
            cout << "#";
        }
        cout << " ";    //shows the current y position of the ball visually (whitespace in the left wall)
        for(int i = x; i < width; i++){
            cout << "#";
        }

        cout << "\n\n" << "Coordinates:" << "\nx:" << x << " y:" << y << endl; //writes the current coordinates

    }
    return 0;
}
