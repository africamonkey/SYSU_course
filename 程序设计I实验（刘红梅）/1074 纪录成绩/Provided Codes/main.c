#include <stdio.h>
#include <stdlib.h>
void input(double** score, int nStuNum, int nCourseNum) {
    int i, j;
    for (i = 0; i < nStuNum; i++) {
        for (j = 0; j < nCourseNum; j++) {
            scanf("%lf", &score[i][j]);
        }
    }
}

void output(double **score, int nStuNum, double *avg);

void average(double** score, int nStuNum, int nCourseNum, double* avg);

int main() {
    double **score, *avg;
    int nStuNum, nCourseNum, i;
    scanf("%d%d", &nStuNum, &nCourseNum);
    avg = (double*)malloc(sizeof(*avg) * nStuNum);
    score = (double**)malloc(sizeof(*score) * nStuNum);
    for (i = 0; i < nStuNum; i++)
        score[i] = (double*)malloc(sizeof(**score) * nCourseNum);
    input(score, nStuNum, nCourseNum);
    average(score, nStuNum, nCourseNum, avg);
    output(score, nStuNum, avg);
    return 0;
}
