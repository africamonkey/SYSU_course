#include "process.h"
#include "forkio.h"

char str[55] = "129djwqhdsajd128dw9i39ie93i8494urjoiew98kdkd";

int LetterNr = 0;

void forkmain() {
	int pid, i, j;
	int ch;
	pid = fork();
	if (pid == -1) puts_no_new_line("error in fork!\n");
	if (pid) {
		puts_no_new_line("child pid=");
		printint(pid);
		ch = wait();
		puts_no_new_line("return val=");
		printint(ch);
		for (i = 0; str[i]; ++i);
		puts_no_new_line("tot len=");
		printint(i);
		exit(0);
	} else {
		j = 0;
		for (i = 0; str[i]; ++i)
			if (str[i] >= 'a' && str[i] <= 'z')
				++ j;
		puts_no_new_line("alpha len=");
		printint(j);
		exit(0);
	}
}