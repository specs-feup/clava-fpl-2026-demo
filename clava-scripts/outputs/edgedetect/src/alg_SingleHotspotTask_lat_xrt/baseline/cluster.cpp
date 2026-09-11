#include "cluster.h"
#include <stdint.h>
void convolve2d_rep0_hw(int input_image[262144], int filter[9], int output_image[262144]) {
   int i;
   int j;
   int c;
   int r;
   int normal_factor;
   int sum;
   int dead_rows;
   int dead_cols;
   bool decomp_0;
   dead_rows = 1;
   dead_cols = 1;
   normal_factor = 0;
   for(r = 0; r < 3; r++) {
      for(c = 0; c < 3; c++) {
         int _d0_0;
         int _d0_1;
         _d0_0 = abs(filter[r * 3 + c]);
         _d0_1 = normal_factor + _d0_0;
         normal_factor = _d0_1;
      }
   }
   decomp_0 = 0;
   if(decomp_0) {
      normal_factor = 1;
   }
   for(r = 0; r < 510; r++) {
      for(c = 0; c < 510; c++) {
         sum = 0;
         for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
               sum = sum + input_image[((r + i)) * 512 + ((c + j))] * filter[i * 3 + j];
            }
         }
         output_image[((r + dead_rows)) * 512 + ((c + dead_cols))] = (sum / normal_factor);
      }
   }
}
