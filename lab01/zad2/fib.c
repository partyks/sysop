#include <stdlib.h>
#include <stdio.h>

unsigned long fibo(int num){
    if(num<2){
        return num;
    }
    return fibo(num-1)+fibo(num-2);
}


int main(int argc, char* argv[]){
    if(argc<2){
        printf(" Podaj ktory wyraz w argumencie! ");
        return 1;
    }
    fibo(atoi(argv[1]));
    return 0;
}
