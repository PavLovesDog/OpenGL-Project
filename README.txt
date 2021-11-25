TO DO:
	#1 write up comments on the frag & vertex shader stating how each vertex has this code run on it through the GPU
	   therefore, running concurrently on all the GPUs cores ======== NEEDS ELABORATION

	#2 try and implement it to run only within main (i.e on the CPU)
		- time & graph/plot differences

	#3 begin draft of GPGPU operations
 		-a small Report: Explain technology for GPGPU ie. computer shaders(used via opengl),
				 short essay format is fine (probably around 300-400 words).
___________
Submission
1. report explaining tech for GPGPU i.e Compute shader (used via OpenGL)
	- why do we need compute shader?
	- why do we need openGL?
	- how GPU programming works vs CPU programming

	- explain what my program is
	- what will be seeing/ what expect to see
2. solution code (my mandlebrot solution),

=================================
 Explanation & using the program
=================================
With my project I used an online tutorial to help set up my own OpenGl project to help me better understand the workings 
of openGL and how the shaders (vertex and Fragment) operate within the context of openGL!

Note*** -EBO, VBO, VAO & shaderClass Header and CPP files for OpenGL setup were demonstrated on the
	 OpenGL Course - Create 3D and 2D Graphics With C++ referenced below, I merely coded along to 
	 the video to construct them.

	-the default.vert & default.frag shaders were setup with the same video, then manipulated by me 
	 with the other resources referenced below to get my desired output.

Using the program:
-Arrow keys to pan
'+' & '-' keys on the NumPad to zoom in & out, respectively.


=============
   Report
=============
______
GPGPU
- What is it?
General Purpose Graphics Processing Unit(GPU), is a processing unit which performs calculations with great parallelism, due
to its many cores, which would otherwise run through the CPU.
Namely, the GPU is dedicated to graphics rendering.

- why do we use it?
Unlike the CPU, the GPU was designed to calculate vast sums of calculations in parallel, so for displaying graphics to a screen
the GPU can handle the necessary tasks quickly and efficiently, without taxing the CPU or other resources 
(such as battery-life for mobile devices).

- why do we need it?
Thousands to millions of calculations are performed every second over the many cores of the GPU, this enables the display 
on your device to be constantly updated and provide a clean, smooth viewing experience. without a GPU, modern day graphics
would greatly hinder the CPU & we'd probably all be outside looking at nature instead 

____________________________________
CPU vs. GPU - WHat's the difference?
CPUs and GPUs are designed for specific purposes.
The CPU architecture is designed to handle a wide range of tasks sequentially. that is, it has a few heavyweight cores and large
memory size for task-parallelism with high clock speeds. This gives the illusion of parallelism, but is essentially only running
one task at a time.
The GPU architecture is throughput-optimized for high-end parallel computing, be it for graphical computing, machine-learning or
scientific computation. it is comprised of thousands of lightweight cores for high memory throughput and data parallelism. 
The GPU is optimized for dimensional matrix arithmetic and floating point calculations.


_______________
GPU Pros & Cons
- arithmetic complexity: designed for small set calculations such as linear algebra
- high parallelism: designed to rapidly manipulate huge chunks of data all at once.
- GPU memory limits: memory access has high latency
- 

_____________________________
Graphics Pipeline - explained
- all stages
- programmable stages

______________
Compute Shader
-what is?
-how does it fit in to the Graphics Pipeline?

______
OpenGL
- how openGL works & where?
- why do we need openGL & compute shades?

_____________
My Program :)
-explaon the mandlebrot
- how is my .vert & .frag run in parallel for each pixel?
- how OpenGl handles the Graphics pipeline






============
 REFERENCES
============

_______________________________________________________
*** OpenGL library set up sourced from freeCodeCamp.org

Vid: OpenGL Course - Create 3D and 2D Graphics With C++
Link: https://www.youtube.com/watch?v=45MIykWJ-C4

________________________________
*** OpenGL General help sourced:

https://learnopengl.com/Getting-started/Textures

___________________________________________________________________________________________________________________________
*** FRAGMENT SHADER code sourced from assessment steps "algorithm for the Mandlebrot set" & multiple online demonstrations:

https://physicspython.wordpress.com/2020/02/16/visualizing-the-mandelbrot-set-using-opengl-part-1/
&&
https://www.brennengreen.dev/blog/posts/1/
&&
http://nuclear.mutantstargoat.com/articles/sdr_fract/

_____________________________________________________________________
*** PAN/ZOOM controls & PIXEL COLOUR code implemented & sourced from:

https://physicspython.wordpress.com/2020/03/04/visualizing-the-mandelbrot-set-using-opengl-part-2/