#include "niftigl.h"

#include <nifti1_io.h>

int niftigl_stage(const char *path, GLuint **slices, size_t *count)
{
    nifti_image *image;

    image = nifti_image_read(path, 1);

    *count = image->nz;



    return 0;
}