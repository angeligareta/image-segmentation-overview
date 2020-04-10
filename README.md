# Image Segmentation
## Introduction
In this project, exercises in the area of image segmentation are developed, specifically:

- Flatzone Detection
- Regional Minimum and Maximum
- Contour extraction
- Grassfire propagation algorithm
- Teeth Count from gear
- Watershed markers

## Environment
This exercises have been developed in the following environment:
- Cmake version: 3.15
- C++ minimum required version: 14
- OpenCV version: 4.3.0

## Project structure
The project is structured as:
- data: Contains all the images that serve as input examples for the developed programs. 
- output: Example of output from the programs.
- src: Contains all the code with an utils folder and the main programs for the exercises.
- CMakeLists.txt: Used to compile with cmake.

## How to use

- Flatzone:
```
./programs/exercises_11_a_flatzone ./data/immed_gray_inv_20051218_frgr4.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/immed_gray_inv_20051218_frgr4_flatzone_57_36.jpg
./programs/exercises_11_a_flatzone ./data/gran01_64.txt ./data/gran01_64.pgm ./output/gran01_64_0_0.jpg
```
- Regional Minimum:
```
./programs/exercises_13_a_minimum ./data/immed_gray_inv_20051218_frgr4_min_01.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13a_output_01.txt
./programs/exercises_13_a_minimum ./data/immed_gray_inv_20051218_frgr4_min_02.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13a_output_02.txt
```
- Regional Maximum:
```
./programs/exercises_13_b_maximum ./data/immed_gray_inv_20051218_frgr4_max_01.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13b_output_01.txt
./programs/exercises_13_b_maximum ./data/immed_gray_inv_20051218_frgr4_max_02.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13b_output_02.txt
```
- Contour extraction:
```
./programs/exercises_01_a_contour_extraction ./data/hitchcock.png ./output/hitchcock_contour.png
```
- Grassfire propagation algorithm:
```
./programs/exercises_01_b_grassfire ./data/particles.png ./output/particles_regions.png
```
- Teeth Count from gear
```
./programs/exercises_02_a_wheel_teeth_count ./data/wheel.png ./output/wheel_teeth.txt
```
- Watershed markers
```
./programs/exercises_02_b_watershed ./data/coffee_grains.jpg ./output/coffee_markers.jpg
```