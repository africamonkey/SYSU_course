 int* doubleCapacity(int* list, int size, int addSize) {
   int *ret = malloc(sizeof(int) * (size + addSize));
   for (int i=0;i<size;i++) ret[i] = list[i];
   for (int i=size;i<size+addSize;i++) ret[i] = 0;
   return ret;
 }