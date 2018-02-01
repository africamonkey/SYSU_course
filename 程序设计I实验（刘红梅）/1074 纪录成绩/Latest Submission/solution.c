 void average(double** score, int nStuNum, int nCourseNum, double* avg) {
   for (int i=0;i<nStuNum;i++) {
     avg[i] = 0;
     for (int j=0;j<nCourseNum;j++)
       	avg[i] = avg[i] + score[i][j];
     avg[i] /= nCourseNum;
   }
 }

void output(double **score, int nStuNum, double *avg) {
  for (int i=0;i<nStuNum;i++) printf("%d %.2lf\n", i+1, (double)avg[i]);
  for (int i=0;i<nStuNum;i++) free(score[i]);
  free(score);
  free(avg);
  int *dd = new int[4];
  int *ee = new int[5];
}