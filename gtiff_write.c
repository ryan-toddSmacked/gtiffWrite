#include "gtiff_write.h"

#include "env/include/xtiffio.h"
#include "env/include/geotiffio.h"

#include <stdlib.h>



static int __gtiffWrite(const char* filename, const void* data, size_t size, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count)
{
    /* Attempt to open the file for writing */
    TIFF* tiff = XTIFFOpen(filename, "w");
    uint8_t* img = (uint8_t*)data;

    if (tiff == NULL)
    {
        fprintf(stderr, "Failed to open file for writing: %s\n", filename);
        return 0;
    }


    /* Get geotiff writing ready */
    GTIF* gtif = GTIFNew(tiff);

    if (gtif == NULL)
    {
        fprintf(stderr, "Failed to create GTIF structure\n");
        /* Close TIFF file, return 0 */
        TIFFClose(tiff);
        return 0;
    }


    /* Set the TIFF tags */
    /* Make sure to cast data to appropriate primitive type */
    TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, (uint32_t)width);
    TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, (uint32_t)height);
    TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, (uint16_t)bands);
    TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, 8 * size); /* This specifies the memcpy size in TIFFWriteScanLine */
    TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    /* Check if gray scale or RGB */
    if (bands == 1)
    {
        TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    }
    else if (bands == 3)
    {
        TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
    }
    else
    {
        fprintf(stderr, "Unsupported number of bands: %zu\n", bands);
        /* Close TIFF file, return 0 */
        TIFFClose(tiff);
        return 0;
    }

    /* Write the image data */
    for (size_t i = 0; i < height; i++)
    {
        if (TIFFWriteScanline(tiff, img + i * width * bands * size, i, 0) < 0)
        {
            fprintf(stderr, "Failed to write scanline: %zu\n", i);
            /* Close TIFF file, return 0 */
            TIFFClose(tiff);
            return 0;
        }
    }

    /* Write the GCPs, these should be stored in the tiff model tiepoint tag */
    if (gcps != NULL && gcps_count > 0)
    {
        /* Allocate memory for the tiepoints */
        double* tiepoints = (double*)malloc(sizeof(double) * 6 * gcps_count);

        /* Loop over the gcps and store them in the tiepoints array */
        for (size_t i = 0; i < gcps_count; i++)
        {
            tiepoints[6 * i + 0] = gcps[i].x;
            tiepoints[6 * i + 1] = gcps[i].y;
            tiepoints[6 * i + 2] = 0.0;
            tiepoints[6 * i + 3] = gcps[i].lon;
            tiepoints[6 * i + 4] = gcps[i].lat;
            tiepoints[6 * i + 5] = 0.0;
        }

        /* Write the tiepoints to the TIFF file */
        TIFFSetField(tiff, TIFFTAG_GEOTIEPOINTS, 6 * gcps_count, tiepoints);

        /* Free the tiepoints array */
        free(tiepoints);
    }

    /* Write the geotiff tags */
    /* Specify WGS84 GCPs are stored */
    GTIFKeySet(gtif, GTModelTypeGeoKey, TYPE_SHORT, 1, ModelTypeGeographic);
    /* Specify WGS84 datum */
    GTIFKeySet(gtif, GeogGeodeticDatumGeoKey, TYPE_SHORT, 1, Datum_WGS84);

    GTIFKeySet(gtif, GeogCitationGeoKey, TYPE_ASCII, 7, "WGS 84");
    GTIFKeySet(gtif, GeogAngularUnitsGeoKey, TYPE_SHORT, 1, 9102);
    GTIFKeySet(gtif, GeogSemiMajorAxisGeoKey, TYPE_DOUBLE, 1, 6378137.0);
    GTIFKeySet(gtif, GeogInvFlatteningGeoKey, TYPE_DOUBLE, 1, 298.257223563);

    /* Close the geotiff file */
    GTIFWriteKeys(gtif);
    GTIFFree(gtif);

    /* Close the TIFF file */
    TIFFClose(tiff);

    return 1;

}



int gtiffWrite_u8(const char* filename, const uint8_t* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count)
{
    return __gtiffWrite(filename, img, sizeof(uint8_t), width, height, bands, gcps, gcps_count);
}

int gtiffWrite_u16(const char* filename, const uint16_t* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count)
{
    return __gtiffWrite(filename, img, sizeof(uint16_t), width, height, bands, gcps, gcps_count);
}

int gtiffWrite_f32(const char* filename, const float* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count)
{
    return __gtiffWrite(filename, img, sizeof(float), width, height, bands, gcps, gcps_count);
}

int gtiffWrite_f64(const char* filename, const double* img, size_t width, size_t height, size_t bands, const gcp_t* gcps, size_t gcps_count)
{
    return __gtiffWrite(filename, img, sizeof(double), width, height, bands, gcps, gcps_count);
}



