#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void hilo1(void *);

int main(int argc, char const *argv[]) {
  pthread_t tid[10];

  for (int i = 0; i < 10; i++) {
    int valores[10];
    valores[i] = i;
    pthread_create(&tid[i], NULL, (void*)hilo1, (void *)&valores[i]);
  }
  for (size_t j = 0; j < 10; j++) {
    pthread_join(tid[j],NULL);
  }

  return 0;
}

void hilo1(void *args){
  int *param = (int*)args;

  printf("%d\n",*param);
  pthread_exit(NULL);
}
/*
Thread (proceso ligero): solo copia su subrutina, y tiene acceso a la memoria global del proceso que lo creo

int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void*), void *restrict arg);
 1.- apuntador un tipo pthread_t que es el identificador
 2.- apuntador a una struct con los atributos del thread (para su funcionamiento)
 3.- apuntador a una funcion que inicia el comportamiento del thread void*()- desreferenciación, (void*) cast
 4.- apuntador a los parametros que se pasan a la función

 return 0 -error
        1 -success

 pthread_join(pthread_t thread, void **value_ptr);

 pthread_exit().- Terminar un thread, madnar info
*(int*) - desreferenciacion
*/
