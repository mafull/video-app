#include "Video.hpp"

#include <iostream>

Video::Video(const std::string fileName) : fileName(fileName)
{
    std::cout << "Creating video object with file name: " << this->fileName << std::endl;
}

const std::string& Video::getFileName() const
{
    return fileName;
}