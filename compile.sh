#!/bin/bash
gnome-terminal -e "/bin/bash -c 'nasm -f elf64 -o resultado.o $1; ld -s resultado.o -o run; ./run;echo;read -p'Pulse intro';exit'" # ;indica fin de una sentencia 
#$1 - es e primer param pasado por linea de comando