<p align="center">
  <a href="https://voronoid.tech/">
    <img src="https://raw.githubusercontent.com/LukasRennhofer/CHIFEngine/refs/heads/main/config/assets/CHIFEngine_Logo_2_wbg.png" width="200" alt="CHIFEngine logo">
  </a>
</p>
<p align="center">
<img src="https://raw.githubusercontent.com/LukasRennhofer/CHIFEngine/refs/heads/main/config/assets/gif1.gif" alt="GIF Show Background" style="">
</p>

<p align="center">
  <img alt="GitHub Release" src="https://img.shields.io/github/v/release/LukasRennhofer/CHIFEngine">
  <img alt="GitHub top language" src="https://img.shields.io/github/languages/top/LukasRennhofer/CHIFEngine">
  <img alt="GitHub commit activity" src="https://img.shields.io/github/commit-activity/t/LukasRennhofer/CHIFEngine">
  <img alt="GitHub contributors" src="https://img.shields.io/github/contributors/LukasRennhofer/CHIFEngine">
  <img alt="GitHub Downloads (all assets, all releases)" src="https://img.shields.io/github/downloads/LukasRennhofer/CHIFEngine/total">
  
</p>

<br>

<p align="center">
  <img alt="GitHub Sponsors" src="https://img.shields.io/github/sponsors/LukasRennhofer">
  <img alt="GitHub Issues or Pull Requests" src="https://img.shields.io/github/issues/LukasRennhofer/CHIFEngine">
  <img alt="Website" src="https://img.shields.io/website?url=https%3A%2F%2Fvoronoid.tech%2F">
</p>

---

## About CHIFEngine

[CHIFEngine](https://github.com/LukasRennhofer/CHIFEngine) is a low-level, high-performance game engine designed for **large-scale Open-World games** and is a code-focused development SDK and Framework. Built from the ground up with **OpenGL** and custom rendering techniques, it provides fine-grained control over every aspect of game development while maintaining **maximum efficiency**. Unlike high-level game engines, the engine is designed to be **lightweight**, **modular**, and **fully extensible**, allowing developers to directly manipulate rendering, physics, and resource management.

---

## Why CHIFEngine?
> ***C***ross-Platform ***H***igh-Performance ***I***nterface ***F***ramework Engine
- **Free and Open Source**: CHIFEngine is licensed under the MIT License, allowing complete freedom with no royalties or hidden fees, just the same License.
- **Hobby Project for Open-World Game**: As a hobby project, **CHIFEngine** was created with a passion for building a custom low-level game engine to support large-scale open-world games. While it may not offer the conveniences of commercial engines, it provides an invaluable opportunity for hands-on learning, deep customization, and experimenting with game engine design.

> *"Open source is about collaborating; not competing." – **Kelsey Hightower**, technologist at google and open-source advocate*

---

## Getting Started

### Download
You can download the latest binaries of CHIFEngine from [the website](https://lukasrennhofer.github.io/CHIFEngine/#/).

- The [Releases Tab](https://github.com/LukasRennhofer/CHIFEngine/releases)

> **Note**: Currently, CHIFEngine supports only Windows x64 and Nintendo Switch (Homebrew) systems.

### Build Instructions

#### Windows

0. Install Mingw Msys x64 from [their website](https://www.msys2.org/) and install python from [its website](https://www.python.org/).

---

1. Clone the repository:

   ```bash
   git clone https://github.com/LukasRennhofer/CHIFEngine.git
   cd CHIFEngine
   ```

---

2. Install the Dependencies with Msys2:

   ```bash
      pacman -S cmake mingw-w64-x86_64-toolchain mingw-w64-x86_64-freeglut mingw-w64-x86_64-assimp -S mingw-w64-x86_64-sdl2
   ```

---

3. Build the libary with the CHIFDevConsole Script
  ```bash
    python DevConsole.py --platform Windows --build-lib
   ```

#### Linux

- **Status**: Not currently supported. Building on Linux may lead to errors due to limited development resources. (Tested on Ubuntu 24.10)

---

0. Install Python: 
   ```bash
   sudo apt-get install python3
   ```

0. Clone the repository:

   ```bash
   git clone https://github.com/LukasRennhofer/CHIFEngine.git
   cd CHIFEngine
   ```

---

1. Install the Dependencies:

   ```bash
   sudo apt-get install build-essential libsdl2-dev libsdl2-2.0-0 libassimp-dev cmake libglm-dev libglew-dev
   ```

---

2. Build the library from source:

   ```bash
   python3 DevConsole.py --platform Linux --build-lib
   ```

## Features

- **Cross-Platform Support** – Runs on PC and supports Nintendo Switch Homebrew, making it suitable for both modern and embedded hardware
- **Minimal External Dependencies** – Designed to be self-contained, avoiding reliance on bulky third-party libraries while giving developers direct access to OpenGL, Vulkan (experimental), and custom libraries.
- **Custom OpenGL (Vulkan not yet) Rendering Pipeline** – Uses a RHI (Render Hardware Interface) architecture and modern graphics techniques such as deferred shading, GPU-driven culling, and physically-based rendering (PBR) in the future to handle complex environments efficiently.
---

## Documentation & Demos

- **Documentation**: [Doc Site](https://lukasrennhofer.github.io/CHIFEngine/#/).
- **Demos**: *Currently in progress.* Stay tuned for updates.

---

## Roadmap & Todos

Check out our [Todo List](Todo.md) for upcoming features and tasks.

---
## Q&A

 - "When will the public-use version be published?"
 - "Why does the Project takes so long to be complete?"
      - Rome wasn't built in a day.
 - "How can I simply make games with it?"
      - The Engine is specified for complex open-world games only.
 - "Will there be a build for MacOS?"
      - Yeah, right after Apple learns to not be a sandbox for overpriced toys.

## Contributors

We extend our gratitude to the following individuals for their efforts and contributions:

| Name                      | GitHub Handle   | Contributions                     | 
| ------------------------- | --------------- | --------------------------------- |
| **Lukas Rennhofer**       | @LukasRennhofer | **Maintainer**, Engine Logic, Physics |
| **Moritz Rottensteiner**  | @Alyopolo       | 3D Assets and Game Development    |

---

## Stay Connected
- Visit our [Website](https://voronoid.tech/).
- Give us a star on [GitHub](https://github.com/LukasRennhofer/CHIFEngine) for the latest updates.