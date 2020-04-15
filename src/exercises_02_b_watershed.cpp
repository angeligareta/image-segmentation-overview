#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include <stdlib.h>     /* srand, rand */


/**
 * Threshold with a value
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    const cv::String arguments =
            "{help h usage ?    |       | print this message }"
            "{@input_image      |       | image for compare  }"
            "{@output_image     |       | output image       }";

    cv::CommandLineParser parser(argc, argv, arguments);
    parser.about("Watershed markers v1.0.0");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    srand(1234);
    cv::String input_path = parser.get<cv::String>(0);
    cv::String output_path = parser.get<cv::String>(1);

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    cv::Mat input = cv::imread(input_path, cv::IMREAD_COLOR);

    if (!input.data) {
        printf("No image data \n");
        return -1;
    }
    // imshow("Input Image", input);
    
    // Clone input and convert marker image to bg
    cv::Mat markers = input.clone();
    cv::cvtColor(markers, markers, cv::COLOR_BGR2GRAY);

    // Convert input image to CV_8UC3 for watershed
    input.convertTo(input, CV_8UC3);

    // Remove background
    threshold(markers, markers, 180, 255, 1);
    // Erode to separate the elements
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(17, 17));
    cv::erode(markers, markers, kernel);

    // CV_8U version is needed for findContours()
    markers.convertTo(markers, CV_8U);

    std::vector<std::vector<cv::Point> > contours;
    findContours(markers, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Create the marker image for the watershed algorithm
    cv::Mat contour_markers = cv::Mat::zeros(markers.size(), CV_32S);
    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++) {
        drawContours(contour_markers, contours, static_cast<int>(i), cv::Scalar(static_cast<int>(i)+1), -1);
    }
    // Draw the background marker
    circle(contour_markers, cv::Point(5, 5), 3, cv::Scalar(255), -1);

    // Perform the watershed algorithm
    watershed(input, contour_markers);
    
    // Generate random colors
    std::vector<cv::Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++) {
        colors.push_back(cv::Vec3b((uchar) rand() % 255, (uchar) rand() % 255, (uchar) rand() % 255));
    }

    // Create the result image
    cv::Mat output = cv::Mat::zeros(input.size(), CV_8UC3);
    // Fill labeled objects with random colors
    for (int i = 0; i < contour_markers.rows; i++) {
        for (int j = 0; j < contour_markers.cols; j++) {
            int index = contour_markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size())) {
                output.at<cv::Vec3b>(i,j) = colors[index-1];
            }
        }
    }

    // imshow("Output Image", output);
    // cv::waitKey(0);

    cv::imwrite(output_path, output);

    return 0;
}
