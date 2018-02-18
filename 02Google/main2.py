#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math

def kiir(tomb,db):
    for i in range(0,db):
        print "Page rank", tomb[i]

def tavolsag(PR,PRv,n):
    osszeg = 0
    for i in range(0,n):
        osszeg += (PRv[i] - PR[i]) * (PRv[i] - PR[i])

    return math.sqrt(osszeg)

#program starts here
L = [[0.0, 0.0, 1.0 / 3.0, 0.0],
    [1.0, 1.0 / 2.0, 1.0 / 3.0, 1.0],
    [0.0, 1.0 / 2.0, 0.0, 0.0],
    [0.0, 0.0, 1.0 / 3.0, 0.0]]

PR = [0.0, 0.0, 0.0, 0.0]
PRv = [1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0, 1.0 / 4.0]

while True:
    for i in range(0,4):
        PR[i] = 0.0
        for j in range(0,4):
            PR[i] += (L[i][j] * PRv[j])

    if (tavolsag(PR, PRv, 4) < 0.0000000001):
        break

    for i in range(0,4):
        PRv[i] = PR[i]

kiir(PR, 4)
