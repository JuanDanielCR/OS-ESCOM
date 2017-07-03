#!/usr/bin/python
import sys, os, subprocess

def instalar():
	archivoFaltante = 0
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
	print 'Todos los archivos enncontrados'

	

	print 'Java 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instala'
		try:
			subprocess.call(['chmod','+x','java.py'])
			returnCode = subprocess.call(['python','java.py'])
		except ValueError:
			print "Oops!  That was no valid number.  Try again..."
		print returnCode
instalar()
