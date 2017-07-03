#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, os, subprocess
def instalar():
	tomcatTar = 'apache-tomcat-8.5.15.tar.gz'
	tomcat = 'apache-tomcat-8.5.15'
#Descomprima el archivo tar.gz
	subprocess.call(['tar','-xvzf',tomcatTar])
#Mover los archivos que se descomprimieron a la carpeta: /usr/local/tomcat
	subprocess.call(['mv',tomcat,'/usr/local/tomcat/'])
#Agregar la variable de entorno CATALINA_HOME mediante la edicion del archivo bash.bashrc
	path = "/etc/bash.bashrc"
	file = open(path,"a") #....(Al abrir el archivo en modo append si el script llega a fallar verificar este archivo para borrar la línea en caso de que la línea si halla sido agregada)
	contenido = "export CATALINA_HOME=/usr/local/tomcat/"
	file.write(contenido) 
	file.close()

#Crear el grupo con nombre tomcat
	subprocess.call(['groupadd','tomcat'])
#Creación del usuario Tomcat, asignación del directorio /usr/local/tomcat al usuario creado
	subprocess.call(['useradd','-g','tomcat','-d','/usr/local/tomcat/','tomcat'])
#Agregar el usuario al grupo www-data
	subprocess.call(['usermod','-G','www-data','tomcat']) 
#Ingresar la contraseña para el usuario tomcat
	print '***** Ingrese \'tomcat\' como password *****'
	subprocess.call(['passwd','tomcat'])
#Modificación del archivo /etc/passwd
	path = "/etc/passwd"
	file = open(path,"a") 
	contenido = "tomcat:x:1001:1001::/usr/local/tomcat/:/bin/bash"
	file.write(contenido) 
	file.close()
#Cambiar el usuario de la carpeta tomcat/
	subprocess.call(['chown','-R','tomcat:tomcat','tomcat/'])
#Arranque automático del tomcat, creación del archivo 
	path = "/etc/init.d/tomcat"
	file = open(path,"w") 
	contenido = "#!/bin/sh\n### BEGIN INIT INFO\n# Provides:\ttomcat\n# Required-Start:\t$syslog\n# Required-Stop:\t$syslog\n# Default-Start:\t2 3 4 5\n# Default-Stop:\t0 1 6\n# Short-Description:\tarranque automatico de tomcat\n# Description:\n### END INIT INFO\ncase $1 in\nstart)\nsh /usr/local/tomcat/bin/startup.sh\n;;\nstop)\nsh /usr/local/tomcat/bin/shutdown.sh\n;;\nrestart)\nsh /usr/local/tomcat/bin/shutdown.sh\nsh /usr/local/tomcat/bin/startup.sh\n;;\nesac\nexit 0"
	file.write(contenido) 
	file.close()
#Cambiar los permisos al archivo creado
	subprocess.call(['chmod','755','/etc/init.d/tomcat'])  
#Agregar una liga símbolica al script de arranque de Tomcat
	subprocess.call(['update-rc.d','tomcat','defaults']) 
#Iniciar el servidor de Tomcat
	subprocess.call(['/etc/init.d/tomcat','start'])
	subprocess.call(['rm','-rf',tomcat])
	exit(0)
instalar()