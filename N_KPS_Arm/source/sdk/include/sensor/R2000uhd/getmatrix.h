//
// Created by dl on 9/20/18.
//

#ifndef N_KUNHOU_ARM_GETMATRIX_H
#define N_KUNHOU_ARM_GETMATRIX_H

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<iostream>
#include <vector>

#define debug false

#define MAX 100

void input(int *m,int *n,double *x,double a[2][MAX]); 
void makematrix(double a[2][MAX],double c1[MAX][MAX],int n,int m); 
void convert(double c1[MAX][MAX],double c2[MAX][MAX],int n,int m); 
void multiply(double c[MAX][MAX],double c2[MAX][MAX],double c1[MAX][MAX],int n,int m,int t); 
void pmatrix(double a[MAX][MAX],int n,int m); 
std::pair<double, double> output(double x[MAX],int n, double des);  
void solvematrix(double c[MAX][MAX],double b[MAX][MAX],double x[MAX],int n); 

void solve(double all[MAX][MAX],int n);
void swap(double a[MAX],double b[MAX],int n);
void answer(double a[MAX][MAX],double x[MAX],int n);
#endif //N_KUNHOU_ARM_GETMATRIX_H
