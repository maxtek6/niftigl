#ifndef NIFTIGL_H
#define NIFTIGL_H

#include <GL/gl.h>
#include <GL/glx.h>

extern "C" {

int niftigl_stage(const char *path, GLuint **slices, size_t *count);

}

#endif