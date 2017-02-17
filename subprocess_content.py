#!/usr/bin/python
import subprocess, sys, os

def getDirectories(direct):
	conteo_archivos = 0
	conteo_dir = 2 #directorios . | ..
	directorios = subprocess.check_output(['ls','-a',direct[1]])
	concat = ''
	for directorio in directorios:
		if(directorio == "\n"):
			if os.path.isfile(concat):
				conteo_archivos = conteo_archivos +1
			else:
				conteo_dir = conteo_dir + 1
			print concat
			concat = ''
		else:
			concat = concat + directorio

	print "Archivos: "+str(conteo_archivos)
	print "Directorios: "+str(conteo_dir)

getDirectories(sys.argv)