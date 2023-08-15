#ifndef __GTIFF_WRITE_C_DECL_H__
#define __GTIFF_WRITE_C_DECL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Model Tie Point Tag struct */
typedef struct GCPStruct
{
    double x;   /* Pixel/line location in georeferenced space */
    double y;   /* Pixel/line location in georeferenced space */
    double z;   /* 0.0 */
    double lon; /* Georeferenced location in user selected projection */
    double lat; /* Georeferenced location in user selected projection */
    double alt; /* 0.0 */
} gcp_t;

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Write a GeoTIFF file
 * 
 * @param filename Full path on disk to file to write, overwrites existing file
 * @param img ROW-MAJOR image data to write, size is width*height*bands, values range from [0, 255]
 * @param width Width of image in pixels
 * @param height Height of image in pixels
 * @param bands Number of bands in image, 1 for grayscale, 3 for RGB
 * @param gcps Geo-referenced WGS84 ground control points, at least 3 is recommended
 * @param gcps_count Number of ground control points
 * @return int (0) on failure, (1) on success
 */
int gtiffWrite_u8(const char* filename, const uint8_t* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count);


/**
 * @brief Write a GeoTIFF file
 * 
 * @param filename Full path on disk to file to write, overwrites existing file
 * @param img ROW-MAJOR image data to write, size is width*height*bands, values range from [0, 65535]
 * @param width Width of image in pixels
 * @param height Height of image in pixels
 * @param bands Number of bands in image, 1 for grayscale, 3 for RGB
 * @param gcps Geo-referenced WGS84 ground control points, at least 3 is recommended
 * @param gcps_count Number of ground control points
 * @return int (0) on failure, (1) on success
 */
int gtiffWrite_u16(const char* filename, const uint16_t* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count);


/**
 * @brief Write a GeoTIFF file
 * 
 * @param filename Full path on disk to file to write, overwrites existing file
 * @param img ROW-MAJOR image data to write, size is width*height*bands, values range from [0, 1]
 * @param width Width of image in pixels
 * @param height Height of image in pixels
 * @param bands Number of bands in image, 1 for grayscale, 3 for RGB
 * @param gcps Geo-referenced WGS84 ground control points, at least 3 is recommended
 * @param gcps_count Number of ground control points
 * @return int (0) on failure, (1) on success
 */
int gtiffWrite_f32(const char* filename, const float* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count);


/**
 * @brief Write a GeoTIFF file
 * 
 * @param filename Full path on disk to file to write, overwrites existing file
 * @param img ROW-MAJOR image data to write, size is width*height*bands, values range from [0, 1]
 * @param width Width of image in pixels
 * @param height Height of image in pixels
 * @param bands Number of bands in image, 1 for grayscale, 3 for RGB
 * @param gcps Geo-referenced WGS84 ground control points, at least 3 is recommended
 * @param gcps_count Number of ground control points
 * @return int (0) on failure, (1) on success
 */
int gtiffWrite_f64(const char* filename, const double* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count);

#ifdef __cplusplus
}
#endif

#endif /* __GTIFF_WRITE_C_DECL_H__ */
