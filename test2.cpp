#include <iostream>
#include <vector>
#include <ctime>


using namespace std;

int main(){
  clock_t start;
  double duration;
  start = clock();
  for (int i=0; i<10; i++){
    cout << i << '\n';
    continue;
  }
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << duration;
}
