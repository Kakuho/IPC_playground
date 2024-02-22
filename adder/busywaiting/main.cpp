#include <iostream>
#include <sstream>
#include <pthread.h>

int number = 0;
int turn = -1;

void* dowork(void* k){
  while(true){
    if(turn == -1 && number < 50){
      turn = *(int*)k;
      number++;
      std::stringstream outputmessage;
      outputmessage << "Number incremented = " << number << "\n";
      std::cout << outputmessage.str();
      turn = -1;
    }
    else{
      // busy waiting
    }
  }
}

int main(){
  //pthread_create(&thread1, nullptr, &process, (void*)&pid1);
  for(int i = 0; i < 4; i++){
    pthread_t working_thread;
    pthread_create(&working_thread, nullptr, &dowork, (void*)&i);
  }
  while(true);
}
