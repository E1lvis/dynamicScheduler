#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>

#include "seq_loop.hpp"

#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

float integrateFunction(float (*f)(float, int), float frac, float a, float i, int intensity ){
	
	float value = (frac)*(f(a+(i+0.5)*frac, intensity));
	if(f == f2){
		//std::cout<<"| i =" << i << " |";
	}
	return value; //f(a + (i+0.5)*frac, intensity) * frac;
}

int main (int argc, char* argv[]) {
SeqLoop s1;

  if (argc < 8) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads> <granularity>"<<std::endl;
    return -1;
  }

   int functionid = atoi(argv[1]);
    float a = atof(argv[2]);
    float b = atof(argv[3]);
    float n = atof(argv[4]);
    int nThreads = atoi(argv[6]);
     
    int intensity = atoi(argv[5]);

    float (*functionInUse)(float, int);

    switch (functionid)
    {
    case 1:
      functionInUse = f1;
      break;
    case 2:
      functionInUse = f2;
      break;
    case 3:
      functionInUse = f3;
      break;
    case 4:
      functionInUse = f4;
      break;
    default:

      break;
    }

  double frac = (b-a)/n;
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  double sum = 0;
  
  s1.parfor<double>(1, n, 1, nThreads,
		 [&](double& tls){
		 tls = 0;

		 },
		[&](int i, double& tls) ->void {
		tls += integrateFunction(*functionInUse, frac, a, i, intensity);
		},
		 [&](double& tls) -> void{
		   sum += tls;
		 }
		 );

std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

std::chrono::duration<double> elapsed_seconds = end-start;


std::cout << sum << std::endl;

std::cerr<<elapsed_seconds.count()<<std::endl;

  return 0;
}
