#include <opencv2/opencv.hpp>
#include <utility>      // std::pair, std::make_pair
#include <stdlib.h>     /* srand, rand */
#include <fstream>

class Utils {
    public:

    /**
     * Load configuration in the expected format and initiialize the arguments.
     *
     * @param basicString
     * @param point
     * @param mat
     * @param vec
     */
    static void loadConfiguration(const cv::String& input_config_path, cv::Point& origin, cv::Mat& kernel, cv::Vec3b& regionColor, bool withColor) {
        std::ifstream input_config_file(input_config_path);
        if (input_config_file.is_open()) {
            std::string line;
            // get X
            std::getline(input_config_file, line);
            int x = std::stoi(line);

            // get Y
            std::getline(input_config_file, line);
            int y = std::stoi(line);

            // Convert x and y to origin
            origin = cv::Point(x, y);

            // Get neighbor connectivity and configure the kernel
            std::getline(input_config_file, line);
            int size = std::stoi(line);
            kernel = cv::getStructuringElement(size == 4 ? cv::MORPH_CROSS : cv::MORPH_RECT,cv::Size(3, 3));

            // Get region color
            if (withColor) {
                std::getline(input_config_file, line);
                int regionColorIntensity = std::stoi(line);
                regionColor = cv::Vec3b(regionColorIntensity, regionColorIntensity, regionColorIntensity);
            }
            input_config_file.close();
        }
        else {
            std::cout << "No config data\n";
        }
    }

/**
 * Returns point with max as first and min as second of the area where the kernel overlaps with the image
 * */
static std::pair<cv::Vec3b, cv::Vec3b> generateRegion(const cv::Mat& image, const cv::Mat& kernel, const cv::Point& origin, const cv::Vec3b& regionColor, cv::Mat& outputImage) {
    const cv::Vec3b defaultPixelOut(0, 0, 0);
    cv::Vec3b neighbor_min(255, 255, 255);
    cv::Vec3b neighbor_max(0, 0, 0);
    double magnitude_min = cv::norm(neighbor_min, cv::NORM_L2);
    double magnitude_max = cv::norm(neighbor_max, cv::NORM_L2);

    std::vector<cv::Point> toVisitList{ origin };

    while (!toVisitList.empty()) {
        // Get first element of list
        const cv::Point currentPixel = toVisitList.back();
        toVisitList.pop_back();

        // Label current pixel
        outputImage.at<cv::Vec3b>(currentPixel.x, currentPixel.y) = regionColor;
        const cv::Vec3b& currentPixelLabelImg = image.at<cv::Vec3b>(currentPixel.x, currentPixel.y);

        // Look for all the neighbors of the current pixels and then
        // filter the ones that are not already visited, adding them to visitList
        std::vector<cv::Point> neighbors = getNeighbors(image, kernel, cv::Point(currentPixel.x, currentPixel.y));

        for (const cv::Point& neighbor : neighbors) {
            const cv::Vec3b& neighborPixelLabelOut = outputImage.at<cv::Vec3b>(neighbor.x, neighbor.y);
            const cv::Vec3b& neighborPixelLabelImg = image.at<cv::Vec3b>(neighbor.x, neighbor.y);

            // Check it is not labeled
            if (cv::norm(neighborPixelLabelOut, defaultPixelOut, cv::NORM_L2) == 0) {
                // If colors are the same, it belongs to the region
                if (cv::norm(currentPixelLabelImg, neighborPixelLabelImg, cv::NORM_L2) == 0) {
                    toVisitList.push_back(neighbor);
                }
                 // Otherwise, they are neighbors
                else {
                    // Calculate min
                    double magnitude_neighbor = cv::norm(neighborPixelLabelImg, cv::NORM_L2);
                    if (magnitude_neighbor < magnitude_min) {
                        neighbor_min = neighborPixelLabelImg;
                        magnitude_min = magnitude_neighbor;
                    }

                    // Calculate max
                    if (magnitude_neighbor > magnitude_max) {
                        neighbor_max = neighborPixelLabelImg;
                        magnitude_max = magnitude_neighbor;
                    }
                }
            }
        }
    }

    return std::make_pair(neighbor_min, neighbor_max);
}

private:

    /**
     * Returns point with max as first and min as second of the area where the kernel overlaps with the image
     * */
    static std::vector<cv::Point> getNeighbors(const cv::Mat& image, const cv::Mat& kernel, const cv::Point& origin) {
        std::vector<cv::Point> neighbors;
        int width = kernel.rows / 2;
        int height = kernel.cols / 2;

        // If the width is even, remove one cell to see from the right
        int oneCellWidth = (kernel.rows % 2 == 0) ? 1 : 0;
        int oneCellHeight = (kernel.cols % 2 == 0) ? 1 : 0;

        // Add limits
        int max = -1;
        int min = 256;

        for (int i = -width; i <= width - oneCellWidth; ++i) {
            int imageX = origin.x + i;

            // Check if kernel x is inside image
            if (imageX >= 0 && imageX < image.rows) {
                for (int j = -height; j <= height - oneCellHeight; ++j) {
                    int imageY = origin.y + j;
                    const int& neighborPixel = (int) kernel.at<uchar>(i + width, j + height);

                    // Check if kernel y is inside image and is not origin
                    if (imageY >= 0 && imageY < image.cols && (imageX != origin.x || imageY != origin.y) && neighborPixel == 1) {
                        neighbors.push_back(cv::Point(imageX, imageY));
                    }
                }
            }
        }

        return neighbors;
    }
};