#include "cluster.h"
#include <stdint.h>
void edge_detect_hw_bridge(int image_rgb[786432], int image_gray[262144], int temp_buf[262144], int filter[9], int output[262144]) {
   edge_detect_hw(image_rgb, image_gray, temp_buf, filter, output);
}
