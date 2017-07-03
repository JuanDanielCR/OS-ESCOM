#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, os, subprocess
def instalar():
	sonarZip = 'sonarqube-5.6.6.zip'
	sonarQube = 'sonarqube-5.6.6'
	sonarScannerZip = 'sonar-scanner-2.8.zip'
	sonarScanner = 'sonar-scanner-2.8'
#Descomprimir el archivo de sonar.x.x.zip
	subprocess.call(['unzip',sonarZip])
#Crear el directorio /usr/local/sonar
	subprocess.call(['mkdir','/usr/local/sonar'])
#Crear el directorio /usr/local/sonar/sonar
	subprocess.call(['mkdir','/usr/local/sonar/sonar'])
#Cambiar la ubicación de la carpeta sonar.x.x al directorio /usr/local/sonar/sonar
	subprocess.call(['mv',sonarQube,'/usr/local/sonar/sonar'])
#Crear el usuario para sonar
	subprocess.call(['groupadd','sonar'])
#Crear un usuario con el nombre sonar, agregarlo al grupo con nombre igual y asignnarle el directorio /usr/local/sonar/ como su home
	subprocess.call(['useradd','-g','sonar','-d','/usr/local/sonar/','sonar'])	     
 	
#Archivo de configuracion para sonar
 	path = "/etc/init.d/sonar"
 	file = open(path,"w") 
	contenido = "#!/bin/sh\n### BEGIN INIT INFO\n# Provides:\tsonar\n# Required-Start:\t$syslog\n# Required-Stop:\t$syslog\n# Default-Start:\t2 3 4 5\n# Default-Stop:\t0 1 6\n# Short-Description: arranque automatico de sonar\n# Description:\n### END INIT INFO\ncase $1 in\nstart)\n  sh /usr/local/sonar/sonar/sonarqube-5.6.6/bin/linux-x86-64/sonar.sh start\n;;\nstop)\nsh /usr/local/sonar/sonar/sonarqube-5.6.6/bin/linux-x86-64/sonar.sh stop\n;;\nrestart)\nsh /usr/local/sonar/sonar/sonarqube-5.6.6/bin/linux-x86-64/sonar.sh restart\n;;\nesac\nexit 0"
	file.write(contenido) 
	file.close()
#Cambiar los permisos del archivo /etc/init.d/sonar para que se pueda ejecutar
	subprocess.call(['chmod','755','/etc/init.d/sonar'])
#Agregar una liga símbolica al script de arranque de Sonar
	subprocess.call(['update-rc.d','sonar','defaults'])  
#Copiar el zip de sonar-scanner a /usr/local/sonar
	subprocess.call(['cp',sonarScannerZip,'/usr/local/sonar/'])
#Descomprimir el zip de sonar-scanner en la carpeta de /usr/local/sonar
	subprocess.call(['unzip','/usr/local/sonar/'+sonarScannerZip])
	subprocess.call(['mv',sonarScanner+'/','/usr/local/sonar/'])
#Cambiar el nombre sonar-scanner por sonar-runer
	subprocess.call(['mv','/usr/local/sonar/'+sonarScanner+'/','/usr/local/sonar/sonar-runner/'])

	path = "/etc/bash.bashrc"
	file = open(path,"a") 
	contenido = "export PATH=$PATH:/usr/local/sonar/sonar-runner/bin\n"
	file.write(contenido) 
	file.close()
#Iniciar sonar
	subprocess.call(['/etc/init.d/sonar','start'])
	subprocess.call(['rm','-rf',sonarQube]) 
	subprocess.call(['rm','-rf',sonarScanner]) 
	exit(0)
instalar()