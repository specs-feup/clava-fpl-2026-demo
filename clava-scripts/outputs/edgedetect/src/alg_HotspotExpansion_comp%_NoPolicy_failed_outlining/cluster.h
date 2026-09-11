#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdint.h>
void edge_detect_hw(int image_rgb[512][1536], int image_gray[512][512], int temp_buf[512][512], int filter[3][3],
                    int output[512][512]);
#endif
