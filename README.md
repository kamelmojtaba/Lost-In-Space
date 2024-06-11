# Lost In Space

## Project Overview

This project involves creating a 3D virtual world set in outer space using OpenGL and C++. The primary goal is to demonstrate the application of computer graphics principles by designing and animating 11 virtual models, both custom and built-in, within a dynamic and interactive environment.

## Authors

- Kamel Mojtaba Kamel
- Nur Izzati Insyirah binti Zaharudin

## Institution

Multimedia University

## Instructor

Dr. Ng Kok Why

## Table of Contents

1. [Introduction](#introduction)
2. [Technologies Used](#technologies-used)
3. [Setup Instructions](#setup-instructions)
4. [Code Structure](#code-structure)
5. [Models and Animations](#models-and-animations)
6. [User Interaction](#user-interaction)
7. [PLY Cleaner Utility](#ply-cleaner-utility)

## Introduction

This project aims to create a 3D world set against a starry sky backdrop. It leverages OpenGL for rendering and animating models, applying transformations, and adding lighting effects to enhance visual realism. The project includes both PLY models and built-in OpenGL models, showcasing advanced graphics techniques.

## Technologies Used

- **Development Environment:** CodeBlocks
- **Programming Language:** C++
- **Graphics Library:** OpenGL
- **Additional Tools:** PLY Cleaner Utility (`clean.cpp`)

## Setup Instructions

1. **Clone the repository:**
    ```sh
    git clone https://github.com/kamelmojtaba/Lost-In-Space.git
    ```
2. **Navigate to the project directory:**
    ```sh
    cd Lost In Space
    ```
3. **Open the project in CodeBlocks and build the solution.**
4. **Run the program to explore the 3D virtual world.**

## Code Structure

- **main.cpp:** Entry point of the application, initializes OpenGL and sets up the main loop.
- **Model_Manipulation.cpp/h:** Contains functions for loading, transforming, and displaying 3D models.
- **Vertex.cpp/h:** Defines the vertex structures and includes functions for handling vertex data.
- **ReadBMP.cpp/h:** Utility for reading BMP files used for texture mapping.
- **ImageManipulation.cpp/h:** Provides image manipulation functions for texture processing.
- **clean.cpp:** Utility for cleaning PLY files to ensure compatibility with the application.

## Models and Animations

### PLY Models

1. **Tiger with a ball**
    - **Transformation:** Translated, scaled, and rotated.
    - **Animation:** Rotates on the Y-axis.
2. **Plant**
    - **Transformation:** Translated and scaled.
    - **Animation:** Static.

### Built-in Models

1. **Earth, Moon, Venus, Jupiter**
    - **Transformation:** Drawn using `drawSphere()` with texture mapping.
    - **Animation:** Earth and Moon have spinning animations.
2. **Road Sign**
    - **Transformation:** Constructed using `drawCylinder()` and `drawSquare()`.
    - **Animation:** Static.
3. **Television**
    - **Transformation:** Built using `drawCube()`.
    - **Animation:** Static.

## User Interaction

### Keyboard Controls

- **Arrow keys:** Move the view
- **'W'/'w':** Display model wireframe
- **'V'/'v':** Display model vertices
- **'F'/'f':** Display model surfaces
- **'T'/'t':** Display model textures

### Mouse Controls

- **Left mouse button:** Rotate view
- **Right mouse button:** Scale view
- **Middle mouse button:** Pan view

## PLY Cleaner Utility

The `clean.cpp` utility processes PLY files to remove inconsistencies and errors, ensuring compatibility with the 3D model loading functions. This tool is essential for preparing PLY files for use in the OpenGL project.

### How to Use the PLY Cleaner

1. Compile the `clean.cpp` file:
    ```sh
    g++ clean.cpp -o clean
    ```
2. Run the utility with the PLY file as an argument:
    ```sh
    ./clean input.ply output.ply
    ```
3. Use the cleaned PLY file (`output.ply`) in the main application.


## Acknowledgements

- Special thanks to Multimedia University for supporting this research.
- References and academic papers that inspired this project.
