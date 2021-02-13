<h1 align="center">Image Segmentation Overview</h1>
<h4 align="center">Projects developed for the Image Processing, Analysis And Classification course of the EIT Digital data science master at <a href="https://www.upm.es/">UPM</a></h4>

<p align="center">
  <img alt="UPM" src="https://img.shields.io/badge/EIT%20Digital-UPM-blue?style=flat-square">
  <img alt="License" src="https://img.shields.io/github/license/angeligareta/image-processing-overview?style=flat-square" />
</p>

## Introduction
The exercises developed in the area of image segmentation are the following:
- __Contour extraction:__ Extract contour from an image using the morphological operations of erosion or dilation. (Exercise [1a](src/exercises_01_a_contour_extraction.cpp))
- __Grassfire propagation algorithm:__ Detect all the flatzones in the image and output them with different random colors. (Exercise [1b](src/exercises_01_b_grassfire.cpp))
- __Teeth count from gear:__ Given an image of a gear, this program will output an approximate teeth number. (Exercise [2a](src/exercises_02_a_wheel_teeth_count.cpp))
- __Watershed markers:__ Apply watershed algorithm. (Exercise [2b](src/exercises_02_b_watershed.cpp))
 - __Flatzone detection:__ Given pixel coordinates, neighborhood connectivity and region label, detect the flat zone where the origin pixel is and output an image with that region colored with the input label. (Exercise [11](src/exercises_11_a_flatzone.cpp))
- __Regional minimum and maximum:__ Given pixel coordinates and neighborhood connectivity, output if the origin pixel is a regional minimum, regional maximum or nothing. (Exercise [13a](src/exercises_13_a_minimum.cpp) and [13b](src/exercises_13_b_maximum.cpp))

## Environment
This exercises have been developed in the following environment:
- Cmake version: 3.15
- C++ minimum required version: 14
- OpenCV version: 4.3.0
- OS: Ubuntu (Linux)

## Project structure
The project is structured as:
- data: Contains all the images that serve as input examples for the developed programs. 
- programs: Compiled version of src programs.
- src: Contains all the code with an utils folder and the main programs for the exercises.
- CMakeLists.txt: Used to compile with cmake.

## How to use

- __Flatzone:__
```
./programs/exercises_11_a_flatzone ./data/immed_gray_inv_20051218_frgr4.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/immed_gray_inv_20051218_frgr4_flatzone_57_36.jpg
./programs/exercises_11_a_flatzone ./data/gran01_64.txt ./data/gran01_64.pgm ./output/gran01_64_0_0.jpg
```
- __Regional minimum:__
```
./programs/exercises_13_a_minimum ./data/immed_gray_inv_20051218_frgr4_min_01.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13a_output_01.txt
./programs/exercises_13_a_minimum ./data/immed_gray_inv_20051218_frgr4_min_02.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13a_output_02.txt
```
- __Regional maximum:__
```
./programs/exercises_13_b_maximum ./data/immed_gray_inv_20051218_frgr4_max_01.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13b_output_01.txt
./programs/exercises_13_b_maximum ./data/immed_gray_inv_20051218_frgr4_max_02.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13b_output_02.txt
```
- __Contour extraction:__
```
./programs/exercises_01_a_contour_extraction ./data/hitchcock.png ./output/hitchcock_contour.png
```
- __Grassfire propagation algorithm:__
```
./programs/exercises_01_b_grassfire ./data/particles.png ./output/particles_regions.png
```
- __Teeth count from gear:__
```
./programs/exercises_02_a_wheel_teeth_count ./data/wheel.png ./output/wheel_teeth.txt
```
- __Watershed markers:__
```
./programs/exercises_02_b_watershed ./data/coffee_grains.jpg ./output/coffee_markers.jpg
```

## Author
- Angel Igareta [angel@igareta.com](mailto:angel@igareta.com) 
