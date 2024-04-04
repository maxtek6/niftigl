#include "niftigl.hpp"

void niftigl::stage(const std::string &path, std::vector<GLuint> &slices)
{
    GLuint *slice_data;
    size_t slice_count;

    niftigl_stage(path.c_str(), &slice_data, &slice_count);
    slices.resize(slice_count);
    std::memcpy(slices.data(), slice_data, slice_count);
    std::free(slice_data);
}