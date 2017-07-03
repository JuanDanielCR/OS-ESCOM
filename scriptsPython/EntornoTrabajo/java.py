#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, os, subprocess
def instalar():
	print 'Instalador de Java'
	javaTar = 'jdk-8u131-linux-x64.tar.gz'
	javaVersion = 'jdk1.8.0_131'
#---Java----
#Descomprima el archivo tar.gz
	subprocess.call(['tar','-xvf',javaTar]) 
#Directorio para alojar Java
	subprocess.call(['mkdir','/usr/local/java'])
#Mover los archivos que se descomprimieron a la carpeta: /usr/local/java'
	subprocess.call(['mv',javaVersion,'/usr/local/java'])
#Indicarle a Debian la ubicación de los comandos de Java: java, javac, jar, javaws
	subprocess.call(['update-alternatives','--install','/usr/bin/java','java','/usr/local/java/'+javaVersion+'/bin/java','1099'])
	subprocess.call(['update-alternatives','--install','/usr/bin/javac','javac','/usr/local/java/'+javaVersion+'/bin/javac','1099'])
	subprocess.call(['update-alternatives','--install','/usr/bin/jar','jar','/usr/local/java/'+javaVersion+'/bin/jar','1099'])
	subprocess.call(['update-alternatives','--install','/usr/bin/javaws','javaws','/usr/local/java/'+javaVersion+'/bin/javaws','1099'])
	print '\n\n\n******Verifica que la version: '+javaVersion+' este seleccionada'
	subprocess.call(['update-alternatives','--config','java'])
	subprocess.call(['rm','-rf',javaVersion]) 
	exit(0)
instalar()