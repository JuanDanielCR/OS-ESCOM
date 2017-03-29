#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pid = fork();
  /*After calling fork both processes parent and child will execute all the next code*/
  if(pid == 0){
    printf("%s pid: %d\n", "Soy el hijo",pid);
  }else if(pid > 0){
    printf("%s pid: %d\n", "Soy el padre",pid);
  }else if(pid < 0){
    printf("%s\n", "Error");
  }
  return 0;
}
