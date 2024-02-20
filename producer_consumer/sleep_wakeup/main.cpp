#include <iostream>
#include <array>
#include <pthread.h>

int done = 0;
int turn = 0;
bool product = 0;
std::array<int, 2> interested{};

void* producer(void*){
  while(true){
    // producer is process 0
    int other = 1;
    int producer = 0;
    interested[producer] = true;
    turn = producer;
    while(turn == producer && interested[other] == true) /* busy waiting */ ;
    // Critical Region Occurs Here
    if(product == false){
      std::cout << "Producer has produced food" << '\n';
      product = true;
    }
    else{
      std::cout << "There is already food, Producer sighs -_-" << '\n';
    }
    interested[producer] = false;
  }
}

void* consumer(void*){
  // consumer is process 1
  while(true){
    int other = 0;
    int consumer = 1;
    interested[consumer] = true;
    turn = consumer;
    while(turn == consumer && interested[other] == true) /* busy waiting */ ;
    // Critical Region Occurs Here
    if(product == true){
      std::cout << "Consumer has ate food" << '\n';
      product = false;
    }
    else{
      std::cout << "There is no food, Consumer cries!" << '\n';
    }
    interested[consumer] = false;
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
  pthread_t thread1, thread2;
  pthread_create(&thread1, nullptr, &producer, nullptr);
  pthread_create(&thread2, nullptr, &consumer, nullptr);
  while(true);
}
