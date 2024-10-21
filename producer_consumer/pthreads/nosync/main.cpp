#include <format>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stack>

template<typename T, std::size_t N>
class BoundedStack{
  public:
    explicit BoundedStack() = default;

    // Stack operations

    void Push(T val){
      stack.push(val);
    };

    void Pop(){
      stack.pop();
    };

    [[nodiscard]] std::size_t Size() const{
      return stack.size();
    }

  private:
    std::stack<T> stack;
};

void* Producer(void* args){
  std::cout << std::format("Producer Created\n");
  BoundedStack<int, 10>* buffer = static_cast<BoundedStack<int, 10>*>(args);
  for(;;){
    buffer->Push(10);
    std::cout << std::format("Producer has produced\n");
  }
}

void* Consumer(void* args){
  std::cout << std::format("Consumer Created\n");
  BoundedStack<int, 10>* buffer = static_cast<BoundedStack<int, 10>*>(args);
  for(;;){
    buffer->Pop();
    std::cout << std::format("Consumer has consumed\n");
  }
}

int main(){
  BoundedStack<int, 10> buffer{};
  std::array<pthread_t, 2> pthreads;
  int stat;
  stat = pthread_create(&pthreads[0], nullptr, Producer, &buffer);
  if(stat != 0){
    std::cout << errno << '\n';
  }
  stat = pthread_create(&pthreads[1], nullptr, Consumer, &buffer);
  if(stat != 0){
    std::cout << errno << '\n';
  }
  for(auto& thread: pthreads){
    stat = pthread_join(thread, nullptr);
    if(stat != 0){
      std::cout << std::format("An error has occured when trying to join");
    }
  }
}
