
#include <stdio.h>
#include <math.h> // for floor and log2
#include "buddy_allocator.h"
#include "bit_map.h"

int levelIdx(size_t idx){
  if (!idx) return 0;
  if (idx==1) return 1;
  return (int)floor(log2(idx+1));
};

int buddyIdx(int idx) {
  if (idx & 0x1) {
    return idx - 1;
  }
  return idx + 1;
}

int parentIdx(int idx) { 
     return floor((idx-1)/2);
}
int startIdx(int idx) {(int idx){
  return (idx-((1<<levelIdx(idx))-1));
}

int firstIdx(int lvl){
  return (1 << lvl) - 1;

}


void print_bitmap(BitMap* bit_map){
  for (int i=0; i<bit_map->num_bits; i++){
    if (levelIdx(i)!=levelIdx(i+1)){
      printf("%d ", BitMap_bit(bit_map,i));
      printf("\n");
    }
    else{ 
     printf("%d ", BitMap_bit(bit_map,i));
    }
  }
  printf("\n");
  }