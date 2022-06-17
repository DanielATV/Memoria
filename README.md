# Readme

### Resumen

El siguiente código es una modificación al código de EVOKA. La modificación consiste en añadir un modelo de ML para ayudar al operador de mutación. Para esto recopila información de las configuraciones descartadas y aceptadas, en donde las aceptadas se les da la clase 1 y las rechazadas 0.

 La cantidad de iteraciones que recopila datos esta dada por el parametro dataThreshold del makefile. Una vez terminada la recolección de datos se procede a evaluar el modelo. Para esto se compara el output del modelo con el resultado de la mutación. La cantidad de iteraciones que se evalua el modelo esta dada por el parámetro evalThreshold del makefile.

 Una vez terminada la evaluación se utiliza el modelo para determinar si las configuraciones cruzadas deben ser mutadas o no.

### Instalación
sudo apt install libmlpack-dev mlpack-bin libarmadillo-dev 

### Ejecución

Output consola:
`make exe`

Ejecucion en segundo plano:
`nohup make exe > salidaOutfile &`






