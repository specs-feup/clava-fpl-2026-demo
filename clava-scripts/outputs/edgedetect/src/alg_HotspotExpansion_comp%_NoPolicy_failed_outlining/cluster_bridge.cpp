#include "cluster.h"
#include <stdint.h>
void edge_detect_hw_bridge(int image_rgb[512][1536], int image_gray[512][512], int temp_buf[512][512], int filter[3][3],
                           int output[512][512])
{
    edge_detect_hw(image_rgb, image_gray, temp_buf, filter, output);
}
