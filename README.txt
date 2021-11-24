TO DO:
	#1 write up comments on the frag & vertex shader stating how each vertex has this code run on it through the GPU
	   therefore, running concurrently on all the GPUs cores

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


=============
   Report
=============
______
GPGPU
- what is it?
- why do we use it?
- why do we need it?

____________________________________
CPU vs. GPU - WHat's the difference?


_______________
GPU Pros & Cons
- arithmetic complexity
- high parallelism
- GPU memory - limitation?

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