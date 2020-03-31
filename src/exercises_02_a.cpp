#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

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
    parser.about("Teeth Count app v1.0.0");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    cv::String input_path = parser.get<cv::String>(0);
    cv::String output_path = parser.get<cv::String>(1);

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

    // Scale image 2.5 times to perform the operations easier
    cv::resize(input, input, cv::Size(), 2.5, 2.5);

    // Erode with size one to separate gear
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat erodedInput = input.clone();
    cv::erode(input, erodedInput, kernel);

    // namedWindow("Eroded Image", cv::WINDOW_AUTOSIZE);
    // imshow("Eroded Image", erodedInput);

    // Do canny edge detection to locate edges
    int threshold = 50, ratio = 3, kernel_size = 3;
    cv::Mat detected_edges;
    Canny(input, detected_edges, threshold, threshold * ratio, kernel_size);

    // Dilate to increment edge size
    cv::Mat kernel_2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(detected_edges, detected_edges, kernel_2);

    // namedWindow("Dilated Image", cv::WINDOW_AUTOSIZE);
    // imshow("Dilated Image", detected_edges);

    // Find contours, get max one
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(detected_edges, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int max_index = 0, max_area = 0;
    for (int i = 0; i >= 0; i = hierarchy[i][0]) {
        cv::Rect rect = boundingRect(contours[i]);
        int area = rect.width * rect.height;

        if (max_area < area ) {
            max_area = area;
            max_index = i;
        }
    }

    // Get convex hull of biggest contour
    std::vector<cv::Point> hull;
    convexHull(contours[max_index], hull);

    // Draw the contour
    // cv::Mat drawing = cv::Mat::zeros(detected_edges.size(), CV_8UC3);
    // cv::Scalar color = cv::Scalar(255, 0, 0);
    // drawContours(drawing, std::vector<std::vector<cv::Point>>(1, contours[max_index]), -1, color);
    // drawContours(drawing, std::vector<std::vector<cv::Point>>(1, hull), -1, color);
    // drawContours(drawing, std::vector<std::vector<cv::Point>>(1, contours[max_index]), -1, color);
    // for (int i = 0; i < hull.size(); i++) {
    //     cv::circle(drawing, hull.at(i), 2, color, 5);
    // }

    std::cout << hull.size() << std::endl;

    // namedWindow("Convex hull Image", cv::WINDOW_AUTOSIZE);
    // imshow("Convex hull Image", drawing);

    cv::waitKey(0);
    // cv::imwrite(output_path, output);

    return 0;
}
