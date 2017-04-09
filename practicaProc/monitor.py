#!/usr/bin/python
import time 
from datetime import datetime

#menu
def menu():
	continuar = 1
	modo = 1

	while continuar == 1:
		print "Elige un modo: "
		print "Automatico--------- 1"
		print "Memoria------------ 2"
		print "Procesador--------- 3"
		print "CPU---------------- 4"
		print "Disco-------------- 5"
		modo = raw_input()
		print modo
		if modo == "1":
			start_monitor_auto()
		elif modo == "2":
			start_selected_monitor(1) #memoria
		elif modo == "3":
			start_selected_monitor(2) #procesador
		elif  modo == "4": 
			start_selected_monitor(3) #cpu
		elif modo == "5":
			start_selected_monitor(4) #disco
		else:
			print "Elige una opcion del menu"

		print "Continuar? 1 - Si | 0 - No"
		if input() == 0:
			continuar = 0

#monitor loop
def start_selected_monitor(accion):
	print datetime.now().strftime('%Y-%m-%d %H:%M:%S')
	if accion == 1:
		get_info_from_file(1) #memoria
	elif accion == 2:
		get_info_from_file(2) #procesador
	elif accion == 3:
		get_info_from_file(3) #cpu 
	elif accion == 4:
		get_info_from_file(4) #disco

def start_monitor_auto():
	i = 1
	while True	:
		get_info_from_file(1)
		get_info_from_file(2)
		get_info_from_file(3)
		get_info_from_file(4)
		print str(i)+" Monitor Sistema | Juan Daniel ESCOM  | " + datetime.now().strftime('%Y-%m-%d %H:%M:%S')
		i = i+1
		time.sleep(5.0 - ((time.time() - 3.0))%5.0)
#read file
def get_info_from_file(id):
	disks = []
	cpus = [] 
	values_list = []
	if id == 1:
		print "--------MEMORIA------"
		analyse_file('/proc/meminfo', values_list,id,cpus)
		print "Total:            " + str(values_list[0])+" kB"
		print "Libre:             " + str(values_list[1])+" kB" 
		print "Uso:              " + str(values_list[2])+" kB"
		porcentaje = float(values_list[2]*100)/float(values_list[0])
		print "Porcentaje usado: %.4f" %porcentaje +"%"
	elif id == 2:
		print "--------PROCESADOR------"
		analyse_file('/proc/cpuinfo',values_list,id,cpus)
		print "Procesador:          " + str(values_list[0])
		print "Fabricante:          " + str(values_list[1])
		print "Modelo:              " + str(values_list[2])
		print "Velocidad:           " + str(values_list[3])
		print "# cores:             " + str(values_list[4])
	elif id == 3:
		print "--------Informacion del CPU--------"
		analyse_file('/proc/stat',values_list,id,cpus);
		total_use = 0.0
		i = 0
		for cpu in cpus:
			total_use = total_use + (float(cpu[1])+float(cpu[2])+float(cpu[3])+float(cpu[6])+float(cpu[7]))/(float(cpu[1])+float(cpu[2])+float(cpu[3])+float(cpu[4])+float(cpu[5])+float(cpu[6])+float(cpu[7]))*100
			print("%s usado: %.4f %s" %(cpus[i][0],(float(cpu[1])+float(cpu[2])
				+float(cpu[3])+float(cpu[6])+float(cpu[7]))/
				(float(cpu[1])+float(cpu[2])+float(cpu[3])+float(cpu[4])+float(cpu[5])+float(cpu[6])+float(cpu[7]))*100,"%"))
			i = i+1
		print "Uso total:  %.2f " %((total_use)/i)+"%"
		print "Interrupciones:      " + str(values_list[0])
		print "Context Switch:      " + str(values_list[1])
		print "Booted time:         " + str(values_list[2])
		print "# procesos:          " + str(values_list[3])
		print "# procesos actuales: " + str(values_list[4])
		print "# procesos bloqueados:" + str(values_list[5])
	elif id== 4:
		print "--------Informacion del Disco------"
		analyse_file('/proc/diskstats',values_list,id,disks);
		print "Tienes %d discos virtuales" % len(disks)
		for disk in disks:
			print str(disk[2]).upper()
			print "Lecturas: " + str(disk[3])+" | Escrituras: " + str(disk[7])+" | Tiempo lectura: " + str(float(disk[6])/(1000*3))+"seg | Tiempo escritura: " + str(float(disk[10])/(1000*3))+"seg | Uso de disco: " + str(float(disk[12])/1000) 
			#3 en la multiplicacion - numero de procesadores ya que cada uno usa el I/O y Tiempo de lectura es el usado por los tres
			print "Sectores leidos: "+str(disk[5])+" Sectores escritos: "+str(disk[9]) 

#analyze files
def analyse_file(ruta,values_list,id,devices):
	archivo = open(ruta)
	linea = 'default'
	while linea != '':
		linea = archivo.readline();
		if id == 1:
			get_mem_data(linea, values_list)
		elif id == 2:
			get_processor_info(linea, values_list)
		elif id == 3:
			get_cpu_usage(linea, values_list, devices)
		elif id == 4:
			get_disk_info(linea, values_list,devices)

#-----memory function---------
def get_mem_data(linea,values):
	prop = linea.split(" ")
	if prop[0] == "MemTotal:":
		values.append(get_value(linea)) 
	elif prop[0] == "MemFree:":
		values.append(get_value(linea)) 
	elif prop[0] == "Active:":
		values.append(get_value(linea)) 

#-----processor function------
def get_processor_info(linea,values):
	prop = linea.split(":")
	aux = ""
	if prop[0] == "processor\t":
		aux = prop[1].rstrip()
		values.append(aux)
	elif prop[0] == "vendor_id\t":
		aux = prop[1].rstrip()
		values.append(aux)
	elif prop[0] == "model name\t":
		aux = prop[1].rstrip()
		values.append(aux)
	elif prop[0] == "cpu MHz\t\t":
		aux = prop[1].rstrip()
		values.append(aux)
	elif prop[0] == "cpu cores\t":
		aux = prop[1].rstrip()
		values.append(aux)

#-----cpu function------------
def get_cpu_usage(linea, values, cpus):
	prop = linea.split()
	if len(prop) > 0:
		if prop[0].find("cpu") != -1:
			cpus.append(prop)
		else:
			values.append(prop[1])

#-----disk function-----------
def get_disk_info(linea, values, disks):
	prop = linea.split();
	if len(prop) > 0:
		if prop[2].find("sd") != -1 or prop[2].find("hd") != -1:
			disks.append(prop)

#------analizes each line and returns the propertie's value-----
def get_value(lista):
	valor = ""
	for elemento in lista:
		if elemento.isdigit() == True:
			valor = valor + elemento
	return int(valor)

menu()