#ifndef __PPM_H__
#define __PPM_H__

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
    int            height);  ///< [in] Image height

#endif // __PPM_H__
