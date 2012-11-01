# -*- coding: utf-8 -*-
"""
Created on Sun Apr 22 17:34:07 2012

@author: chris
"""

import numpy as np
from numpy import nonzero, zeros, shape

# Strategien
S = list(["Vietnam", "Korea", "China", "Indonesien", "Thailand"])
# Auszahlungsmatrix
A = np.array([[0,18000,20000],[6500,8500,10000],[5000,10000,15000],[7000,8000,11000],[6500,6500,6500]])
# erwartete Wahrscheinlichkeiten
W = np.array([[0.1,0.8,0.1],[0.2,0.3,0.5],[0.3,0.4,0.3],[0.2,0.1,0.7],[0.4,0.4,0.2]])
# Lambda
L = 0.4
# Risikoneigung q
q = -0.75

def Maximax(strategien, auszahlungsmatrix):
    m,n = shape(auszahlungsmatrix)      # Zeilen & Spalten der Matrix feststellen
    Mmax = zeros((m,1))
    i = 0
    for row in auszahlungsmatrix:
        Mmax[i] = max(row)              # Maximum jeder Strategie feststellen
        i = i+1
    max_Mmax = max(Mmax)                # Maximum der Maxima
    max_Mmax = nonzero(Mmax>=max_Mmax)  # Index des Maximax-Ergebnisses feststellen
    print "Bei der Maximax-Strategie ist die Wahl:",strategien[max_Mmax[0]]

def Maximin(strategien, auszahlungsmatrix):
    m,n = shape(auszahlungsmatrix)
    Mmin = zeros((m,1))
    i = 0
    for row in auszahlungsmatrix:
        Mmin[i] = min(row)              # Minimum jeder Strategie feststellen
        i = i+1
    max_Mmin = max(Mmin)                # Maximum der Minima feststellen
    max_Mmin = nonzero(Mmin>=max_Mmin)
    print "Bei der Maximin-Strategie ist die Wahl:",strategien[max_Mmin[0]]

def Laplace(strategien, auszahlungsmatrix):
    m,n = shape(auszahlungsmatrix)
    Lap = zeros((m,1))
    i = 0
    for row in auszahlungsmatrix:
        Lap[i] = sum(row) / n
        i = i+1
    max_Lap = max(Lap)
    max_Lap = nonzero(Lap>=max_Lap)
    print "Bei der Laplace-Strategie ist die Wahl:",strategien[max_Lap[0]]

def Hurwicz(strategien, auszahlungsmatrix, Lambda):
    m,n = shape(auszahlungsmatrix)
    Hur = zeros((m,1))
    i = 0
    for row in auszahlungsmatrix:
        Hur[i] = Lambda * max(row) + (1-Lambda) * min(row)
        i = i+1
    max_Hur = max(Hur)
    max_Hur = nonzero(Hur>=max_Hur)
    print "Bei der Hurwicz-Strategie ist die Wahl:",strategien[max_Hur[0]]

def SavageNiehans(strategien, auszahlungsmatrix):
    m,n = shape(auszahlungsmatrix)
    bedauernsmatrix = zeros((m,n))            # leere Bedauernsmatrix initialisieren
    SN = zeros((m,1))
    column_max = zeros((1,n))
    i = 0
    for i in range(n):
        column_max[0,i] = max(auszahlungsmatrix[:,i])
    bedauernsmatrix = column_max - auszahlungsmatrix
    i = 0
    for row in bedauernsmatrix:
        SN[i] = max(row)
        i = i+1
    min_SN = min(SN)
    min_SN = nonzero(SN<=min_SN)
    print "Bei der Savage-Niehans-Strategie ist die Wahl:", strategien[min_SN[0]]
        
def Bayes(strategien, auszahlungsmatrix, wahrscheinlichkeitsmatrix):
    m,n = shape(auszahlungsmatrix)
    erwartungsmatrix = auszahlungsmatrix * wahrscheinlichkeitsmatrix
    Bay = zeros((m,1))
    i = 0
    for row in erwartungsmatrix:
        Bay[i] = sum(row)
        i = i+1
    max_Bay = max(Bay)
    max_Bay = nonzero(Bay>=max_Bay)
    print "Bei der Bayes-Strategie ist die Wahl:", strategien[max_Bay[0]]

def uSigma(strategien, auszahlungsmatrix, wahrscheinlichkeitsmatrix, q):
    m,n = shape(auszahlungsmatrix)
    erwartungsmatrix = auszahlungsmatrix * wahrscheinlichkeitsmatrix
    usi = zeros((m,1))
    Var = zeros((m,n))
    i = 0
    j = 0
    for i in range(m): # Varianz mit Wahrscheinlichkeiten gewichten
        for j in range(n): # Varianz jeder Alternative berechnen
            Var[i,j] = (auszahlungsmatrix[i,j] - (sum(erwartungsmatrix[i,:])))**2
            j = j+1
        Var[i] = Var[i] * wahrscheinlichkeitsmatrix[i]
        i = i+1
    print(Var)
    i = 0
    for i in range(m): # Berechnen des u-Sigma
        usi[i] = sum(erwartungsmatrix[i]) + q * np.sqrt(sum(Var[i]))
        i + 1
    print(usi)
    max_usi = max(usi)
    max_usi = nonzero(usi>=max_usi)
    print "Bei der u-Sigma-Strategie ist die Wahl:", strategien[max_usi[0]]
    
def Bernoulli(strategien, auszahlungsmatrix, wahrscheinlichkeitsmatrix):
    m,n = shape(auszahlungsmatrix)
    auszahlungsmatrix = auszahlungsmatrix + 10
    nutzenmatrix = Nutzenfunktion(auszahlungsmatrix)
    erwartungsmatrix = nutzenmatrix * wahrscheinlichkeitsmatrix
    Ber = zeros((m,1))
    i = 0
    for row in erwartungsmatrix:
        Ber[i] = sum(row)
        i = i+1
    max_Ber = max(Ber)
    max_Ber = nonzero(Ber>=max_Ber)
    print "Bei der Bernoulli-Strategie ist die Wahl:",strategien[max_Ber[0]]

def Nutzenfunktion(auszahlung):
    nutzen = np.log(auszahlung/10)
    return nutzen

Maximax(S,A)            # Beim Aufrufen werden die Parameter übergeben:
Maximin(S,A)            # S = Namen der Strategien
Hurwicz(S,A,L)          # A = Auszahlungsmatrix
Laplace(S,A)            # L = Lambda
SavageNiehans(S,A)      # W = Wahrscheinlichkeitsmatrix
Bayes(S,A,W)            # q = Risikoneigung
uSigma(S,A,W,q)
Bernoulli(S,A,W)