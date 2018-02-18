#!/usr/bin/env python
# -*- coding: utf-8 -*-

#This small program swaps two variables without a temp variable
#Made by Attila Fekete at the University of Debrecen in 2018

def swap(a,b):
    
    a = a - b
    b = a + b
    a = b - a
    return a,b

#The program stars here

a = input("a = ")
b = input("b = ")

print "a =" , a , " b =" , b , "\nSWAP"
a,b = swap(a,b)
print "a =" , a , " b =" , b
