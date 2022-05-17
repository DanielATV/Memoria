/*
 * Initialize.h
 *
 *  Created on: 22-12-2014
 *      Author: nicolas
 */

#ifndef INITIALIZE_H_
#define INITIALIZE_H_
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdio.h>
//#include <ncurses.h> //versi^?n linux reemplazar por conio.h
#include <cstdlib>
#include <vector>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <iostream>
using namespace std;
using std::ifstream;

void Capture_Params(int argc, char** argv);
bool Read_Instance();
void PrintInstancia();
void DefineInitial();
int int_rand (int a, int b);
float float_rand (float a, float b);


extern char* InstanciaFile;
extern float Opt;
extern int eval;
extern unsigned int N,M,TotalAnts,TotalAntsp1,Seed;
extern int func_eval;
extern int traduccion;
extern int TotalEvaluations;
extern vector < float > Profits;
extern vector < float > Aux;
extern vector <vector < float > > Weights;
extern float Budget;
extern vector < vector < float > > Pheromone;
extern vector < int > BestSolutionFound;
extern float penal;
extern int n_tests;
extern float alpha,beta,ph_max,ph_min,rho;
extern double BestFitnessFound;
extern vector < float > AntiPheromone;
extern float ph_ini;
extern vector < float > HeuristicProfit;
extern vector < float > HeuristicWeight;
extern vector <vector < float > > Mat_A;
extern vector < float > b_i;
extern float alpha_p1,beta_p1,rho_p1,taumax_p1;
extern int Method, Stats;

#endif /* INITIALIZE_H_ */
