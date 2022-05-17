#include "Initialize.h"
#include "Ant.h"
#include "ACO.h"

using namespace std;
vector <int> auxiliar;
vector <int> allowed;
vector <int> visited;
bool factible;

void ACO(){
		bool print = false;
		vector <Ant> Hormigas;
		vector <float> CapRem;
	  	float mejor,lowerq,gap_it;
		//float gap_best;
	  	float QualityNew = 0;
	  	tiempoAF = 0;
	  	tiempoF = 0;
	  	cantidadAF = 0;
	  	cantidadF = 0;
	  	unsigned int i,depositant;
	  	int curr_eval = 0;
	  	//bool foundsolution = false;
		//unsigned int delta = TotalEvaluations/100;
		bool stop = true;
		bool end = true;
		bool FirstStep = true;
	  	InitVector();

	  	gap_avg = gap_it = depositant= lowerq = mejor = 0;
	  	CapRem = b_i;
	  	Ant ant;
	  	ant.initAnt();
	  	//vector de hormigas
	  	for(i = 0; i < TotalAnts; i++){
	  		ant.setId(i);
	  		Hormigas.push_back(ant);
	  	}


	  	if(Budget == 0){
	  		FirstStep = false;
	  		if(print) cout << "no hay first step" << endl;
	  		BestFitnessFound = 0;
	  		Method = 0;
	  	}
	  	else{
	  		if(print) cout << "hay first step" << endl;

	  	}
		
		int EvaluationsAph = TotalEvaluations*Budget;

		if(print) cout << "usaremos -->" << EvaluationsAph << "para el First Step" << endl;
		//fase ANTIFEROMONA
	  	while(curr_eval < TotalEvaluations && end){

	  		Inicio = time(NULL);
	  		if(print){
	  			if(FirstStep) cout << "Current State: First Step" << endl;
	  			else cout << "Current State: Second Step" << endl;
	  		}
		    for(i = 0; (i < TotalAnts) && end ; i++){
					stop = true;

					QualityNew += InsertObjectToCandSolution(int_rand(0,(N-1)),CapRem);
					CheckAllowedNodes(CapRem);

					//CONSTRUCCION DE LAS SOLUCIONES
					while(stop){

						if(FirstStep) QualityNew += InsertObjectToCandSolution(decide(CapRem,true),CapRem);
						else QualityNew += InsertObjectToCandSolution(decide(CapRem,false),CapRem);
						CheckAllowedNodes(CapRem);
						if(allowed.size() == 0)stop=false;
					}

					if(print){
						cout << "curr_eval ->" << curr_eval << " - Ant#" << i << " - Q:" << QualityNew << endl;
					}
					if(i == 0){
					   mejor = QualityNew;
					   depositant = i;
					   lowerq = QualityNew;
					}
					else{

						if(lowerq > QualityNew){
							lowerq = QualityNew;
							if(FirstStep) depositant = i;
						}


						if(mejor < QualityNew){
								mejor = QualityNew;
								if(FirstStep == false) depositant = i;

						}
					}
					if(QualityNew != Opt){
						if(FirstStep){//minimizamos el BestFitnessFound
							if(QualityNew < BestFitnessFound){
								BestSolutionFound = auxiliar;
								BestFitnessFound = QualityNew;
						   }

						}
						else{
							if(QualityNew > BestFitnessFound){
								BestSolutionFound = auxiliar;
								BestFitnessFound = QualityNew;
							   }
						}
					}
					else{
						BestSolutionFound = auxiliar;
						//foundsolution = true;
						end = false;
						BestFitnessFound = QualityNew;
					}

					//if(curr_eval < TotalEvaluations) end = false;

					Hormigas[i].setEvaluacion(QualityNew);
					Hormigas[i].setMemoria(auxiliar);

				    QualityNew = 0;
				    CleanVector(); //auxiliar y visited no lleva ningun objeto
				    CapRem = b_i; // empezamos con toda la capacidad en las M dimensiones
				    stop = true;
				    curr_eval++;
		    }


		    if(print){
		    	if(FirstStep) cout << "Best Ant Was: #" << depositant << " - Q:" << lowerq << endl;
		    	else cout << "Best Ant Was: #" << depositant << " - Q:" << mejor << endl;
		    }


		   if(FirstStep){
			   RhoPheromone(0);
			   UpdatePheromone(0,Hormigas[depositant].getMem(),lowerq);
		   }
		   else {
			   RhoPheromone(1);
			   UpdatePheromone(1,Hormigas[depositant].getMem(),mejor);
		   }



		   if((Stats == 1) && FirstStep){
			   gap_it = (mejor - lowerq)/(mejor);
			   gap_avg += gap_it;
			   //gap_best = (Opt - lowerq)/Opt;
			   if(print){
				   cout << "Gap for this iteration is: " << gap_it << " between B_i:" << mejor << " and L_i:" << lowerq << endl;
				   //cout << "and: " << gap_best << " with BK:" << Opt << endl;
			   }
		   }
		   /*
		   if(curr_eval == delta){
		  	Output.push_back(BestFitnessFound);
			delta += TotalEvaluations/100;
		   }
		   */

		   if(print)getchar();
		   if((curr_eval == EvaluationsAph) && FirstStep){
			   ChangePheromone();
			   Method = 0; //Al cambiar de fase, el decide siempre es en 0.
			   FirstStep = false;
			   if(print) cout << "First into Second Step" << endl;
			   if(Stats) gap_avg = gap_avg/EvaluationsAph;
		   }

		   /*
		   Fin_ejec = time(NULL);

		   if(curr_eval <= IteracionesAph){
			   tiempoAF += float(Fin_ejec - Inicio);
			   cantidadAF++;
		   }
		   else{
			   tiempoF += float(Fin_ejec - Inicio);
			   cantidadF++;
		   }*/
	 	}


	  	//cout << gap_avg << endl;

}


float InsertObjectToCandSolution(int obj,vector <float> &CapRem){
	unsigned int j;
	visited[obj] = 0;
	auxiliar[obj] = 1;
	//UPDATE OF CAP REM
	for(j = 0; j < Weights.size(); j++){
		CapRem[j] -= Weights[j][obj];
	}

	return Profits[obj];

}

//Complemento
void ChangePheromone(){
	unsigned int i,j;


	for(i = 0; i < (N-1); i++){
		  for(j = (i+1); j < N; j++){
			  if(i != j){
				  	Pheromone[i][j] = taumax_p1 - Pheromone[i][j];
				  	Pheromone[j][i] = Pheromone[i][j];
				  	if(Pheromone[i][j] < ph_min){
				  		Pheromone[i][j] = ph_min;
				  		Pheromone[j][i] = ph_min;
				  	}
				  	if(Pheromone[i][j] > ph_max){
				  		Pheromone[i][j] = ph_max;
				  		Pheromone[j][i] = ph_max;
				  	}
			  }
		}
	}


}

void RhoPheromone(int fase){
	unsigned int i,j;
	for(i = 0; i < (N-1); i++){
		  for(j = (i+1); j < N; j++){
			  if(i != j){

					if(fase == 0){
						Pheromone[i][j] = Pheromone[i][j]*(1 - rho_p1);
						Pheromone[j][i] = Pheromone[i][j];
					}
					else{
						Pheromone[i][j] = Pheromone[i][j]*(1 - rho);
						Pheromone[j][i] = Pheromone[i][j];
					}
					if(Pheromone[i][j] < ph_min){
						Pheromone[i][j] = ph_min;
						Pheromone[j][i] = ph_min;
					}
			  }
		  }
	}
}

int decide (vector <float> CapRem, bool Step){
  	unsigned int i,j;
	float rnd;
	vector < float > Matriz;
	float num1,num2,mult;
	float min_heu,max_heu;
	float div = 0;
	double suma_total = 0;
	vector <float> remanenteobj;
    float rempromedio = 0;

    switch(Method){
		case 0:
			//SOL or AK, use the same construction process
			 for(i = 0; i < allowed.size(); i++){
				 //Por cada objeto permitido, suma en DIV de peso/cap_remanente en todas las dimensiones
				 for(j = 0; j < CapRem.size(); j++){
						div = (float)(Weights[j][allowed[i]]/CapRem[j]);
						rempromedio += div;
				 }

				 mult = (float)(Profits[allowed[i]]/rempromedio);
				 remanenteobj.push_back(mult);
				 rempromedio = 0;
				}
			break;
		case 1:
			//HOL

			for(i = 0; i < allowed.size(); i++){
				 for(j = 0; j < CapRem.size(); j++){
						div = (float)(CapRem[j] - Weights[j][allowed[i]]);
						rempromedio += div;
				 }
				 mult = (float)(Profits[allowed[i]]/rempromedio);
				 remanenteobj.push_back(mult);
				 rempromedio = 0;
			}
			break;
		case 2:
			//WOL
			for(i = 0; i < allowed.size(); i++){
				 for(j = 0; j < CapRem.size(); j++){
						div = (float)(Weights[j][allowed[i]]/CapRem[j]);
						rempromedio += div;
				 }

				 mult = (float)(Profits[allowed[i]]/rempromedio);
				 if(i == 0){
					 min_heu = mult;
					 max_heu = mult;
				 }
				 else{
					 if(min_heu > mult) min_heu = mult;
					 if(max_heu < mult) max_heu = mult;
				 }
				 remanenteobj.push_back(mult);
				 rempromedio = 0;
				}
			for(i = 0; i < allowed.size(); i++){
				remanenteobj[i] = max_heu + min_heu - remanenteobj[i];
			}
			break;
		default:
			break;
    }

	//Roulette
	suma_total = 0;
	float suma_obj_allowed = 0;
	for(i = 0; i < allowed.size(); i++){
	   for(j = 0; j < visited.size(); j++){
		if(visited[j] == 0)suma_obj_allowed += Pheromone[j][allowed[i]];
	   }

	   if(Step){
		   num1 = powf(suma_obj_allowed,alpha_p1);
		   num2 = powf(remanenteobj[i],beta_p1);
	   }
	   else{
		   num1 = powf(suma_obj_allowed,alpha);
		   num2 = powf(remanenteobj[i],beta);
	   }
	   mult = num1*num2;
	   Matriz.push_back(mult);
	   suma_total += mult;
	   suma_obj_allowed = 0;
	}
	rnd = float_rand(0.00,1.00);
	bool flag = true;
	int index_mellevo=0;
	//a_ij de cada objeto
	float acumulado = 0; 
	for(i = 0; (i < Matriz.size())&&(flag); i++){
	    mult = Matriz[i]/suma_total;
	    acumulado += mult;
	    if(rnd < acumulado){
	      index_mellevo = i;
	      flag = false;
	    }
	    Matriz[i]= acumulado;
	  }
	return allowed[index_mellevo];
}	


void UpdatePheromone(int fase, vector <int> Sol, float quality){
	unsigned int i,j;
	float howmuch =  0;
	float upperph = 0;
	//maximizo
	if(fase == 1){
		howmuch = (float)(1/(1+BestFitnessFound - quality));
		upperph = ph_max;
	}
	else{
		howmuch = (float)(1/(1+quality - BestFitnessFound)); //minimizo
		upperph = taumax_p1;
	}

	for(i = 0; i < (N-1); i++){
		  if(Sol[i] == 1){
		    for(j = (i+1); j < N; j++){
		    	if((Sol[j] == 1) && (i != j)){
		    		Pheromone[i][j] += howmuch;
		    		Pheromone[j][i] = Pheromone[i][j];
		    		if(Pheromone[i][j] > upperph){
		    			Pheromone[i][j] = upperph;
		    			Pheromone[j][i] = upperph;
		    		}

		    	}
		    }
		  }
	  }
}


void CleanVector(){
	unsigned int i;
	for(i = 0; i < N; i++){
		auxiliar[i] = 0;
		visited[i] = 1;
	}
}

void InitVector(){
	unsigned int i;
	for(i = 0; i < N; i++){
		auxiliar.push_back(0);
		visited.push_back(1);
	}
}

bool ValidateSolution(){

//		float profit = 0;
//		float howmuch = 0;
		float auxmuch = 0;
		unsigned int i,j;
//		for(i = 0; i < N; i++){
//			profit += Profits[i]*BestSolutionFound[i];
//		}
		for(i = 0; i < Weights.size(); i++){
			for(j = 0; j < Weights[i].size(); j++){
				//auxmuch me dice el peso de los objetos que llevo en auxiliar
				auxmuch += Weights[i][j]*BestSolutionFound[j];
			}
			//si es que auxmuch es más que b_i: ojo con los indices de b_i, puede estar raro
			//penal es parámetro, que tanto penalizamos
			if(auxmuch > b_i[i]){
				return false;
			}
			auxmuch = 0;
		}

		return true;
}

void CheckAllowedNodes(vector <float> CRem){
	unsigned int i,j;
	allowed.clear();
	bool flag = true;
	for(i = 0; i < N; i++){
	  //El objeto i en visited es 1 cuando no lo he visitado - es disponible
	   if(visited[i]){
		//Ve que la capacidad remanente, en cada dimension, sea mayor que el peso del objeto i
           	for(j = 0; (j < M) && flag; j++){
        		if(CRem[j] < Weights[j][i]){
        			flag = false;
        		}
           	}
		// si cabe, es allowed
			if(flag){
					allowed.push_back(i);
			}
			flag = true;
        }
	}
}
