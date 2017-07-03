#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, os, subprocess

"""
CDT 2017
Author: Juan Daniel Castillo Reyes

Como utilizar el sig. script:

1 - Ubicar el script en la carpeta que contenga los archivos a descomprimir o utilizar
2 - Brindar permisos de ejecución al script: $ chmod +x cdt.py
3 - Ejecutar el script con : $ python cdt.py
4 - Disfrute su instalación
"""
  
#metodo que inicia el script
def instalar():
	myId = os.getuid()
	if myId!=0:
		print "Necesitas permisos de administrador :("
		sys.exit(1)

#Variables: Si desea modificar alguna version de algun paquete modifiquelo aquí y en el archivo de su script correspondiente ej. java.py
	javaTar = 'jdk-8u131-linux-x64.tar.gz'
	javaVersion = 'jdk1.8.0_131'
	dBeaver = 'dbeaver-ce_4.0.8_amd64.deb'
	slack = 'slack-desktop-2.6.3-amd64.deb'
	eclipse = 'eclipse-jee-neon-3-linux-gtk-x86_64.tar.gz'
	sonarZip = 'sonarqube-5.6.6.zip'
	sonarQube = 'sonarqube-5.6.6'
	sonarScannerZip = 'sonar-scanner-2.8.zip'
	sonarScanner = 'sonar-scanner-2.8'
	tomcatTar = 'apache-tomcat-8.5.15.tar.gz'
	tomcat = 'apache-tomcat-8.5.15'
	netbeans = 'netbeans-8.2-linux.sh'
#Validacion para saber si el directorio actual contiene los archivos necesarios
	archivoFaltante = 0
	#Buscando el archivo de Java
	if os.path.isfile(javaTar) != 1:
		print 'Archivo faltante: '+javaTar
		archivoFaltante = 1
	if os.path.isfile(dBeaver) != 1:
		print 'Archivo faltante: '+dBeaver
		archivoFaltante = 1
	if os.path.isfile(slack) != 1:
		print 'Archivo faltante: '+slack
		archivoFaltante = 1
	if os.path.isfile(eclipse) != 1:
		print 'Archivo faltante: '+eclipse
		archivoFaltante = 1
	if os.path.isfile(sonarZip) != 1:
		print 'Archivo faltante: '+sonarZip
		archivoFaltante = 1
	if os.path.isfile(sonarScannerZip) != 1:
		print 'Archivo faltante: '+sonarScannerZip
		archivoFaltante = 1
	if os.path.isfile(tomcatTar) != 1:
		print 'Archivo faltante: '+tomcatTar
		archivoFaltante = 1
	if os.path.isfile(netbeans) != 1:
		print 'Archivo faltante: '+netbeans
		archivoFaltante = 1
	#Algun archivo no fue encontrado
	if archivoFaltante == 1:
		exit(1)

	
#Actualización de los paquetes contenido en la PC
	subprocess.call(['apt','update','-y'])
	subprocess.call(['apt','upgrade','-y'])
	subprocess.call(['apt','install','-f','-y'])
	
#---Sublime Text----
	print 'Sublime Text 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Sublime Text'
		try:
			subprocess.call(['wget','http://c758482.r82.cf2.rackcdn.com/sublime-text_build-3083_amd64.deb'])
			returnCode = subprocess.call(['dpkg','-i','sublime-text_build-3083_amd64.deb'])
			if returnCode == 0:
				print 'Sublime Text se ha instalado'
			subprocess.call(['rm','-rf','sublime-text*'])
		except Exception, e:
			print 'Error al instalar Sublime :('
			pass

#---Java----
	print 'Java 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Java'
		try:
			subprocess.call(['chmod','+x','java.py'])
			returnCode = subprocess.call(['python','java.py'])
			if returnCode == 0:
				print 'Java se ha instalado'
		except Exception, e:
			print 'Error al instalar Java :('
			pass

#---Dbeaver----
	print 'DBeaver 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando dBeaver'
		try:
			returnCode = subprocess.call(['dpkg','-i',dBeaver])
			if returnCode == 0:
				print 'dBeaver se ha instalado'
		except Exception, e:
			print 'Error al instalar DBeaver :('
			pass
		

#---Slack-----
	print 'Slack 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Slack'
		try:
			returnCode = subprocess.call(['dpkg','-i',slack])
			if returnCode == 0:
				print 'Slack se ha instalado'
		except Exception, e:
			print 'Error al instalar Slack :('
			pass

#---Eclipse---
	print 'Eclipse 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Eclipse'
		try:
			subprocess.call(['chmod','+x','eclipse.py'])
			returnCode = subprocess.call(['python','eclipse.py'])
			if returnCode == 0:
				print 'Eclipse se ha instalado'
		except Exception, e:
			print 'Error al instalar Eclipse :('
			pass

#---Sonar---
	print 'Sonar 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Eclipse'
		try:
			subprocess.call(['chmod','+x','sonar.py'])
			returnCode = subprocess.call(['python','sonar.py'])
			if returnCode == 0:
				print 'Eclipse se ha instalado'
		except Exception, e:
			print 'Error al instalar Sonar :('
			pass

#---Tomcat---
	print 'Tomcat 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Tomcat'
		try:
			subprocess.call(['chmod','+x','tomcat.py'])
			returnCode = subprocess.call(['python','tomcat.py'])
			if returnCode == 0:
				print 'Tomcat se ha instalado'
		except Exception, e:
			print 'Error al instalar Tomcat :('
			pass

#---Subversion---
	print 'Subversion 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Subversion'
		try:
			returnCode = subprocess.call(['apt-get','install','subversion'])
			if returnCode == 0:
				print 'Subversion se ha instalado'
		except Exception, e:
			print 'Error al instalar Subversion :('
			pass

#---PostgresSQL---
	print 'PostgresSQL 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando PostgresSQL'
		try:
			returnCode = subprocess.call(['apt-get','install','postgresql-9.4-postgis-2.1'])
			if returnCode == 0:
				print 'PostgresSQL se ha instalado'
		except Exception, e:
			print 'Error al instalar PostgresSQL:('
			pass

#---Permisos para Netbeans y Visual Paradigm---
	subprocess.call(['chmod','+x',netbeans])
 	
 	print '\n\n\n\n***********************************************************'
	print 'Para verificar la correcta instalación realice los siguientes pasos:\n'
	print 'Java: $ java -version\n'
	print 'Tomcat: Acceda a localhost:8080\n'
	print 'Sonar: Acceda a localhost:9000, aun falta configurar sonar en eclipse\n'
	print 'Eclipse: Ingrese Eclipse al menú busqueda para verificar la creación del icono, agregue Jetty a Eclipse\n'
	print 'Slack: Ingrese Slack al menú busqueda para verificar la creación del icono\n'
	print 'Dbeaver: Ingrese DBeaver al menú busqueda para verificar la creación del icono\n'
	print 'Subversion: $svn --version\n'
	print '********  La instalación Netbeans, VisualParadigm y la configuracion de PostgresSQL no es realizada por este Script utilize los archivos .sh correspondientes :)\n'
	exit(0)

instalar()  