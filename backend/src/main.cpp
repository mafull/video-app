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

#include "base64.hpp"

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
        cout << "> (" << (fs::is_directory(entry) ? "DIR" : "FIL") << ")" << entry.path().filename() << endl;
        if (!fs::is_directory(entry) && (entry.path().extension() == ".MP4" || entry.path().extension() == ".mp4") && firstFile) {
            firstFile = false;
            cout << "Opening " << entry.path() << "..." << endl;
            cv::VideoCapture cap(entry.path());
            if (!cap.isOpened()) {
                cout << "Error opening video stream or file" << endl;
                return -1;
            }

            double fps = cap.get(cv::CAP_PROP_FPS) / 0.5;
            const int waitTimeMs = 1000 / fps;
            cout << fps << " - " << waitTimeMs << endl;


            int counter = 0;
            while (1) {
                cout << "started" << endl;
                cv::Mat frame;
                cap >> frame;

                if (frame.empty()) break;

                // if (counter++ % 2 > 0) continue;

                std::vector<base64::byte> buf;
                cv::imencode(".jpg", frame, buf);
                // auto *encoded = reinterpret_cast<unsigned char*>(buf.data());
                std::string encodedStr = base64::encode(buf);

                // cout << "frame: " << frame << endl;
                // cout << "frame: " << frame.reshape(0,1) << endl;
                cout << "frame:" << encodedStr << endl;

                char c = cv::waitKey(waitTimeMs);
                if (c == 88) break;

                // break;
            }

            cap.release();
        }
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
    while (counter < 10) {
        cout << "Count: " << counter++ << std::endl;
        sleep_for(1s);
    }
    return 0;
}
