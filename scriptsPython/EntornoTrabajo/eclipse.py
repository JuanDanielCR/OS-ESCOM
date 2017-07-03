#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, os, subprocess
def instalar():
	eclipse = 'eclipse-jee-neon-3-linux-gtk-x86_64.tar.gz'
#Descomprima el archivo tar.gz
	subprocess.call(['tar','-xzvf',eclipse])
#Mover los archivos que se descomprimieron a la carpeta /opt
	subprocess.call(['mv','eclipse','/opt/'])

#Crear icono de eclipse con la creación de un archivo .desktop
	path = "/usr/share/applications/eclipse.desktop"
	file = open(path,"w") 
	contenido = "[Desktop Entry]\nType=Application\nEncoding=UTF-8\nName=Eclipse\nComment=Eclipse IDE\nExec=/opt/eclipse/eclipse\nIcon=/opt/eclipse/icon.xpm\nTerminal=false\nType=Application\nCategories=GNOME;Application;Development;\nStartupNotify=true`"
	file.write(contenido) 
	file.close()
	subprocess.call(['rm','-rf','eclipse']) 
	exit(0)
instalar()