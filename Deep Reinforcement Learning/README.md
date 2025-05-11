# Flappy Bird - Deep Reinforcement Learning Project

This project explores various reinforcement learning approaches to train an agent to play the game Flappy Bird. The goal is to achieve the highest possible average reward by navigating the bird through as many obstacles as possible without colliding.

## Project Overview

In this project, I implemented and compared several approaches to solve the Flappy Bird game using reinforcement learning techniques:

1. **Heuristic Rules**: A rule-based approach that avoids "suicide actions" (actions that would inevitably lead to failure)
2. **Deep Q-Learning (DQN)**: A deep learning approach to learn the optimal policy
3. **Deep Recurrent Q-Network (DRQN)**: An extension of DQN with LSTM for handling sequential information
4. **Hybrid Approaches**: Combinations of heuristic rules with learning-based methods

## Game Environment

In the Flappy Bird environment:
- The state is represented by the bird's position and velocity, along with information about upcoming obstacles
- Actions are binary: push (action=1) or let fall (action=0)
- A reward of +1 is given for passing each obstacle
- A reward of -1 is given when the bird collides with an obstacle or exits the screen

## Methodology

### State Representation

The state space was carefully designed to provide the agent with relevant information:
- The bird's vertical position, vertical velocity, and vertical acceleration
- A discretized representation of the forward view (11 intervals of length 0.05)
- For each interval, the minimum and maximum heights where the bird can safely fly

This results in a 25-dimensional state vector that captures the essential information for decision-making.

### Heuristic Rules

I developed a set of heuristic rules based on the concept of "suicide actions":
- An action is considered a "suicide action" if it inevitably leads to failure within the current view
- The primary rule is to avoid these suicide actions at every step
- When no suicide action exists, different strategies were tested: random action, stable action (keeping the bird near vertical position 0.5), and learned policies

### Deep Q-Learning

The DQN implementation includes:
- A neural network to approximate the Q-function
- Experience replay to break correlations between consecutive samples
- Target network for stable learning
- Hyperparameter tuning for optimal performance

### Deep Recurrent Q-Learning

The DRQN implementation extends DQN by:
- Replacing fully connected layers with LSTM cells
- Providing the network with short-term memory capabilities
- Processing time-series information more effectively

## Experiments and Results

### Performance Comparison

Various approaches were evaluated over 20 episodes with a maximum of 2000 steps each:

| Approach | Average Reward |
|----------|----------------|
| Deep Q-Learning | 88.4 |
| Deep Q-Learning + RNN | 42 |
| Heuristic Rules + DRQN | 376.2 |
| Heuristic Rules + Random Action | 160.6 |
| Heuristic Rules + Stable Action | 345.15 |
| Heuristic Rules + Deep Q-Learning | 358.5 |
| Heuristic Rules + A2C | 156.6 |

The results demonstrate that:
- Heuristic rules provide a strong baseline performance
- Combining heuristic rules with learning-based approaches yields the best results
- DRQN shows faster learning compared to standard DQN

### Hyperparameter Study

A grid search was conducted to find optimal hyperparameters for the DQN approach:
- Discount factor (γ): 1.0 was found to be optimal
- Exploration rate (ε): 0.2 provided the best exploration-exploitation balance
- Learning rate (η): 10^-4 was most effective
- Hidden layer dimension: 128 neurons provided sufficient representational capacity

## Files in this Project

- `[MVA_2023]_Project_part_2_flappy_bird.ipynb`: Jupyter notebook containing the implementation and experiments
- `DeepRL_Project2.pdf`: Project report with detailed methodology and results
- `perfomances`: Results of the hyperparameter grid search

## Conclusion

The most effective approach was found to be the combination of heuristic rules with either DQN or DRQN (if trained), or heuristic rules with the stable action strategy (without training). This hybrid approach leverages the strengths of both rule-based and learning-based methods to achieve superior performance in the Flappy Bird environment.

The project demonstrates the value of combining domain knowledge (in the form of heuristic rules) with modern deep reinforcement learning techniques to solve complex sequential decision-making problems.
