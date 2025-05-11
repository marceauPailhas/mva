# Advanced Kernel Methods for Graph Data

## Overview

This project explores advanced kernel methods for graph-structured data, with a focus on efficient graph representation and similarity computation for machine learning tasks. The work was developed as part of a Kaggle challenge on molecule classification, where molecules are represented as graphs with labeled nodes (atoms) and edges (chemical bonds).

## Technical Approach

### Graph Representation

We implemented several techniques to represent graphs in a format suitable for kernel-based machine learning:

1. **Subgraph Enumeration**: Algorithms to efficiently enumerate all subgraphs of a given size in a graph
2. **Path Extraction**: Methods to identify all paths of length at most 5 in each graph
3. **Graph-to-Vector Conversion**: Transformation of graph structures into vector representations while preserving structural information
4. **Node and Edge Labeling**: Encoding of atom and bond information using alphabetic and numeric labels

### Kernel Methods

We developed and implemented several kernel functions for measuring similarity between graphs:

1. **Min-Max Kernel**: A custom kernel that compares the minimum and maximum values of common substructures between two graphs
2. **N-th Order Walk Kernel**: A kernel that counts common walks of length n between two graphs
3. **Weisfeiler-Lehman Kernel**: A kernel based on the Weisfeiler-Lehman test of isomorphism

### Classification with SVMs

We used Support Vector Machines (SVMs) with our custom kernels for the classification task:

1. **Kernel SVM Implementation**: Custom implementation of SVM that works with our graph kernels
2. **Hyperparameter Tuning**: Exploration of different C values to optimize the SVM performance
3. **Class Imbalance Handling**: Techniques such as oversampling and undersampling to address class imbalance

## Implementation Details

- **Graph Processing**: Used NetworkX for graph manipulation and analysis
- **Custom Kernel Functions**: Implemented specialized functions for graph similarity computation
- **Optimization**: Techniques to improve computational efficiency, such as exploiting kernel matrix symmetry
- **Evaluation**: ROC AUC metric for performance assessment

## Results

- Achieved competitive performance on the Kaggle challenge
- Identified trade-offs between computational complexity and model performance
- Demonstrated the effectiveness of min-max kernel for graph classification tasks

## Key Learnings

- The importance of efficient graph representation for kernel methods
- Techniques for handling computational complexity in graph kernel computation
- Strategies for addressing class imbalance in graph classification problems
- The effectiveness of custom kernels for capturing structural similarities in graphs

## Files

- `n_th_order_walk.ipynb`: Implementation of graph-to-vector conversion techniques
- `kernel.py`: Implementation of various graph kernels
- `svm.py`: Support Vector Machine implementation with custom kernels
- Various model files and submission results
