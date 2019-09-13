# Endora

Endora is a little opengl wrapper, providing helper structs to ease opengl development.

The first and basic implementation follows an Object Oriented Approach, but I recently added a single-header version, lightweight and getting rid of the abstraction layer for data.

*Note: the single header implementation was made to regain the default-constructible, default-copyable and default-movable traits, to enable the support for some STL containers.*

## Functionalities

Single header is still wip to handle all previous objects.

|                      | Object Oriented Approach | Single-header |
| -------------------- |:------------------------:| -------------:|
| **Basic Structures** |||
| Vertex Array/Buffer  | &#10004; | &#10004; |
| Uniform              | &#10004; | &#10004; |
| Uniform Block        | &#10004; | &#10006; |
| Framebuffer Object   | &#10004; | &#10006; |
| **Helpers**          |||
| Shader Program       | &#10004; | &#10004; |
| Texture              | &#10004; | &#10004; |
| Texture - CubeMap    | &#10004; | &#10006; |

## Getting started

To be written...
