# Mini Project - Audio Source Separation

This folder contains the mini project for the Machine Learning for Time Series course at MVA 2022-2023, focusing on audio source separation techniques.

## Overview

Audio source separation is the task of separating a mixed audio signal into its constituent source signals. This project implements and compares several state-of-the-art methods for blind source separation:

- Independent Vector Analysis (IVA)
- Independent Component Analysis (ICA)
- Multichannel Non-negative Matrix Factorization (MNMF)
- Independent Low-Rank Matrix Analysis (ILRMA)

## Contents

- `Projet_Time_Series_3.8.ipynb`: Main Jupyter notebook containing the project implementation and results
- `audio_source_separation-main/`: Directory containing the source separation implementation code
- `data/`: Directory containing audio data files
- `estimations_IVA_ICA_MNMF_ILRMA/`: Directory containing separation results from different algorithms
- `MNMF/`, `MNMF_last_version/`: Implementations of Multichannel Non-negative Matrix Factorization
- Various PDF files: Research papers related to the implemented methods
- `*.wav` files: Sample audio files for testing and demonstration
- `prepare.py`, `prepare.sh`: Scripts for data preparation
- `test/`, `test2/`, `test3/`: Directories containing test results
- `vitesse_convergence/`: Directory containing convergence analysis results

## Theoretical Background

The project explores several key approaches to blind source separation:

1. **ICA (Independent Component Analysis)**: Separates mixed signals by maximizing statistical independence
2. **IVA (Independent Vector Analysis)**: Extension of ICA that preserves dependencies between frequency bins
3. **MNMF (Multichannel Non-negative Matrix Factorization)**: Decomposes spectrograms into non-negative components
4. **ILRMA (Independent Low-Rank Matrix Analysis)**: Combines IVA and NMF approaches

## How to Run

1. Open the main Jupyter notebook `Projet_Time_Series_3.8.ipynb`
2. Ensure you have the required Python libraries installed:
   - NumPy
   - SciPy
   - Matplotlib
   - Librosa (for audio processing)
   - PyTorch (optional, for some implementations)
3. Run the cells in sequence to reproduce the analysis and results

## Performance Comparison

The project includes a comprehensive comparison of the different algorithms in terms of:
- Separation quality (SDR, SIR, SAR metrics)
- Computational efficiency
- Convergence speed
- Robustness to different mixing conditions

## References

The implementation is based on several research papers, which are included in the directory:
- "A Review of Blind Source Separation Methods: Two Converging Routes to ILRMA Originating from ICA and NMF"
- "Determined Blind Source Separation Unifying Independent Vector Analysis and Nonnegative Matrix Factorization"
- "Multichannel Extensions of Non-Negative Matrix Factorization"
