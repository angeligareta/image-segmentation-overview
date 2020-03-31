#include <stdio.h>
#include <opencv2/opencv.hpp>

/**
 * Threshold with a value
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    const cv::String arguments =
            "{help h usage ?    |       | print this message }"
            "{size              |   2   | src value          }"
            "{@input_image      |       | image for compare  }"
            "{@output_image     |       | output image       }";

    cv::CommandLineParser parser(argc, argv, arguments);
    parser.about("Contour extraction app v1.0.0");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    cv::String input_path = parser.get<cv::String>(0);
    cv::String output_path = parser.get<cv::String>(1);
    int size = parser.get<int>("size");

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    cv::Mat input = cv::imread(input_path, cv::IMREAD_GRAYSCALE);

    if (!input.data) {
        printf("No image data \n");
        return -1;
    }

    // namedWindow("Input Image", cv::WINDOW_AUTOSIZE);
    // imshow("Input Image", input);

    // Do dilation
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,
        cv::Size(2 * size + 1, 2 * size + 1));
    cv::Mat dilatedInput = input.clone();
    cv::dilate(input, dilatedInput, kernel);

    // Do subtraction with the dilated image
    cv::Mat output = input.clone();
    cv::subtract(dilatedInput, input, output);

    // namedWindow("Output Image", cv::WINDOW_AUTOSIZE);
    // imshow("Output Image", output);

    // cv::waitKey(0);
    cv::imwrite(output_path, output);

    return 0;
}
