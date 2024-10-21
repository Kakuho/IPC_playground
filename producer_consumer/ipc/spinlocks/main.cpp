#include <iostream>
#include <array>
#include <pthread.h>

int done = 0;
int turn = 0;
bool product = 0;


void* producer(void*){
  while(true){
    if(turn == 0){
      product = true;
      std::cout << "producer has produced food" << '\n';
      turn = 1;
    }
    else /* busy waiting */ ;
  }
}

void* consumer(void*){
  while(true){
    if(turn == 1){
      product = false;
      std::cout << "consumer has eaten food" << '\n';
      turn = 2;
    }
    else /* busy waiting */ ;
  }
}

void* separator(void*){
  while(true){
    if(turn == 2){
      std::cout << "\n\n";
      turn = 0;
    }
    else /* busy waiting */ ;
  }
}

int main(){
  pthread_t thread1, thread2, thread3;
  pthread_create(&thread1, nullptr, &producer, nullptr);
  pthread_create(&thread2, nullptr, &consumer, nullptr);
  pthread_create(&thread3, nullptr, &separator, nullptr);
  while(true);
}
