#include "cluster.h"
#include <stdint.h>
void cluster_rgbToGrayscale(int input_image[786432], int output_image[262144]);
void cluster_edge_detect_out0(int filter[9]);
void cluster_convolve2d_rep0(int input_image[262144], int filter[9],
                             int output_image[262144]);
void cluster_edge_detect_out1(int filter[9]);
void cluster_convolve2d_rep1(int input_image[262144], int filter[9],
                             int output_image[262144]);
void cluster_edge_detect_out2(int filter[9]);
void cluster_convolve2d_rep2(int input_image[262144], int filter[9],
                             int output_image[262144]);
void cluster_combthreshold(int image_gray[262144], int temp_buf[262144],
                           int output[262144]);
void edge_detect_hw(int image_gray[262144], int output[262144]) {
  int filter[9];
  int temp_buf[262144];
  cluster_edge_detect_out0(filter);
  cluster_convolve2d_rep0(image_gray, filter, output);
  cluster_edge_detect_out1(filter);
  cluster_convolve2d_rep1(output, filter, image_gray);
  cluster_edge_detect_out2(filter);
  cluster_convolve2d_rep2(output, filter, temp_buf);
  cluster_combthreshold(image_gray, temp_buf, output);
}

void cluster_combthreshold(int image_gray[262144], int temp_buf[262144],
                           int output[262144]) {
  int i;
  int j;
  int temp1;
  int temp2;
  int temp3;
  for (i = 0; i < 512; i++) {
    for (j = 0; j < 512; ++j) {
      temp1 = abs(image_gray[i * 512 + j]);
      temp2 = abs(temp_buf[i * 512 + j]);
      temp3 = (temp1 > temp2) ? temp1 : temp2;
      output[i * 512 + j] = (temp3 > 50) ? 255 : 0;
    }
  }
}

void cluster_convolve2d_rep2(int input_image[262144], int filter[9],
                             int output_image[262144]) {
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
  for (r = 0; r < 3; r++) {
    for (c = 0; c < 3; c++) {
      int _d0_0;
      int _d0_1;
      _d0_0 = abs(filter[r * 3 + c]);
      _d0_1 = normal_factor + _d0_0;
      normal_factor = _d0_1;
    }
  }
  decomp_0 = 0;
  if (decomp_0) {
    normal_factor = 1;
  }
  for (r = 0; r < 510; r++) {
    for (c = 0; c < 510; c++) {
      sum = 0;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          sum = sum +
                input_image[((r + i)) * 512 + ((c + j))] * filter[i * 3 + j];
        }
      }
      output_image[((r + dead_rows)) * 512 + ((c + dead_cols))] =
          (sum / normal_factor);
    }
  }
}

void cluster_edge_detect_out2(int filter[9]) {
  filter[0] = 1;
  filter[1] = 2;
  filter[2] = 1;
  filter[3] = 0;
  filter[4] = 0;
  filter[5] = 0;
  filter[6] = -1;
  filter[7] = -2;
  filter[8] = -1;
}

void cluster_convolve2d_rep1(int input_image[262144], int filter[9],
                             int output_image[262144]) {
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
  for (r = 0; r < 3; r++) {
    for (c = 0; c < 3; c++) {
      int _d0_0;
      int _d0_1;
      _d0_0 = abs(filter[r * 3 + c]);
      _d0_1 = normal_factor + _d0_0;
      normal_factor = _d0_1;
    }
  }
  decomp_0 = 0;
  if (decomp_0) {
    normal_factor = 1;
  }
  for (r = 0; r < 510; r++) {
    for (c = 0; c < 510; c++) {
      sum = 0;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          sum = sum +
                input_image[((r + i)) * 512 + ((c + j))] * filter[i * 3 + j];
        }
      }
      output_image[((r + dead_rows)) * 512 + ((c + dead_cols))] =
          (sum / normal_factor);
    }
  }
}

void cluster_edge_detect_out1(int filter[9]) {
  filter[0] = 1;
  filter[1] = 0;
  filter[2] = -1;
  filter[3] = 2;
  filter[4] = 0;
  filter[5] = -2;
  filter[6] = 1;
  filter[7] = 0;
  filter[8] = -1;
}

void cluster_convolve2d_rep0(int input_image[262144], int filter[9],
                             int output_image[262144]) {
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
  for (r = 0; r < 3; r++) {
    for (c = 0; c < 3; c++) {
      int _d0_0;
      int _d0_1;
      _d0_0 = abs(filter[r * 3 + c]);
      _d0_1 = normal_factor + _d0_0;
      normal_factor = _d0_1;
    }
  }
  decomp_0 = 0;
  if (decomp_0) {
    normal_factor = 1;
  }
  for (r = 0; r < 510; r++) {
    for (c = 0; c < 510; c++) {
      sum = 0;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          sum = sum +
                input_image[((r + i)) * 512 + ((c + j))] * filter[i * 3 + j];
        }
      }
      output_image[((r + dead_rows)) * 512 + ((c + dead_cols))] =
          (sum / normal_factor);
    }
  }
}

void cluster_edge_detect_out0(int filter[9]) {
  filter[0] = 1;
  filter[1] = 2;
  filter[2] = 1;
  filter[3] = 2;
  filter[4] = 4;
  filter[5] = 2;
  filter[6] = 1;
  filter[7] = 2;
  filter[8] = 1;
}

void cluster_rgbToGrayscale(int input_image[786432], int output_image[262144]) {
  for (int i = 0; i < 512; i++) {
    int jj;
    jj = 0;
    for (int j = 0; j < 512; j++) {
      int r;
      int g;
      int b;
      float gray;
      r = input_image[i * 1536 + jj];
      g = input_image[i * 1536 + (jj + 1)];
      b = input_image[i * 1536 + (jj + 2)];
      jj = jj + 3;
      gray = 0.299 * r + 0.587 * g + 0.114 * b;
      output_image[i * 512 + j] = (int)floor(gray);
    }
  }
}
