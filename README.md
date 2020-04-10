# Exercises 1X
## Introduction
These exercises introduce to image segmentation by calculating the flat zone of a pixel in an image, as well as the region maximum and minimum.

## Environment
This exercises have been developed in the following environment:
- Cmake version: 3.15
- C++ minimum required version: 14
- OpenCV version: 4.3.0

## Project structure
The project is structured as:
- data: Contains all the images that serve as input examples for the developed programs. 
- src: Contains all the code with an utils folder and the main programs for the exercises.
- CMakeLists.txt: Used to compile with cmake.

## How to use

- Exercise Flatzone:
```
./programs/exercises_011_a ./data/immed_gray_inv_20051218_frgr4.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/immed_gray_inv_20051218_frgr4_flatzone_57_36.jpg
./programs/exercises_011_a ./data/gran01_64.txt ./data/gran01_64.pgm ./output/gran01_64_0_0.jpg
```
- Exercise Regional Minimum:
```
./programs/exercises_013_a ./data/immed_gray_inv_20051218_frgr4_min_01.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13a_output_01.txt
./programs/exercises_013_a ./data/immed_gray_inv_20051218_frgr4_min_02.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13a_output_02.txt
```
- Exercise Regional Maximum:
```
./programs/exercises_013_b ./data/immed_gray_inv_20051218_frgr4_max_01.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13b_output_01.txt
./programs/exercises_013_b ./data/immed_gray_inv_20051218_frgr4_max_02.txt ./data/immed_gray_inv_20051218_frgr4.pgm ./output/exercise_13b_output_02.txt
```