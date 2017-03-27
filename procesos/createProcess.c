#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int proceso = fork();
  if(proceso == 0){
    printf("%s\n", "Soy el padre");
  }else {
    if(proceso > 0){
      printf("Soy el hijo");
    }else{
      printf("Error");
    }
  }
  return 0;
}
