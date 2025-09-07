# About {#mainpage}

* Name: Joshua Yeoh Keat Keong
* Student ID: 0135760
* Semester: September 2024

BalisongEngine is a game engine written in C++.

It supports player inputs, timers, random number generation, window and camera adjustments, events or signals to subscribe to and invoke, custom sprites and resource allocation, sprite animator, custom scenes and scene changing, custom game objects and components, prefabs and instantiation, simple AABBox and circle collision detection, simple shape gizmos for debugging, and custom audio playing using irrKlang.

This is the final assignment in Game Engine Architecture and Design.

It is about structuring the project, adding core components, writing documentation using Doxygen, and creating a simple game using this engine.

### Libraries Used

The project uses these libraries:

|Library|Description|
|:-:|:-|
|OpenGL 2.1|Graphics API used for rendering Vertices and Meshes in 3D space|
|GLAD|Loader for OpenGL functions, ensuring compatibility across platforms|
|GLFW|Library for creating windows and handling user input like keyboard and mouse|
|glm|Math library for transformations, vectors, matrices, and other 3D math operations|
|stb_image|Image loading library for loading textures and images|
|random|Used for random number generation with uniform distributions|
|Signal.h|For events and delegates by Simon Schneegans|
|irrKlang|Used for loading and playing audio files|