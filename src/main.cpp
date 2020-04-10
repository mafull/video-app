#include <iostream>
#include <filesystem>
#include <string>

#include "Video.hpp"

using std::cout;
using std::cerr;
using std::endl;

// https://www.codingame.com/playgrounds/5659/c17-filesystem
namespace fs = std::filesystem;

int main()
{
    const fs::path picsPath = "/usr/pictures";
    if (!fs::exists(picsPath) || !fs::is_directory(picsPath)) {
        cerr << "Directory " << picsPath << " could not be found" << endl;
        return 1;
    }

    cout << "Listing contents of directory \"" << picsPath << "\"" << endl;
    for (const auto& entry : fs::directory_iterator(picsPath)) {
        cout << "> (" << (fs::is_directory(entry) ? "DIR" : "FIL") << ")" << entry.path().filename() << endl;
    }

    const Video video("/dir/hello");
    const Video video2;

    VideoError vidErr = VideoError::NotFound;
    cout << static_cast<int>(vidErr) << endl;

    return 0;
}
