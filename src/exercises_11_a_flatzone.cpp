#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "utils/utils.hpp"

/**
 * Threshold with a value
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    const cv::String arguments =
            "{help h usage ?    |       | print this message }"
            "{@input_config_path|       | input config       }"
            "{@input_image      |       | image for compare  }"
            "{@output_image     |       | output image       }";

    cv::CommandLineParser parser(argc, argv, arguments);
    parser.about("Contour extraction app v1.0.0");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    const cv::String input_config_path = parser.get<cv::String>(0);
    const cv::String input_path = parser.get<cv::String>(1);
    const cv::String output_path = parser.get<cv::String>(2);

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    cv::Mat input = cv::imread(input_path, cv::IMREAD_COLOR);
    if (!input.data) {
        printf("No image data \n");
        return -1;
    }
    //    namedWindow("Input Image", cv::WINDOW_AUTOSIZE);
    //    imshow("Input Image", input);

    // Load configuration
    cv::Point origin;
    cv::Mat kernel;
    cv::Vec3b region_pixel_out;
    Utils::LoadConfiguration(input_config_path, origin, kernel, region_pixel_out, true);

     // Create default output image
    const cv::Vec3b default_pixel_out(0, 0, 0);
    cv::Mat output(input.rows, input.cols, CV_8UC3, default_pixel_out);

    // Generate region
    Utils::GenerateRegion(input, kernel, origin, region_pixel_out, output);

    //    namedWindow("Output Image", cv::WINDOW_AUTOSIZE);
    //    imshow("Output Image", output);

    //    cv::waitKey(3000);
    cv::imwrite(output_path, output);

    return 0;
}
