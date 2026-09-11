#include "cluster.h"
#include <stdint.h>
void convolve2d_rep0_hw_bridge(int input_image[262144], int filter[9], int output_image[262144]) {
   convolve2d_rep0_hw(input_image, filter, output_image);
}
