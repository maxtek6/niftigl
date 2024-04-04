#ifndef NIFTIGL_H
#define NIFTIGL_H

#ifdef _WIN32
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#define CLAMP_TO_EDGE GL_CLAMP
#else
#include <GL/gl.h>
#include <GL/glx.h>
#define CLAMP_TO_EDGE GL_CLAMP_TO_EDGE
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef NIFTIGL_INTERNAL_API
#include <nifti1_io.h>
int niftigl_load_slices(const char *path, nifti_image **image);
int niftigl_count_slices(nifti_image *image, size_t *count);
int niftigl_upload_slices(nifti_image *image, GLuint *slices, size_t count);
#endif

int niftigl_stage(const char *path, GLuint **slices, size_t *count);

#ifdef __cplusplus
}
#endif

#endif