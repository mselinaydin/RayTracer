#include <cstdio>
#include "ppm.h"

/**
***************************************************************************************
* writePPM
*
* @brief
*	  Saves the given image in binary PPM file format. For details of this format
*     see, http://netpbm.sourceforge.net/doc/ppm.html. The pixel data is assumed
*     to be a contiguous array of pixels. The first pixel corresponds to the top-left
*     corner of the image. Each pixel must have three color components stored in
*     RGB order.
*
* @return
*	  true if successful, false otherwise
**************************************************************************************
*/
bool writePPM(
    const char*    filename, ///< [in] Output file name
    unsigned char* data,     ///< [in] Pixel data
    int            width,    ///< [in] Image width
    int            height)   ///< [in] Image height
{
    // Check the sanity of the inputs

    if (!data || width <= 0 || height <= 0)
    {
        return false;
    }

    // Open the output file

    FILE* fp = fopen(filename, "wb");

    if (!fp)
    {
        return false;
    }

    // Write the PPM header

    fprintf(fp, "P6\n");          // magic number
    fprintf(fp, "%d\n", width);   // image width
    fprintf(fp, "%d\n", height);  // image height
    fprintf(fp, "255\n", height); // maximum color value

    // Write the scanline data from top to bottom

    unsigned char* ptr = data;
    size_t scanlineWidth = width * 3;

    for (int y = 0; y < height; ++y)
    {
        fwrite(ptr, scanlineWidth, 1, fp);
        ptr += scanlineWidth;
    }

    // Close the file stream

    fclose(fp);

    return true;
}
