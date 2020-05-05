// #ifdef _WIN32
// #include <Windows.h>
// #else
// #include <unistd.h>
// #endif

#include <chrono>
#include <iostream>
#include <filesystem>
#include <string>
#include <thread>
#include <opencv2/opencv.hpp>

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

    cout << "Listing contents of directory " << picsPath << endl;
    bool firstFile = true;
    for (const auto& entry : fs::directory_iterator(picsPath)) {
        if (!fs::is_directory(entry) && entry.path().extension() == ".mp4" && firstFile) {
            firstFile = false;
            cv::VideoCapture cap(entry.path().filename());
            if (!cap.isOpened()) {
                cout << "Error opening video stream or file" << endl;
                return -1;
            }
        }
        cout << "> (" << (fs::is_directory(entry) ? "DIR" : "FIL") << ")" << entry.path().filename() << endl;
    }

    // const Video video("/dir/hello");
    // const Video video2;

    // VideoError vidErr = VideoError::NotFound;
    // cout << static_cast<int>(vidErr) << endl;
    cv::Mat image;

    using namespace std::this_thread;
    using namespace std::chrono_literals;
    int counter = 0;
    cout << "Gunna start counting" << std::endl;
    while (1) {
        cout << "Count: " << counter++ << std::endl;
        sleep_for(1s);
    }
    return 0;
}
