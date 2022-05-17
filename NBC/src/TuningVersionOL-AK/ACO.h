/*
 * ACO.h
 *
 *  Created on: 22-12-2014
 *      Author: nicolas
 */

#ifndef ACO_H_
#define ACO_H_
#include <math.h>

using namespace std;

extern float alpha_p1,beta_p1,rho_p1,taumax_p1;
extern vector < int > BestSolutionFound;
extern float Budget;
extern float penal;
extern vector < int > BestFactible;
extern double BestFitFactible;
void ChangePheromone();
extern bool validado;
void InitVector();
void CompareSolutions();
int decide (vector <float> CapRem, bool Step);
void CheckAllowedNodes(vector <float> CRem);
void UpdatePheromone(int fase, vector <int> Sol, float quality);
float InsertObjectToCandSolution(int obj,vector <float> &CapRem);
void ACO();
void RhoPheromone(int fase);
bool ValidateSolution();
extern vector < float > Profits;
extern vector < float > Aux;
extern vector <vector < float > > Weights;
extern vector <vector < float > > Pheromone;
extern vector < int > BestSolutionFound;
extern vector < int > AFtime;
extern vector < int > Ftime;
extern float gap_avg;
extern float tiempoAF;
extern float tiempoF;
extern int cantidadAF;
extern int cantidadF;
extern int Method;
extern vector < double > Output;
extern time_t Inicio, Fin_opt, Fin_ejec;
void CleanVector();
#endif /* ACO_H_ */
