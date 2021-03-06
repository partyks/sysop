#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>


int licznik = 0;

void fun1(int x) {
    printf(" ->  Odbieram zadany sygnał...\n");
    licznik++;
}

void fun2(int x) {
    printf(" -> W sumie odebrano sygnalow: %d\n", licznik);
    int parent = getppid();
    int l=licznik;
    while(l--){
        printf(" -> Zwracam zadany sygnał...\n");
        kill(parent,SIGRTMAX);
        sleep(2);
    }
    printf(" -> Wysyłam potwierdzenie\n");
    kill(parent,SIGRTMIN);
    exit(licznik);
}

int main() {
    signal(SIGRTMAX,fun1);
    signal(SIGRTMIN,fun2);
    while(1){}
    return -100;
}
