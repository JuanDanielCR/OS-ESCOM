#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, os, subprocess, getpass

"""
CDT 2017
Author: Juan Daniel Castillo Reyes
103857448
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
	slack = 'slack-desktop-2.6.3-amd64.deb'
	texStudio = 'texstudio_2.12.4-3.1_amd64.deb'
	balsamicZip = 'Balsamiq_Mockups_3.5.13_bundled.zip'
	balsamic = 'Balsamiq_Mockups_3'
	balsamicExe = 'Balsamiq Mockups 3.exe'
#Validacion para saber si el directorio actual contiene los archivos necesarios
	archivoFaltante = 0
	#Buscando el archivo de Java
	if os.path.isfile(javaTar) != 1:
		print 'Archivo faltante: '+javaTar
		archivoFaltante = 1
	if os.path.isfile(slack) != 1:
		print 'Archivo faltante: '+slack
		archivoFaltante = 1
	if os.path.isfile(balsamicZip) != 1:
		print 'Archivo faltante: '+balsamicZip
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

#---Texlive-----
	print 'Texlive 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Texlive'
		try:
			returnCode = subprocess.call(['apt-get','install','texlive-full'])  
			if returnCode == 0:
				print 'Texlive se ha instalado'
		except Exception, e:
			print 'Error al instalar Texlive :('
			pass

#---TexStudio----
	print 'TexStudio 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando TexStudio'
		try:
			subprocess.call(['apt-get','install','gdebi'])
			subprocess.call(['wget','http://download.opensuse.org/repositories/home:/jsundermeyer/Debian_7.0/amd64/texstudio_2.9.4_amd64.deb'])
			returnCode = subprocess.call(['gdebi','install','gdebi'])
			if returnCode == 0:
				print 'TexStudio se ha instalado'
			subprocess.call(['rm','-rf','texstudio*'])
		except Exception, e:
			print 'Error al instalar TexStudio :('
			pass

#---Wine---- 
	print 'Wine 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Wine'
		try:
			#Enable multiarch
			subprocess.call(['dpkg','--add-architecture','i386'])
			subprocess.call(['apt','update'])
			returnCode = subprocess.call(['apt','install','wine'])
			if returnCode == 0:
				print 'Wine se ha instalado'
		except Exception, e:
			print 'Error al instalar Wine :('
			pass

#---Wine Development---- 
	print 'Wine Development 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Wine Development'
		try:
			returnCode = subprocess.call(['apt','install','wine-development'])
			if returnCode == 0:
				print 'Wine Development se ha instalado'
		except Exception, e:
			print 'Error al instalar Wine Development :('
			pass

#---OpenVpn---- 
	print 'OpenVpn 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando OpenVpn'
		try:
			subprocess.call(['apt-get','install','openvpn'])
			returnCode = subprocess.call(['apt-get','install','network-manager-openvpn-gnome'])
			if returnCode == 0:
				print 'OpenVpn se ha instalado'
		except Exception, e:
			print 'Error al instalar OpenVpn :('
			pass

#---Balsamic Mockups---
	print 'Balsamic Mockups 1-(Yes) 2-(No): '
	proceed = raw_input()
	if proceed == '1':
		print 'Instalando Balsamic Mockups'
		try:
			subprocess.call(['unzip',balsamicZip])
			print os.getlogin()
			subprocess.call(['mv',balsamic,'/home/'+os.getlogin()+'/Balsamiq'])
			subprocess.call(['mv','/home/'+os.getlogin()+'/Balsamiq/Balsamiq Mockups 3.exe', '/home/'+os.getlogin()+'/Balsamiq/balsamiq.exe'])
			
			returnCode = subprocess.call(['wine', '/home/'+os.getlogin()+'/Balsamiq/balsamiq.exe'])
			#Crear icono de Balsamic con la creación de un archivo .desktop
			path = "/usr/share/applications/Balsamic.desktop"
			file = open(path,"w") 
			contenido = '[Desktop Entry]\nType=Application\nEncoding=UTF-8\nName=Balsamiq Mockups\nExec=wine ~/'+balsamic+'/'+balsamicExe+'\nIcon=~/'+balsamic+'/icons/mockups_doc_ico_48.png\nTerminal=false\nCategories=Graphics;\nMimeType=application/x-xdg-protocol-tg;x-scheme-handler/tg;'
			file.write(contenido) 
			file.close()
			if returnCode == 0:
				print 'Balsamic Mockups se ha instalado'
		except Exception, e:
			print 'Error al instalar Balsamic Mockups :('
			pass
instalar()