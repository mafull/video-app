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


void log_info(std::string message);
void log_error(std::string message);

// https://www.codingame.com/playgrounds/5659/c17-filesystem
namespace fs = std::filesystem;

int main()
{
    // Get a list of files
    const fs::path picsPath = "/usr/pictures";
    if (!fs::exists(picsPath) || !fs::is_directory(picsPath)) {
        log_error("Directory " + std::string(picsPath) + " could not be found");
        return 1;
    }

    log_info("Listing contents of directory " + std::string(picsPath));
    bool firstFile = true;
    for (const auto& entry : fs::directory_iterator(picsPath)) {
        log_info("> (" + std::string(fs::is_directory(entry) ? "DIR" : "FIL") + ")" + std::string(entry.path().filename()));
        if (!fs::is_directory(entry) && (entry.path().extension() == ".MP4" || entry.path().extension() == ".mp4") && firstFile) {
            firstFile = false;
            log_info("Opening " + std::string(entry.path()) + "...");
            cv::VideoCapture cap(entry.path());
            if (!cap.isOpened()) {
                log_error("Error opening video stream or file");
                return -1;
            }

            double fps = cap.get(cv::CAP_PROP_FPS) / 0.5;
            const int waitTimeMs = 1000 / fps;
            log_info(std::to_string(fps) + " - " + std::to_string(waitTimeMs));


            int counter = 0;
            log_info("started");
            while (1) {
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
                cout << "frame|" << encodedStr << endl;

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
    log_info("Gunna start counting");
    while (counter < 10) {
        log_info("Count: " + std::to_string(counter++));
        sleep_for(1s);
    }
    return 0;
}

void log_info(std::string message)
{
    cout << "log|" << message << endl;
}

void log_error(std::string message)
{
    cerr << "error|" << message << endl;
}