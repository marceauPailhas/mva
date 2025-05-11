# QRT Data Challenge - Electricity Price Prediction

## Overview

This project addresses the QRT ENS Data Challenge 2023, which focused on predicting daily electricity price variations for futures contracts of 24H electricity baseload in France and Germany. The challenge required developing models that could accurately forecast price changes based on various energy-related features.

## Problem Description

- **Objective**: Predict price changes for daily futures contracts of 24H electricity baseload
- **Evaluation Metric**: Spearman rank correlation (chosen for robustness against volatility)
- **Baseline Performance**: 15.9% Spearman correlation on the public leaderboard
- **Challenge**: Handling missing values, identifying relevant features, and avoiding overfitting on a small dataset

## Data Description

The dataset included various features related to electricity markets in France and Germany:

- **Consumption data**: DE_CONSUMPTION, FR_CONSUMPTION
- **Exchange data**: DE_FR_EXCHANGE, FR_DE_EXCHANGE
- **Export/Import data**: DE_NET_EXPORT, FR_NET_EXPORT, DE_NET_IMPORT, FR_NET_IMPORT
- **Energy sources**: DE_GAS, FR_GAS, DE_COAL, FR_COAL, DE_HYDRO, FR_HYDRO, DE_NUCLEAR, FR_NUCLEAR, DE_SOLAR, FR_SOLAR, DE_WINDPOW, FR_WINDPOW, DE_LIGNITE
- **Load data**: DE_RESIDUAL_LOAD, FR_RESIDUAL_LOAD
- **Weather data**: DE_RAIN, FR_RAIN, DE_WIND, FR_WIND, DE_TEMP, FR_TEMP
- **Commodity returns**: GAS_RET, COAL_RET, CARBON_RET

## Approaches

We explored several preprocessing and modeling approaches:

### Preprocessing Techniques

1. **Feature Selection**: Identifying and removing highly correlated features
2. **Missing Value Handling**: Various strategies including zero-filling and mean imputation
3. **Feature Engineering**: 
   - Creating lagged features (t-1, t-7 days)
   - Constructing price features from price variations
   - Country-specific feature encoding

### Modeling Approaches

1. **Linear Regression**: Baseline model with simple preprocessing
2. **Random Forest Regression**: Achieved better performance by capturing non-linear relationships
3. **Kernel Methods**: Explored kernel ridge regression for improved generalization
4. **Time Series Analysis**: Applied periodogram analysis to identify cyclical patterns

## Results and Insights

- **Feature Importance**: Identified key drivers of electricity price variations
- **Correlation Analysis**: Discovered strong correlations between certain features (e.g., DE_CONSUMPTION and FR_CONSUMPTION with 0.82 correlation)
- **Country-Specific Models**: Found that separate models for France and Germany performed better than a unified approach
- **Temporal Patterns**: Identified potential cyclical patterns in price variations

## Technical Implementation

- **Data Preprocessing**: Custom preprocessing functions for different modeling approaches
- **Feature Engineering**: Creation of lagged variables and derived features
- **Model Training**: Implementation of various regression models with hyperparameter tuning
- **Evaluation**: Cross-validation strategies to ensure robust performance estimation

## Key Learnings

- The importance of feature selection in high-dimensional datasets with correlated features
- The value of domain knowledge in energy markets for effective feature engineering
- Strategies for handling time series data with missing values
- The challenge of balancing model complexity with dataset size to avoid overfitting

