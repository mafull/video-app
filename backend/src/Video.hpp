#pragma once

#include <string>

enum class VideoError : int
{
    None,
    NotFound
};

class Video {
    enum class Error : int
    {
        None,
        NotFound
    };

private:
    const std::string fileName;

public:
    Video() = default;
    Video(const std::string fileName);

    Video operator+(Video const& secondVideo) const;
    Video operator+=(Video const& secondVideo);

    const std::string& getFileName() const;
};
