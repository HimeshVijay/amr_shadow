# AMR Shadow

> Building an Autonomous Mobile Robot software stack in ROS2 from first principles.

AMR Shadow is a long-term robotics software engineering project focused on developing the complete software stack of an Autonomous Mobile Robot (AMR) using ROS2 and modern C++.

Instead of following isolated tutorials, this repository documents the incremental development of a modular robot, where every subsystem is designed, implemented, tested in simulation, version-controlled, and later deployed to real hardware.

The objective is not simply to learn ROS2 APIs, but to understand the engineering principles behind distributed robotic systems.

---

# Vision

The goal of Shadow is to build a complete AMR software stack comparable to those used in industrial mobile robots.

Development follows a simulation-first workflow:

Algorithm → ROS2 Node → Simulation → Hardware Interface → Physical Robot

Every feature is first implemented and verified in software before interacting with physical hardware.

---

# Current Progress

## Sprint 1

- ROS2 Workspace Setup
- Package Creation
- Heartbeat Publisher
- Git Repository Initialization

## Sprint 2

- Publisher / Subscriber Communication
- Event-driven Node Architecture
- Shared State Between Callbacks
- Command Publisher Node
- Heartbeat Subscriber Node
- GitHub Integration

---

# Repository Structure

```
shadow_ws/
│
├── src/
│   └── shadow_diagnostics/
│       ├── src/
│       │   ├── heartbeat_node.cpp
│       │   └── command_node.cpp
│       ├── CMakeLists.txt
│       └── package.xml
│
├── build/
├── install/
└── log/
```

---

# Engineering Principles

Shadow follows several software engineering principles throughout development.

- Modular ROS2 node architecture
- Incremental development
- Event-driven programming
- Simulation before hardware
- Git-based version control
- Clean and maintainable C++ design

---

# Planned Roadmap

- Custom ROS2 Messages
- Parameters
- Launch Files
- Services
- Actions
- Diagnostics
- TF2
- URDF
- RViz
- Gazebo Simulation
- Differential Drive
- Odometry
- LiDAR Integration
- IMU Integration
- Localization
- SLAM
- Navigation
- Hardware Deployment

---

# Build

```bash
cd ~/shadow_ws

colcon build

source install/setup.bash
```

Run heartbeat node

```bash
ros2 run shadow_diagnostics heartbeat_node
```

Run command node

```bash
ros2 run shadow_diagnostics command_node
```

---

# Technologies

- ROS2 Humble
- Modern C++
- Git
- CMake
- Ubuntu 22.04

---
i dont want it to become another repository with ai generated codebase, so i am trying and doing everything from scratch and learning on the way. its an ongoing effort to design and implement an autonomous mobile robot software stack using the same incremental engineering approach used in professional robotics development. 

This repository is developed incrementally. Every major feature represents a completed engineering sprint with corresponding Git history documenting the evolution of the software stack.
