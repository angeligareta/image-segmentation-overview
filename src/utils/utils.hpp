#include <opencv2/opencv.hpp>
#include <utility>      // std::pair, std::make_pair
#include <stdlib.h>     /* srand, rand */

class Utils {
    public:
    static cv::Mat grassfirePropagate(const cv::Mat& image, const cv::Mat& kernel) {
        srand(1234);        
        
        const cv::Vec3b defaultPixelOut(255, 255, 255);
        cv::Mat outputImage(image.rows, image.cols, CV_8UC3, defaultPixelOut);

        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                const cv::Vec3b& outputPixel = outputImage.at<cv::Vec3b>(i, j);

                // If the pixel does not belong to a region, start region generator
                if (cv::norm(outputPixel, defaultPixelOut, cv::NORM_L2) == 0) {
                    // std::cout << outputPixel << std::endl;
                    generateRegion(image, kernel, cv::Point(i, j), outputImage);
                }
            }
        }

        return outputImage;
    }

    private:
    
    /**
     * Returns point with max as first and min as second of the area where the kernel overlaps with the image
     * */
    static void generateRegion(const cv::Mat& image, const cv::Mat& kernel, const cv::Point& origin, cv::Mat& outputImage) {
        const cv::Vec3b defaultPixelOut(255, 255, 255);
        const cv::Vec3b regionColor(rand() % 255, rand() % 255, rand() % 255);

        // std::cout << regionColor << std::endl;

        // cv::Scalar regionColor = cv::Scalar(colorGenerator.uniform(0, 255));
        std::vector<cv::Point> toVisitList{ origin };
        
        while (toVisitList.size() != 0) {
            // Get first element of list
            const cv::Point currentPixel = toVisitList.back();
            toVisitList.pop_back();

            // Label current pixel
            outputImage.at<cv::Vec3b>(currentPixel.x, currentPixel.y) = regionColor;
            const cv::Vec3b currentPixelLabelImg = image.at<cv::Vec3b>(currentPixel.x, currentPixel.y);

            // Look for all the neighbors of the current pixels and then 
            // filter the ones that are not already visited, adding them to visitList
            std::vector<cv::Point> neighbors = getNeighbors(image, kernel, cv::Point(currentPixel.x, currentPixel.y));
            for (const cv::Point& neighbor : neighbors) {
                const cv::Vec3b neighborPixelLabelOut = outputImage.at<cv::Vec3b>(neighbor.x, neighbor.y);
                const cv::Vec3b neighborPixelLabelImg = image.at<cv::Vec3b>(neighbor.x, neighbor.y);

                // Check it is not labeled and colors are the same
                if (cv::norm(neighborPixelLabelOut, defaultPixelOut, cv::NORM_L2) == 0
                    && cv::norm(currentPixelLabelImg, neighborPixelLabelImg, cv::NORM_L2) == 0) {
                        toVisitList.push_back(neighbor);
                }
            }
        }
    }    

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

                    // Check if kernel y is inside image and is not origin
                    if (imageY >= 0 && imageY < image.cols && imageX != origin.x && imageY != origin.y) {
                        neighbors.push_back(cv::Point(imageX, imageY));
                    }
                }
            }
        }

        return neighbors;
    }    
};