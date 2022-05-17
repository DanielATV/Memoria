import os
import subprocess
import numpy as np
import pandas as pd
import xlsxwriter
import time

 

filler="0 0 0 0 0 0 0 0"
# Semillas
np.random.seed(1)
semillas=(list(np.random.randint(low = 50,size=10)))
contSemillas= 1
contInstancias= 1


# Create a workbook and add a worksheet.
workbook = xlsxwriter.Workbook('ResultadoEval.xlsx')
worksheet = workbook.add_worksheet()

# Write some data headers.
worksheet.write('A1', 'Instancia')
worksheet.write('B1', 'Best Time')
worksheet.write('C1', 'Mean Time')
worksheet.write('D1', 'Best Quality')
worksheet.write('E1', 'Mean Quality')
worksheet.write('F1', 'STD Quality')

# Start from the first cell below the headers.
row = 1
col = 0
 

folder="TestingReFormat"

print("---------Evaluando {semi} semillas en la carpeta {fold}---------".format(semi= len(semillas),fold=folder))
path = "../../{folder}".format(folder=folder)
dir_list = os.listdir(path)
dir_list.sort()


# Lectura de istancias
for instance in dir_list:
    if (instance.endswith(".dat")):
        print("--------------Evaluacion {cont}----------------".format(cont=contInstancias))
        print("--------------Instancia: "+ instance+"--------------")

        bestTime= float('inf')
        quality= list()
        timeList= list()
        bestQual= float('inf')
        #Lectura de parametros
        with open('parametros.txt') as f:
            for line in f:
                line= line.rstrip('\n')
                #Evaluacion en instancias
                for seed in semillas:
                    print("--------------Evaluando semilla {cont}/{tot}----------------".format(cont=contSemillas, tot= len(semillas)))
                    command="./AK {ruta}/{instan} {seed} {params} {filler}".format(instan= instance,ruta= path, seed=seed, params=line, filler=filler)
                    print(command)
                    with subprocess.Popen(command, stdout=subprocess.PIPE, stderr=None, shell=True) as process:
                        start_time = time.time()
                        output = float(process.communicate()[0].decode("utf-8"))
                        timeUsed= time.time() - start_time
                        print(output)
                        quality.append(output)
                        timeList.append(timeUsed)

                        if output <= bestQual:
                            bestQual= output
                        if timeUsed <= bestTime:
                            bestTime= timeUsed
                    contSemillas+=1
                contSemillas= 1

        # Iterate over the data and write it out row by row.
        worksheet.write(row, col, instance)
        worksheet.write(row, col + 1, bestTime)
        worksheet.write(row, col + 2, np.mean(timeList))
        worksheet.write(row, col + 3, bestQual)
        worksheet.write(row, col + 4, np.mean(quality))
        worksheet.write(row, col + 5, np.std(quality))
        row += 1
        contInstancias += 1
workbook.close()  


                    


'''
semilla= "4947"
hormigas="4"
evaluaciones= "1000" fijo
alpha ="1.0000"
beta = "6.4330"
ph_max = "26.5240"
ph_min = "0.01" fijo
rho = "0.1760"




command="./"
command="./AK ../../AllInst/OR5x100-0.25_8.dat 4947 4 1000 1.0000 6.4330 26.5240 0.01 0.1760 0 0 0 0 0 0 0 0"


with subprocess.Popen(command, stdout=subprocess.PIPE, stderr=None, shell=True) as process:
    output = process.communicate()[0].decode("utf-8")
    #print(output)

. Al final de ejecutar las 20 semillas, es ideal que el mismo script te calcule el tiempo de ejecución,
 el mejor tiempo, el promedio, la mejor calidad obtenida, el promedio de la calidad, la desviación std.
'''
