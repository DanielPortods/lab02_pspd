#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

double calc_time(__time_t sec_ini, __time_t sec_end, __suseconds_t usec_ini, __suseconds_t usec_end){
	return (sec_end + (double) usec_end/1000000) - (sec_ini + (double) usec_ini/1000000);
}

int main (int argc, char *argv[]){

	if (argc < 2) {
		printf ("usage: %s fileName.txt\n", argv[0]);
		return 1;
	}

	FILE *names = fopen(argv[1], "r");

  	if(!names){
        printf("Can't onpen the file: %s\n", argv[1]);
  		return 1;
	}

    fseek(names, 0, SEEK_SET);
    struct timeval total_ini, total_end;

    int n = 0, n_l_six = 0, n_g_six = 0, pos_ant = 0;

    gettimeofday(&total_ini, NULL);
    while (!feof(names)){        
        while(!feof(names) && fgetc(names) != ' ');

        int size = ftell(names) - pos_ant - 1;
        
        if(!size) continue;
        else if(size < 6) n_l_six++;
        else if(size < 10) n_g_six++;

        n++;
        pos_ant = ftell(names);
    }
    gettimeofday(&total_end, NULL);

    double time = calc_time(total_ini.tv_sec, total_end.tv_sec, total_ini.tv_usec, total_end.tv_usec);
        
    printf("[%.8lf s] %d palavras: %d menores que 6 bytes e %d entre 6 e 10 bytes.\n", time, n, n_l_six, n_g_six);

    fclose(names);

    return 0;
}