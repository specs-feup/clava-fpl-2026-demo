#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdint.h>
using namespace std;
using namespace std::chrono;
// Universal params
// #define FORCE_EXTERNAL
void rgbToGrayscale(int input_image[512][1536], int output_image[512][512])
{
    for (int i = 0; i < 512; i++)
    {
        int jj = 0;
        for (int j = 0; j < 512; j++)
        {
            int r = input_image[i][jj];
            int g = input_image[i][jj + 1];
            int b = input_image[i][jj + 2];
            jj += 3;
            float gray = 0.299 * r + 0.587 * g + 0.114 * b;
            output_image[i][j] = (int)floor(gray);
        }
    }
}

void convolve2d(int input_image[512][512], int filter[3][3], int output_image[512][512])
{
    int i;
    int j;
    int c;
    int r;
    int normal_factor;
    int sum;
    int dead_rows;
    int dead_cols;
    dead_rows = 3 / 2;
    dead_cols = 3 / 2;
    normal_factor = 0;
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            normal_factor += abs(filter[r][c]);
        }
    }
    if (normal_factor == 0)
        normal_factor = 1;
    for (r = 0; r < 512 - 3 + 1; r++)
    {
        for (c = 0; c < 512 - 3 + 1; c++)
        {
            sum = 0;
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    sum += input_image[(r + i)][(c + j)] * filter[i][j];
                }
            }
            output_image[(r + dead_rows)][(c + dead_cols)] = (sum / normal_factor);
        }
    }
}

void combthreshold(int image_gray[512][512], int temp_buf[512][512], int output[512][512])
{
    int i, j;
    int temp1;
    int temp2;
    int temp3;
    for (i = 0; i < 512; i++)
    {
        for (j = 0; j < 512; ++j)
        {
            temp1 = abs(image_gray[i][j]);
            temp2 = abs(temp_buf[i][j]);
            temp3 = (temp1 > temp2) ? temp1 : temp2;
            output[i][j] = (temp3 > 50) ? 255 : 0;
        }
    }
}

void edge_detect_sw(int image_rgb[512][1536], int image_gray[512][512], int temp_buf[512][512], int filter[3][3],
                    int output[512][512])
{
    rgbToGrayscale(image_rgb, image_gray);
    filter[0][0] = 1;
    filter[0][1] = 2;
    filter[0][2] = 1;
    filter[1][0] = 2;
    filter[1][1] = 4;
    filter[1][2] = 2;
    filter[2][0] = 1;
    filter[2][1] = 2;
    filter[2][2] = 1;
    convolve2d(image_gray, filter, output);
    filter[0][0] = 1;
    filter[0][1] = 0;
    filter[0][2] = -1;
    filter[1][0] = 2;
    filter[1][1] = 0;
    filter[1][2] = -2;
    filter[2][0] = 1;
    filter[2][1] = 0;
    filter[2][2] = -1;
    convolve2d(output, filter, image_gray);
    filter[0][0] = 1;
    filter[0][1] = 2;
    filter[0][2] = 1;
    filter[1][0] = 0;
    filter[1][1] = 0;
    filter[1][2] = 0;
    filter[2][0] = -1;
    filter[2][1] = -2;
    filter[2][2] = -1;
    convolve2d(output, filter, temp_buf);
    combthreshold(image_gray, temp_buf, output);
}

void edge_detect_hw_bridge(int image_rgb[512][1536], int image_gray[512][512], int temp_buf[512][512], int filter[3][3],
                           int output[512][512]);
int main()
{
    int image_rgb[512][1536] = {0};
    // #include "img_512_512.dat"
    int image_gray[512][512] = {0};
    int temp_buf[512][512] = {0};
    int filter[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int output[512][512] = {0};
    auto start = high_resolution_clock::now();
    // Selector between SW and HW bridge calls based on OFFLOAD getenv variable
    if (getenv("OFFLOAD") != NULL)
    {
        edge_detect_hw_bridge(image_rgb, image_gray, temp_buf, filter, output);
    }
    else
    {
        edge_detect_sw(image_rgb, image_gray, temp_buf, filter, output);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Duration: " << duration.count() << std::endl;
    int actual = 0;
    int real = 2455650;
    for (int i = 0; i < 512; i++)
    {
        for (int j = 0; j < 512; j++)
        {
            actual += output[i][j];
        }
    }
    cout << "Checksum: real = " << real << ", actual = " << actual << (real == actual ? " (VERIFIED)" : " (ERROR)")
         << endl;

    return 0;
}
