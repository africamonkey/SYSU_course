#include <stdio.h>
#include "linkedList.h"

void print() {
	int i;
	for (i = 0; i < size; ++i) {
		printf("%d ", get(i));
	}
	printf("\n");
}


int main() {
	head = NULL;
	size = 0;
	int n, i, position, value;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d%d", &position, &value);
		if (insert(position, value)) {
			print();
		} else {
			printf("position is not valid\n");
		}
	}
	clear();
	return 0;
}