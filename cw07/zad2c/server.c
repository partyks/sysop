#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <mqueue.h>
#include "defs.h"

// nie mozna sie wylogowac!

mqd_t queue_id;
int limit;
int out;
int ids_size=0;

/**
* pomocnicza - sprzata kolejke i plik (nie gromadza sie komunikaty przypadkiem)
*/
void closeQueue(char* name,mqd_t queue_id){
    mq_close(queue_id);
    mq_unlink(name);
}


/**
* zestaw funkcji porzadkujacych
*/
void cleanup(){
    closeQueue(QUEUENAME,queue_id);
}
int flag=1;
void breakloop(int i){
    flag=0;
}

char buff[512];
int persist_it(message msg){
    time_t t;
    time(&t);
    sprintf(buff,"%s\t%s\n%s\n\n",ctime(&t),msg.who,msg.what);
    int thissize=strlen(buff);
    if(limit-thissize<0)return 0;
    write(out,buff,strlen(buff));
    limit-=thissize;
    return 1;
}

int main(int argc, char** argv){
    if(argc<2){
        printf("usage: [file length limit in characters]");
        return 1;
    }
    limit=atoi(argv[1]);

    /** otwieramy arbitralnie zadana kolejke */
    mqd_t queue_id = createQueue(QUEUENAME,sizeof(message));
    if(queue_id<0){
        printf("SERVER not created\n");
        perror(NULL);
        exit(1);
    }
    printf("SERVER %s at %d\n",QUEUENAME,queue_id);
    out=open("tmp/LOG.log",O_WRONLY|O_CREAT,S_IRUSR | S_IWUSR|S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(out<0){
        printf("LOG not created\n");
        perror(NULL);
        exit(1);
    }

    ids_size=0;
    signal(SIGINT,breakloop);
    int rc;
    while(flag){
        /** odbior komunikatu nt. pojawienia sie klienta
        *   nie czekamy, musimy jeszcze obslugiwac transfer wiadomosci
        *   klienta notyfikujemy przez sygnal - jego rodzaj oznacza sukces/porazka
        */
        message msg;
        rc = mq_receive(queue_id, (char*)(&msg), sizeof(msg), NULL);
        if(rc>=0){
            int ok = persist_it(msg);
            printf("\nRECIEVED:\t%s\n%s\n",msg.who,msg.what);
            if(!ok)printf("BUT NOT SAVED\n");
            printf("pid: %d\n",msg.pid);
            if(ok)kill(msg.pid,SIGUSR1);else kill(msg.pid,SIGUSR2);
            printf("LIMIT=%d\n",limit);
        }
    }
    cleanup();
    return 0;
}
