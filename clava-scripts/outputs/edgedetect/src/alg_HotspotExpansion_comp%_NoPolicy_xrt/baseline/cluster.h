#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <chrono>
#include <iostream>
#include <stdint.h>
void edge_detect_hw(int image_rgb[786432], int image_gray[262144], int temp_buf[262144], int filter[9], int output[262144]);
#endif
