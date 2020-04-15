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
    static void LoadConfiguration(const cv::String& input_config_path, cv::Point& origin, cv::Mat& kernel, cv::Vec3b& region_color, bool with_color) {
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
            if (with_color) {
                std::getline(input_config_file, line);
                int region_color_intensity = std::stoi(line);
                region_color = cv::Vec3b(region_color_intensity, region_color_intensity, region_color_intensity);
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
static std::pair<cv::Vec3b, cv::Vec3b> GenerateRegion(const cv::Mat& image, const cv::Mat& kernel, const cv::Point& origin, const cv::Vec3b& region_color, cv::Mat& output_image) {
    const cv::Vec3b default_pixel_out(0, 0, 0);
    cv::Vec3b neighbor_min(255, 255, 255);
    cv::Vec3b neighbor_max(0, 0, 0);
    double magnitude_min = cv::norm(neighbor_min, cv::NORM_L2);
    double magnitude_max = cv::norm(neighbor_max, cv::NORM_L2);

    std::vector<cv::Point> to_visit_list{origin };

    while (!to_visit_list.empty()) {
        // Get first element of list
        const cv::Point current_pixel_coord = to_visit_list.back();
        to_visit_list.pop_back();

        // Label current pixel
        output_image.at<cv::Vec3b>(current_pixel_coord.x, current_pixel_coord.y) = region_color;
        const auto& current_pixel_img = image.at<cv::Vec3b>(current_pixel_coord.x, current_pixel_coord.y);

        // Look for all the neighbors of the current pixels and then
        // filter the ones that are not already visited, adding them to visitList
        std::vector<cv::Point> neighbors = GetNeighbors(image, kernel, cv::Point(current_pixel_coord.x, current_pixel_coord.y));

        for (const cv::Point& neighbor : neighbors) {
            const cv::Vec3b& neighbor_pixel_out = output_image.at<cv::Vec3b>(neighbor.x, neighbor.y);
            const auto& neighbor_pixel_img = image.at<cv::Vec3b>(neighbor.x, neighbor.y);

            // Check it is not labeled
            if (cv::norm(neighbor_pixel_out, default_pixel_out, cv::NORM_L2) == 0) {
                // If colors are the same, it belongs to the region
                if (cv::norm(current_pixel_img, neighbor_pixel_img, cv::NORM_L2) == 0) {
                    to_visit_list.push_back(neighbor);
                }
                 // Otherwise, they are neighbors
                else {
                    // Calculate min
                    double magnitude_neighbor = cv::norm(neighbor_pixel_img, cv::NORM_L2);
                    if (magnitude_neighbor < magnitude_min) {
                        neighbor_min = neighbor_pixel_img;
                        magnitude_min = magnitude_neighbor;
                    }

                    // Calculate max
                    if (magnitude_neighbor > magnitude_max) {
                        neighbor_max = neighbor_pixel_img;
                        magnitude_max = magnitude_neighbor;
                    }
                }
            }
        }
    }

    return std::make_pair(neighbor_min, neighbor_max);
}

    static cv::Mat GrassFirePropagate(const cv::Mat& image, const cv::Mat& kernel) {
        srand(1234);

        const cv::Vec3b default_pixel_out(0, 0, 0);
        cv::Mat output_image(image.rows, image.cols, CV_8UC3, default_pixel_out);

        for (int i = 0; i < image.rows; ++i) {
            for (int j = 0; j < image.cols; ++j) {
                const auto& input_pixel = image.at<cv::Vec3b>(i, j);
                const cv::Vec3b& output_pixel = output_image.at<cv::Vec3b>(i, j);

                // If the pixel does not belong to a region and color in input is not black, start region generator
                if (cv::norm(output_pixel, default_pixel_out, cv::NORM_L2) == 0 && cv::norm(input_pixel, default_pixel_out, cv::NORM_L2) != 0) {
                    const cv::Vec3b region_color(rand() % 255, rand() % 255, rand() % 255);
                    GenerateRegion(image, kernel, cv::Point(i, j), region_color, output_image);
                }
            }
        }

        return output_image;
    }

private:

    /**
     * Returns point with max as first and min as second of the area where the kernel overlaps with the image
     * */
    static std::vector<cv::Point> GetNeighbors(const cv::Mat& image, const cv::Mat& kernel, const cv::Point& origin) {
        std::vector<cv::Point> neighbors;
        int width = kernel.rows / 2;
        int height = kernel.cols / 2;

        // If the width is even, remove one cell to see from the right
        int one_cell_width = (kernel.rows % 2 == 0) ? 1 : 0;
        int one_cell_height = (kernel.cols % 2 == 0) ? 1 : 0;

        // Add limits
        int max = -1;
        int min = 256;

        for (int i = -width; i <= width - one_cell_width; ++i) {
            int image_x = origin.x + i;

            // Check if kernel x is inside image
            if (image_x >= 0 && image_x < image.rows) {
                for (int j = -height; j <= height - one_cell_height; ++j) {
                    int image_y = origin.y + j;
                    const int& neighbor_pixel = (int) kernel.at<uchar>(i + width, j + height);

                    // Check if kernel y is inside image and is not origin
                    if (image_y >= 0 && image_y < image.cols && (image_x != origin.x || image_y != origin.y) && neighbor_pixel == 1) {
                        neighbors.push_back(cv::Point(image_x, image_y));
                    }
                }
            }
        }

        return neighbors;
    }
};