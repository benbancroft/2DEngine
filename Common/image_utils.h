#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include "platform/platform_gl.h"

namespace ImageUtils
{

    typedef struct {
        unsigned int width;
        unsigned int height;
        unsigned long size;
        const GLenum gl_color_format;
        const void* data;
    } RawImageData;

    /* Returns the decoded image data, or aborts if there's an error during decoding. */
    RawImageData get_raw_image_data_from_png(const unsigned char* png_data, unsigned int png_data_size);
    void release_raw_image_data(const RawImageData* data);

}

#endif
