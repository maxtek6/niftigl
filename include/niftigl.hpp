#ifndef NIFTIGL_HPP
#define NIFTIGL_HPP

#include <nifti1_io.h>

#include <fstream>
#include <iostream>
#include <memory>

namespace niftigl
{
    class image
    {
    public:
        image(const std::string& path);
    private:
        std::unique_ptr<nifti_image> _image;
    };
}

#endif