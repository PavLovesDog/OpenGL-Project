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
	
	-Geberal processing ON a GPU, things coded to be optimized on the GPU, which would otherwise run on the CPU

	- explain what my program is
	- what will be seeing/ what expect to see
2. solution code (my mandlebrot solution),

=================================
 Explanation & using the program
=================================
Because I started early on my assessment, for my project I used an online tutorial to help set up my own OpenGl 
project to help me better understand the workings of openGL and how the shaders (vertex and Fragment) operate within the context of openGL!
I did this before we were provided sample code within class so rather than start again on a new project I decided to use 
what I had already made as my base.

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
-------
 GPGPU
-------
- What Is It? -
General Purpose Graphics Processing Unit(GPU), is a processing unit which performs general calculations with great parallelism, 
due to its many cores, which would otherwise run through the CPU.
Usually, the Graphics Processing Unit(GPU) is dedicated to graphics rendering.
However, the term GPGPU came about when code began to be optimized to run through the GPU rather than CPU. As the technology
and need for software parallelism grew, the CPU quickly became unable to keep up due to its sequential nature, where the GPU
could handle massive amounts of data as long as the code was written for its architecture.
*prevalently this is within the areas of machine learning (A.I), crypto-mining, graphics-processing (the GPUs original function),
scientific computations & other physics calculations. 

- Why Do We Use It? -
Unlike the CPU, the GPU was designed to calculate vast sums of calculations in parallel, so for displaying graphics to a screen
the GPU can handle the necessary tasks quickly and efficiently, without taxing all resources, where the CPU would be left behind
trying to solve all graphics equations sequentially. 
We use this technology to handle massive amounts of data which require specific tasks, or similar calculations performed on
every set of data (such as linear algebra, floating-point clculations etc.), that need to be solved simultaneuosly for correct
& smooth data output of the program running the code.

- Why Do We Need It? -
Thousands to millions of calculations are performed every second over the many cores of the GPU, this enables the display 
on your device to be constantly updated and provide a clean, smooth viewing experience. without a GPU, modern day graphics
would greatly hinder the CPU & we'd probably all be outside looking at nature instead.
We need General Purpose Graphics Processing Unit programming for the ever growing demand for better graphics and the exploration into
better, 'smarter' technology for the uses stated above (look for the *) 

--------------------------------------
 CPU vs. GPU - What's The Difference?
--------------------------------------
CPUs and GPUs are designed for specific purposes.
The CPU architecture is designed to handle a wide range of tasks sequentially. that is, it has a few large cores and large
memory size for task-parallelism with high clock speeds. This gives the illusion of parallelism, but is essentially only running
one task at a time.
The GPU architecture is throughput-optimized for high-end parallel computing, be it for graphical computing, machine-learning or
scientific computation. it is comprised of thousands of tiny cores for high memory throughput and data parallelism. 
The GPU is optimized for dimensional matrix arithmetic and floating point calculations.


-----------------
 GPU Pros & Cons
-----------------
- arithmetic complexity: designed for small set calculations such as linear algebra
- high parallelism: designed to rapidly manipulate huge chunks of data all at once.
- GPU memory limits: memory access has high latency

-------------------
 Graphics Pipeline
-------------------
The Graphics Pipeline(GP) consists of a few stages. these stages generally go as follows:
Vertex Specification -> Vertex Shader -> Vertex Post Processing -> Primitive Assembly -> Rasterization -> Fragment Shader -> Per Sample Operation -> Frame Buffer 
But, as programmers we focus on two stages called Vertex Processing(VP) & Fragment Processing(FP).
these are the 2 stages of the GP which are programmable and where we have control of what is rendered.
along with these stages there are also the Rasterization(R) stage and the Frame Buffer(FB). these are important as they slot in between our 
programmable stages.
The order: VP --> R --> FP --> FB
Once data is fed into the pipeline, The Vertex Processing begins with positional coordinates. first the Vertex Shader uses the date provided
and creates vertices within 3D space, then the Primitive Assembly joins those vertices in a pre-calculation to determine triangles, quads, lines or points.
once the primitives are assembled, the Rasterization then converts the calculations of vertices within 3D space into 2D set of pixels, or a raster.
this process is called multisampling and smoothing.
Next the Fragment Processing begins. The purpose of the FP is to provide colour data for pixels with the Fragment Shader via textures, alpha or depth data.
depending on the data fed into the Fragment Shader, the pixel becomes coloured and then is passed into the Frame Buffer where colours are blended 
and displayed.

----------------
 Compute Shader
----------------
The Compute Shader is a tool for GPGPU programming designed to distribute work on specified number of threads to run on the GPU.
This essentially opens up the power of the GPU for non-rendering purposes or tasks in a controllable way.
It can save the data its generated and return back through the graphic pipeline or read back to the CPU for further manipulation.
This is particularly handy for handling tasks like particle movement, where positions of vertices are constantly updated.
Though compute shader can handle rendering triangles and pixels, its generally reserved for tasks outside of the rendering stage.

--------
 OpenGL
--------
At its core, OpenGL(Open Graphics Library) is an application programming interface(API) for rendering 2D and 3D vector graphics.
It is a software interface into graphics hardware and is almost exclusively used with the GPU.
- why do we need openGL & compute shades? -
We need OpenGL, like any graphical API, for any graphics rendering we wish to do and would be hard pressed to do it without them.
As OpenGL follows a strict graphic pipeline and always outputs to the FrameBuffer, a Compute Shader is required to further manipulate
data flowing through the pipeline, if data is needed to be changed or updated.

_____________
My Program :)
-explain the mandlebrot
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
*** FRAGMENT SHADER code sourced from assessment brief steps "algorithm for the Mandlebrot set" & multiple online demonstrations:

https://physicspython.wordpress.com/2020/02/16/visualizing-the-mandelbrot-set-using-opengl-part-1/
&&
https://www.brennengreen.dev/blog/posts/1/
&&
http://nuclear.mutantstargoat.com/articles/sdr_fract/

_____________________________________________________________________
*** PAN/ZOOM controls & PIXEL COLOUR code implemented & sourced from:

https://physicspython.wordpress.com/2020/03/04/visualizing-the-mandelbrot-set-using-opengl-part-2/