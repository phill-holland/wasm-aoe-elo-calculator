#include <iostream> 
#include <emscripten/emscripten.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE int reversenumber(int n) { 
   int reverse=0, rem; 
   while(n!=0) { 
      rem=n%10; reverse=reverse*10+rem; n/=10; 
   } 
   return reverse; 
}

/*
int main()//int argc, char *argv[])
{ 
    return 0;
}

*/