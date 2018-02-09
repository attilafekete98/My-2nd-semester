#!/usr/bin/env python
# -*- coding: utf-8 -*-

#This small little program bounces a "ball" on four walls, without the use of if statements.
#I implemented and "improved" (just some visually fancy stuff to make it prettier) some other codes in this work.
#Made by Attila Fekete at the University of Debrecen in 2018

from time import sleep
import os

width, height = 32, 24 #the resolution of the box
x, y = 10, 10 #current coordinates of the ball
x1, y1 = x, y

while True:
    sleep(0.08)
    os.system("clear");

    #move the ball
    x += pow(-1, (x1-1)/(width-3))
    y += pow(-1, (y1-1)/(height-3))
    x1 = x1+1
    y1 = y1+1

    #upper wall
    for i in range(0,width):    #simply draws a line from 0 to the desired width
        print("#"),
    print("")

    #wall above the ball
    for i in range(0,y-1):  #draw the whitespaces just right before the desired width
        print("#"),
        for j in range(0,width-2):
            print(" "),
        print("#")

    #line of the ball
    print(" "), #shows the current x position of the ball visually (whitespace in the left wall)
    for i in range(0,x-1):
        print(" "),
    print("@"), #the ball
    for i in range(x+1,width-1):    #shows the current x position of the ball visually (whitespace in the left wall)
        print(" "),
    print("#")  #wall


    #wall below the wall (nearly the same logic as with the wall above the ball)
    for i in range(y,height-2):
        print("#"),
        for j in range(0,width-2):
            print(" "),
        print("#")


    #bottom wall
    for i in range(0,x):
        print("#"),
    print(" "),
    for i in range(x+1,width):
        print("#"),

    print"\nCoordinates\nx:" , x , "y:" , y

    
