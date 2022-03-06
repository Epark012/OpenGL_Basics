# OpenGL_Basics

**OpenGL-Model-Loader By Eun Hyeon Park**

Development Environment

Visual studio 2019
OpenGL
c++
glm
glfw

*****

## Purpose

This project is for learning the basics of OpenGL, which is multi-cross platform, and it will be extended for my personal uses. 
Currently, I am working on the structure of the software design, and I will add more features to enhance my personal efficiency. 
The main features will be to highlight the information of the models I import with this engine, and modify file format, animations and to test shaders. 

*****

--  How do I work it? --

Parses common model files with ASSIMP. 

Uses string streams to separate data out, Position, Normal and Texcoord currently.

Everything gets stored in temp vectors of glm vecs 2 and 3;
It keeps track of the file path and tries to find mtl file automatically

During a face parsing, the algorithm will check if the faces are triangulated and if not, it will proceed to triangulate and output the new indices to temp vectors
Vertices(positions) & normal get uncompressed with the newly generated indices;

Then the vertices are inputted into a Vertex and then into a Vertex array inside the mesh (more info below)
Now these Vertex structs will be put through a unordered map (hash table) o Hash table will store any unique vertex objects and with a value of vertices vector (starts of 0 and increments). o The unique index gets pushed to temp vector o Also the unique vertex get stored into another temp vector o If a Vertex is not unique than it will get pushed into index vector with a retrieved int value from the hash table

*****

--  What I want to learn from OpenGL --

By parsing graphic datas, it could give general understanding of data management in graphic pipele. This project is currently at the base stage, and I will add vertex info UI with ImGui, 
and particle system to understanding the movement of data in 3d space.

*****

![Alt text](/resource/img/EngineProject.PNG)