#!/bin/bash

bench=$1
outfile=$2
seed=$3

shift 3
TotalEvaluations=1000
alpha=1
beta=5
ph_max=6
ph_min=0.01
rho=0.01
TotalAnts=30

Budget=0
alpha_p1=0
beta_p1=0
rho_p1=0
taumax_p1=0
Method=0
Stats=0

while [ $# != 0 ]; do
    flag="$1"
    case "$flag" in
        -TotalAnts) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              TotalAnts=$arg
            fi
            ;;
        -alpha) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              alpha=$arg
            fi
            ;;
        -beta) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              beta=$arg
            fi
	    ;;
        -ph_max) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              ph_max=$arg
            fi
	    ;;
        -rho) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              rho=$arg
            fi
	    ;;
        *) echo "Unrecognized flag or argument: $flag"
            ;;
        esac
    shift
done

rm -rf ${outfile}
echo "./AK ${bench} ${seed} ${TotalAnts} ${TotalEvaluations} ${alpha} ${beta} ${ph_max} ${ph_min} ${rho} ${Budget} ${alpha_p1} ${beta_p1} ${rho_p1} ${taumax_p1} ${Method} ${Stats} >> ${outfile}"
./AK ${bench} ${seed} ${TotalAnts} ${TotalEvaluations} ${alpha} ${beta} ${ph_max} ${ph_min} ${rho} ${Budget} ${alpha_p1} ${beta_p1} ${rho_p1} ${taumax_p1} ${Method} ${Stats} >> ${outfile}
#done
