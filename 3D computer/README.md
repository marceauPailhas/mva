# 3D Computer Vision

This repository contains C++ implementations of various 3D computer vision algorithms using the Imagine++ library. These implementations cover fundamental concepts in stereo vision, 3D reconstruction, and image alignment.

## Contents

The repository includes the following implementations:

### 1. Seeds.cpp - Seed-Based Stereo Matching

This implementation uses a seed propagation approach for computing disparity maps between stereo image pairs. The algorithm:

- Computes normalized cross-correlation (NCC) between patches in the left and right images
- Identifies high-confidence matches as "seeds" (points with high NCC values)
- Propagates these seeds to neighboring pixels to create a dense disparity map
- Visualizes the resulting 3D reconstruction

The algorithm is particularly effective for stereo matching as it combines the accuracy of correlation-based methods with the efficiency of propagation-based approaches.

### 2. Fundamental.cpp - Fundamental Matrix Computation

This implementation computes the fundamental matrix between two images, which encodes the epipolar geometry. The algorithm:

- Detects SIFT features in both images to find potential point correspondences
- Uses RANSAC to robustly estimate the fundamental matrix while filtering outliers
- Implements the 8-point algorithm for fundamental matrix computation
- Provides an interactive visualization of epipolar lines

The fundamental matrix is essential for stereo vision tasks as it defines the geometric relationship between two camera views.

### 3. GCDisparity.cpp - Graph Cuts for Stereo Matching

This implementation uses graph cuts optimization for computing disparity maps. The algorithm:

- Formulates the stereo matching problem as an energy minimization task
- Constructs a graph where nodes represent pixel-disparity assignments
- Uses max-flow/min-cut algorithm to find the optimal disparity assignment
- Includes both data terms (based on ZNCC) and smoothness terms for regularization
- Visualizes the resulting disparity map and 3D reconstruction

Graph cuts provide a global optimization approach to stereo matching, which often results in more accurate and smoother disparity maps compared to local methods.

### 4. Panorama.cpp - Image Stitching

This implementation creates panoramic images by stitching two overlapping images. The algorithm:

- Allows users to select corresponding points in both images
- Computes the homography transformation between the images
- Warps and blends the images to create a seamless panorama
- Handles the transformation of coordinates and proper image blending

Image stitching is a fundamental technique for creating panoramas and is based on projective geometry principles.

## Dependencies

These implementations rely on the Imagine++ library, which provides:
- Image loading and manipulation
- Linear algebra operations
- Graphics and visualization tools
- Feature detection (SIFT)

## Usage

Each implementation can be compiled and run separately. For example:

```bash
# Compile Seeds implementation
g++ Seeds.cpp -o Seeds -lImagine++

# Run with default images
./Seeds

# Run with custom images
./Seeds im1.jpg im2.jpg
```

Similar commands apply to the other implementations.

## Implementation Details

The code includes detailed comments explaining the algorithms and their implementation. Key computer vision concepts demonstrated include:

- Correlation-based matching
- Feature detection and matching
- RANSAC for robust estimation
- Epipolar geometry
- Energy minimization via graph cuts
- Homography estimation and image warping

These implementations serve as educational examples of fundamental 3D computer vision algorithms.
