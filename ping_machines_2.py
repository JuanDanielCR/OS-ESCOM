#!/usr/bin/python
import subprocess, sys


def getPings(terminal):
	si=open('si.txt','w+')
	no=open('no.txt','w+')
	subredes = 1
	ip = []
	ip_novalida = []
	while(subredes<255):
		host =terminal[1]
		host_ind = host.replace('x',str(subredes))
		if (subprocess.call(['ping','-c','3','-w','5',host_ind], stdout = open('/dev/null','w'),stderr = open('/dev/null','w')))==0:
			ip.append(host_ind)
			print "SI: "+host_ind
			si.write(host_ind+"\n")
		else:
			ip_novalida.append(host_ind)
			print "NO:"+host_ind
			no.write(host_ind+"\n")
		subredes = subredes +1;
	si.close()
	no.close()
getPings(sys.argv)