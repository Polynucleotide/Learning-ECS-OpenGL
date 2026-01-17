# Custom ECS & OpenGL Experiment

This is a personal learning project exploring **Entity Component Systems (ECS)** and **OpenGL instanced rendering**.  
It is my first time learning ECS and OpenGL, so the code is experimental and meant for learning purposes.

## Features
- Experimental ECS with archetypes and bitflags
- Instanced quad rendering using OpenGL
- Memory layout and cache behavior exploration

## Benchmark
- Achieved **200k textured quads at ~60 FPS**  
  *(tested on NVIDIA GeForce RTX 4060 Laptop GPU)*

## Dependencies

This project uses some third-party headers and libraries that I have not included:

```text
Extern/
|-- include/
|   |-- glad/
|   |   `-- glad.h
|   |-- GLFW/
|   |   |-- glfw3.h
|   |   `-- glfw3native.h
|   |-- glm/
|   |   |-- detail/
|   |   |-- ext/
|   |   |-- gtc/
|   |   |-- gtx/
|   |   |-- simd/
|   |   |-- glm.hpp
|   |   |-- mat3x3.hpp
|   |   |-- vec2.hpp
|   |   `-- (All other glm headers) ...
|   `-- KHR/
|       `-- khrplatform.h
`-- lib/
    `-- glfw3.lib
```

## Mistakes Made / Lesson Learned

1. **Component storage & archetypes:**  
   Components are stored by value in contiguous memory, which made moving them around archetypes tricky when structs were large.

2. **Removing components:**  
   Used swap-and-pop when removing components, which can create dangling pointers.

Due to these mistakes and time constraints, this project was not further developed.  

Nevertheless, this experience provided valuable insights into memory layout, ECS design trade-offs, and the complexities of low-level, high-performance systems.
