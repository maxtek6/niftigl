#include "niftigl.h"

#ifndef NIFTIGL_INTERNAL_API
#include <nifti1_io.h>
static int niftigl_load_slices(const char *path, nifti_image **image);
static int niftigl_count_slices(nifti_image *image, size_t *count);
static int niftigl_upload_slices(nifti_image *image, GLuint *slices, size_t count);
#endif

int niftigl_stage(const char *path, GLuint **slices, size_t *count)
{
    nifti_image *image;
    size_t slice_count;
    GLuint *slice_data;

    image = NULL;

    niftigl_load_slices(path, &image);
    niftigl_count_slices(image, &slice_count);
    slice_data = calloc(slice_count, sizeof(GLuint));
    niftigl_upload_slices(image, slice_data, slice_count);

    nifti_image_free(image);
    return 0;
}

int niftigl_load_slices(const char *path, nifti_image **image)
{
    *image = nifti_image_read(path, 1);
    return 0;
}

int niftigl_count_slices(nifti_image *image, size_t *count)
{
    *count = image->nz;
    return 0;
}

int niftigl_upload_slices(nifti_image *image, GLuint *slices, size_t count)
{
    GLint texture;
    glGenTextures(count, slices);
    for (size_t slice_index = 0; slice_index < count; slice_index++)
    {
        texture = *(slices + slice_index);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->nx, image->ny, 0, GL_LUMINANCE, GL_FLOAT, image->data + slice_index * image->nx * image->ny);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
