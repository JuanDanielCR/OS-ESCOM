#!/usr/bin/python
import subprocess, time
#libreria subprocess permite ejecutar comandos linux
hosts = ('8.8.8.8','kernel.org','yahoo.com')

def ping(hosts):
	ret = subprocess.call(['ping','-c','3','-w','5',hosts], stdout = open('/dev/null','w'),stderr = open('/dev/null','w')) 
	#stdout: /dev: dentro hay una terminal, la salida estandar es un terminal con permisos de escritura
	#stderr: al igual que arriba
	#stdin
	return ret == 0

def net_is_up():
	print "[%s] check if network is up..." % time.strftime("%Y-%m-%d %H-%M-%S")
	xstatus = 1
	for h in hosts:
		if ping(h):
			print "[%s] check if network is up" % time.strftime("%Y-%m-%d %H-%M-%S")
			xstatus = 0
			break
	if xstatus:
		print "[%S] network is down"

	return xstatus

quit(net_is_up()d)

