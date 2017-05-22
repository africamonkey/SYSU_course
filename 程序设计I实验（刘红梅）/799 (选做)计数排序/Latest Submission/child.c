void set(unsigned int* bitmap, unsigned int index) {
  bitmap[index / 32] |= 1u << (index % 32);
}
 
int get(unsigned int* bitmap, unsigned int index) {
  return (bitmap[index / 32] >> (index % 32)) & 1;
}