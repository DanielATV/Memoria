#include "Initialize.h"
#include "Ant.h"
#include "ACO.h"
#include <ctime>
#include <sys/time.h>
#include <time.h>

char* InstanciaFile;
float Opt;
unsigned int N,M,Seed,TotalAnts,TotalAntsp1;
vector < float > Profits;
vector < float > Aux;
vector < int > BestFactible;
double BestFitFactible;
vector <vector < float > > Weights;
vector <vector < float > > Mat_A;
vector <vector < float > > Pheromone;
vector < float > AntiPheromone;
vector < float > HeuristicProfit;
vector < float > HeuristicWeight;
int func_eval;
int traduccion;
float alpha,beta,ph_max,ph_min,rho;
float alpha_p1,beta_p1,rho_p1,taumax_p1;
vector < int > BestSolutionFound;
float Budget;
double BestFitnessFound;
vector < double > Output;
bool validado;
int n_tests;
vector < float > b_i;
int TotalEvaluations;
float penal;
float ph_ini,gap_avg;
int eval;
time_t Inicio, Fin_opt, Fin_ejec;
vector < int > AFtime;
vector < int > Ftime;
float tiempoAF;
float tiempoF;
int cantidadAF;
int cantidadF;
int Method;
int Stats;

using namespace std;

int main(int argc, char** argv) {
	Capture_Params(argc,argv);
	Read_Instance();
	srand48(Seed);
	DefineInitial();
	//PrintInstancia();
	
	validado = false;
	ACO();

	//cout << BestFitnessFound << " " << tiempoAF << " " << tiempoF << " " << tiempoAF/cantidadAF << " " << tiempoF/cantidadF << " " << validado << endl;
	//cout << 100*(Opt - BestFitnessFound)/Opt << endl;
/*	  cout << "FINAL" << endl;

        cout << endl;
      }*/

	//For statistics:
	//if(Stats && gap_avg != 0)  cout << BestFitnessFound << " " << 100*(Opt - BestFitnessFound)/Opt << " " << gap_avg << endl;
	//else cout << BestFitnessFound << " " << 100*(Opt - BestFitnessFound)/Opt << endl;

	// For tuning:
	cout << 100*(Opt - BestFitnessFound)/Opt << endl;


	//Convergence analysis:
	/*
		unsigned int p;
		Output.push_back(BestFitnessFound);
		ofstream out;
		std::vector<char*> v;
		char* chars_array = strtok(argv[1], "/");
		while(chars_array)
		{
				v.push_back(chars_array);
				chars_array = strtok(NULL, "/");
		}
		int indice = v.size();
		strcat(argv[2],v[indice-1]);
		out.open(argv[2],ofstream::app);
		indice = 0;
		for(p = 0; p < Output.size(); p++){
				out <<indice << " " << Output[p] << endl;
				indice += iteraciones/100;
		}
		out << "###" << endl;
		out.close();

*/
	return 0;
}
