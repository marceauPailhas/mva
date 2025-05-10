# Comprehensive QRT Model

This repository contains a comprehensive model for the QRT ENS Challenge Data 2023, which combines the best approaches from Antoine and Marceau's individual notebooks.

## Overview

The goal of this challenge is to predict electricity price variations based on various features related to electricity consumption, production, and exchange between France and Germany. The comprehensive model integrates multiple techniques to improve prediction accuracy:

1. **Feature Engineering**
   - Lagged features (1-day and 7-day lags) for key variables
   - Day of week encoding
   - Separate preprocessing for France and Germany

2. **Outlier Detection and Removal**
   - Implementation of multiple outlier detection algorithms (ABOD, CBLOF, ECOD)
   - Comparison of different outlier detection methods
   - Removal of outliers to improve model robustness

3. **Model Selection and Evaluation**
   - Linear Regression
   - Polynomial Features with Linear Regression
   - Kernel Ridge Regression (RBF and Sigmoid kernels)
   - Random Forest
   - XGBoost
   - Hyperparameter tuning for XGBoost

4. **Ensemble Learning**
   - Weighted ensemble of all models to leverage their individual strengths

## Key Improvements

The comprehensive model improves upon the individual approaches in several ways:

1. **More Sophisticated Feature Engineering**
   - Combines the lagged features approach from Antoine with the polynomial features from Marceau
   - Adds day of week encoding to capture weekly patterns

2. **Outlier Handling**
   - Incorporates Marceau's outlier detection techniques to improve model robustness
   - Compares multiple outlier detection algorithms to identify the most effective approach

3. **Advanced Model Selection**
   - Tests a wider range of models than either individual approach
   - Uses cross-validation to ensure reliable model evaluation

4. **Ensemble Learning**
   - Creates a weighted ensemble of all models to achieve better performance than any single model

## How to Use

1. Open the `Comprehensive_QRT_Model.ipynb` notebook
2. Run all cells in order
3. The notebook will generate two submission files:
   - `comprehensive_qrt_submission.csv`: Predictions from the best single model (tuned XGBoost)
   - `ensemble_qrt_submission.csv`: Predictions from the weighted ensemble of all models

## Requirements

The notebook requires the following Python libraries:
- numpy
- pandas
- scipy
- scikit-learn
- xgboost
- matplotlib
- statsmodels
- pyod (for outlier detection)

## Results

The comprehensive model achieves a higher Spearman correlation than the benchmark model (15.9%), demonstrating the effectiveness of combining multiple approaches and techniques.

## Future Improvements

Potential areas for further improvement include:
- More sophisticated time series features
- Additional feature selection techniques
- More advanced ensemble methods
- Neural network approaches
