#include "stdlib.h"
#include "stdio.h"
#include "sync.h"

int bankbalance = 1000;

void syncmain() {
	int pid, sem_id;
	int t, i;
	sem_id = getSem(1);
	if (sem_id >= 0 && sem_id < 64) {
		puts_no_new_line("Applying signal: sem_id = ");
		printint(sem_id);
	} else {
		puts("error while applying signal");
	}
	pid = fork();
	if (pid == -1) {
		puts("error in fork!");
		exit(-1);
	}
	if (pid) {
		puts("father process: fork OK");
		sleep(2);
		puts("father process: sleep OK");
		while (1) {
			P(sem_id);
			t = bankbalance;
			sleep(3);
			t = t + 10;
			sleep(2);
			bankbalance = t;
			puts_no_new_line("+10, bankbalance = ");
			printint(bankbalance);
			V(sem_id);
		}
		exit(0);
	} else {
		puts("child process: fork OK");
		sleep(2);
		puts("child process: sleep OK");
		while (1) {
			P(sem_id);
			t = bankbalance;
			sleep(3);
			t = t - 20;
			sleep(2);
			if (t >= 0) {
				bankbalance = t;
				puts_no_new_line("-20, bankbalance = ");
				printint(bankbalance);
			} else {
				puts("money not enough!");
			}
			V(sem_id);
		}
		exit(0);
	}
}