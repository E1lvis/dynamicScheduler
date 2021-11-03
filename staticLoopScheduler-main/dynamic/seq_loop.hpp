#ifndef __SEQ_LOOP_H
#define __SEQ_LOOP_H
#include <thread>
//#include "static_sched.cpp"

#include <functional>
//int start = 0;
//int finish = 0;
//int breakPoint =0;
class SeqLoop {
public:
  /// @brief execute the function f multiple times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel
  void parfor (size_t beg, size_t end, size_t inc,
	       std::function<void(int)> f) {
    for (size_t i=beg; i<end; i+= inc) {
      f(i);
    }
  }

 

static void testFunction(int x, int y, double& tls, std::function<void(int, double&)>f, int breakPoint ){
	int counterTo = 0;

	for(x; x < y; x++){
	f(x, tls);
  	
	counterTo++;		
	
	if(counterTo == breakPoint ){
	break;
	}
	  
  	}

}

static void testFunction(int& x, int& y, double& tls, std::function<void(int, double&)>f ){
	

	for(x; x < y; x++){
	f(x, tls);
  	
		
	


}
}


  // @brief execute the function f multipl
  //
  //e times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel.
  ///
  /// Each thread that participate in the calculation will have its
  /// own TLS object.
  ///
  /// Each thread will execute function before prior to any
  /// calculation on a TLS object.
  ///
  /// Each thread will be passed the TLS object it executed before on.
  ///
  /// Once the iterations are complete, each thread will execute after
  /// on the TLS object. No two thread can execute after at the same time.
  //youre threading should be done in here 
  //tls will need to go into an array
  

  //chunks would be = iterations/ specified chunk size
  
  std::vector<std::thread> mythreads;
  template<typename TLS>
  void parfor (size_t beg, size_t end, size_t increment, int nThreads,
	       std::function<void(TLS&)> before,
	       std::function<void(int, TLS&)> f,
	       std::function<void(TLS&)> after
	       ) {
    
    int count = 0;
    int breakPoint = (end)/nThreads;
    
    TLS tls[nThreads];
    
    int chunkSize = end /(nThreads * 10);
    int localstart = 1;
    int i = 1;

    for(int x = 0; x < nThreads; x++){
      mythreads.push_back(std::thread(testFunction,std::ref(localstart), std::ref((localstart + chunkSize)), std::ref(tls[x]), f));

    }
    
    while (localstart < n){
      //thread(testFunction, localstart(starter), (localstart + chunkSiz)(end of iteration for this chunk), tls, f, ))
    for(std::thread &t: mythreads){
        if(t.joinable()){
          t.detach();
          localstart += chunkSize;

        }

    }

       // we will probably have to use localstart as the checker for the while loop or += chunkSize
    } 	
    for(int x = 0; x < nThreads; x++) {
    after(tls[x]);
    }
  }



};



#endif
