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

    cv::String input_config_path = parser.get<cv::String>(0);
    cv::String input_path = parser.get<cv::String>(1);
    cv::String output_path = parser.get<cv::String>(2);

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
    cv::Vec3b regionPixelOut;
    Utils::loadConfiguration(input_config_path, origin, kernel, regionPixelOut, true);

     // Create default output image
    const cv::Vec3b defaultPixelOut(0, 0, 0);
    cv::Mat output(input.rows, input.cols, CV_8UC3, defaultPixelOut);

    // Generate region
    Utils::generateRegion(input, kernel, origin, regionPixelOut, output);

    //    namedWindow("Output Image", cv::WINDOW_AUTOSIZE);
    //    imshow("Output Image", output);

    //    cv::waitKey(3000);
    cv::imwrite(output_path, output);

    return 0;
}
