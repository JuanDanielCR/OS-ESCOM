#!/usr/bin/python
import sys, os, subprocess

def obtenerDirectorios(directorios):

	archivos_cuenta = subprocess.call(['ls','-a',directorios[1]])
	archivos = os.listdir(directorios[1])
	conteo_archivos = 0
	conteo_dir = 0

	for archivo in archivos:
		if os.path.isfile(archivo):
			conteo_archivos = conteo_archivos +1
		else:
			conteo_dir = conteo_dir + 1
		print archivo
	print "Archivos: "+str(conteo_archivos)
	print "Directorios: "+str(conteo_dir)


obtenerDirectorios(sys.argv)