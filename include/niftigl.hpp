#ifndef NIFTIGL_HPP
#define NIFTIGL_HPP

#include "niftigl.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace niftigl
{
    void stage(const std::string& path, std::vector<GLuint>& slices);
}

#endif