# Reinforcement Learning Course Assignments

This directory contains three homework assignments completed for the MVA (Mathematics, Vision, Learning) Reinforcement Learning course (2022-2023). Each notebook explores different aspects of reinforcement learning theory and implementation.

## Overview

The assignments cover a wide range of reinforcement learning topics, from fundamental concepts like dynamic programming to more advanced techniques like deep Q-learning and policy gradient methods. The notebooks include both theoretical derivations and practical implementations.

## Homework 1: Dynamic Programming and Tabular RL

**File:** `RL_MVA_2022_Homework_1_MarceauPAILHAS.ipynb`

This notebook focuses on the fundamentals of reinforcement learning:

### Part 1: Dynamic Programming
- Implementation of policy evaluation, policy iteration, and value iteration algorithms
- Comparison of these algorithms in terms of convergence speed and computational efficiency
- Analysis of affine transformations on reward functions and their impact on optimal policies

### Part 2: Tabular Reinforcement Learning
- Estimation of transition probabilities and rewards from sampled data
- Comparison of different data collection methods (random policy vs. uniform sampling)
- Theoretical analysis of error bounds for estimated value functions
- Discussion of offline data utilization in Q-learning and SARSA

### Part 3: Function Approximation
- Implementation of Fitted Q-Iteration (FQI) with linear function approximation
- Derivation of closed-form updates for linear FQI
- Experimentation with different feature maps to reduce approximation error

## Homework 2: Deep Reinforcement Learning

**File:** `RL_MVA_2022_Homework_2_MarceauPAILHAS.ipynb`

This notebook explores deep reinforcement learning methods:

### Part 1: Deep Q-Network (DQN)
- Implementation of various DQN variants:
  - Standard DQN
  - Double DQN
  - Dueling DQN
  - Double Dueling DQN
- Analysis of the role of target networks and update frequency
- Comparison of performance between different DQN architectures

### Part 2: REINFORCE (Policy Gradient)
- Implementation of the REINFORCE algorithm (Monte Carlo policy gradient)
- Derivation of off-policy variants of policy gradient methods
- Analysis of the properties required for behavioral policies in off-policy learning

### Part 3: Model Selection Using UCB
- Implementation of Upper Confidence Bound (UCB) algorithm for online model selection
- Adaptive allocation of computational resources to different RL algorithms
- Analysis of UCB's suitability for online model selection in reinforcement learning

## Homework 3: Linear Contextual Bandits

**File:** `RL_MVA_2022_Homework_3_MarceauPAILHAS.ipynb`

This notebook investigates linear contextual bandits and the impact of representations:

### Step 1: LinUCB with Different Representations
- Implementation of the LinUCB algorithm
- Testing with different linear representations of the same underlying problem
- Analysis of how representation quality affects learning performance
- Investigation of the Hölder-Lipschitz-Smooth (HLS) condition for representations

### Step 2: Representation Selection
- Implementation of the LEADER algorithm for leveraging good representations
- Comparison of LEADER with LinUCB using different representations
- Analysis of LEADER's performance with non-realizable representations

## Key Algorithms Implemented

1. **Dynamic Programming**:
   - Policy Evaluation
   - Policy Iteration
   - Value Iteration

2. **Deep Reinforcement Learning**:
   - DQN (Deep Q-Network)
   - Double DQN
   - Dueling DQN
   - Double Dueling DQN
   - REINFORCE (Policy Gradient)

3. **Bandits**:
   - LinUCB (Linear Upper Confidence Bound)
   - LEADER (Leveraging Good Representations in Linear Contextual Bandits)

## Notable Findings

- Different DQN variants show varying performance, with Double Dueling DQN generally performing best
- Representation quality significantly impacts the performance of linear contextual bandits
- The HLS condition is a key property for achieving constant regret in linear contextual bandits
- LEADER algorithm effectively leverages the best representation among multiple options
