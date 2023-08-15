

#include "gtiff_write.h"
#include <stdio.h>


#define M 200
#define N 100

#include <stdlib.h>


int main()
{


    uint8_t* img = (uint8_t*)malloc(M*N*sizeof(uint8_t));
    uint16_t* img2 = (uint16_t*)malloc(M*N*sizeof(uint16_t));
    float* img3 = (float*)malloc(M*N*sizeof(float));
    double* img4 = (double*)malloc(M*N*sizeof(double));
    for(int i=0; i<M*N; i++)
    {
        img2[i] = 12000; // Lighter image
        img[i] = 0; // Black image
        img3[i] = 0.7; // Gray image
        img4[i] = 1.0; // White image
    }

    gcp_t gcps[4];
    gcp_t gcps1[4];
    gcp_t gcps2[4];
    gcp_t gcps3[4];

    gcps[0].x = 0;
    gcps[0].y = 0;
    gcps[0].lon = 0;
    gcps[0].lat = 0;

    gcps[1].x = N;
    gcps[1].y = 0;
    gcps[1].lon = 1;
    gcps[1].lat = 0;

    gcps[2].x = N;
    gcps[2].y = M;
    gcps[2].lon = 1;
    gcps[2].lat = 1;

    gcps[3].x = 0;
    gcps[3].y = M;
    gcps[3].lon = 0;
    gcps[3].lat = 1;

    gcps1[0].x = 0;
    gcps1[0].y = 0;
    gcps1[0].lon = 1;
    gcps1[0].lat = 1;

    gcps1[1].x = N;
    gcps1[1].y = 0;
    gcps1[1].lon = 2;
    gcps1[1].lat = 1;

    gcps1[2].x = N;
    gcps1[2].y = M;
    gcps1[2].lon = 2;
    gcps1[2].lat = 2;

    gcps1[3].x = 0;
    gcps1[3].y = M;
    gcps1[3].lon = 1;
    gcps1[3].lat = 2;

    gcps2[0].x = 0;
    gcps2[0].y = 0;
    gcps2[0].lon = 2;
    gcps2[0].lat = 2;

    gcps2[1].x = N;
    gcps2[1].y = 0;
    gcps2[1].lon = 3;
    gcps2[1].lat = 2;

    gcps2[2].x = N;
    gcps2[2].y = M;
    gcps2[2].lon = 3;
    gcps2[2].lat = 3;

    gcps2[3].x = 0;
    gcps2[3].y = M;
    gcps2[3].lon = 2;
    gcps2[3].lat = 3;

    gcps3[0].x = 0;
    gcps3[0].y = 0;
    gcps3[0].lon = 3;
    gcps3[0].lat = 3;

    gcps3[1].x = N;
    gcps3[1].y = 0;
    gcps3[1].lon = 4;
    gcps3[1].lat = 3;

    gcps3[2].x = N;
    gcps3[2].y = M;
    gcps3[2].lon = 4;
    gcps3[2].lat = 4;

    gcps3[3].x = 0;
    gcps3[3].y = M;
    gcps3[3].lon = 3;
    gcps3[3].lat = 4;



    const char* filename = "test.tif";
    const char* filename2 = "test2.tif";
    const char* filename3 = "test3.tif";
    const char* filename4 = "test4.tif";
    gtiffWrite_u8(filename, img, N, M, 1, gcps, 4);
    gtiffWrite_u16(filename2, img2, N, M, 1, gcps1, 4);
    gtiffWrite_f32(filename3, img3, N, M, 1, gcps2, 4);
    gtiffWrite_f64(filename4, img4, N, M, 1, gcps3, 4);


    free(img);
    free(img2);
    free(img3);
    free(img4);


    return 0;
}

