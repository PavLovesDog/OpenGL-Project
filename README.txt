=================================
 Explanation & using the program
=================================
Because I started early on my assessment, for my project I used an online tutorial to help set up my own OpenGl 
project to help me better understand the workings of openGL and how the shaders (vertex and Fragment) operate within the context of openGL!
I did this before we were provided sample code within class so rather than start again on a new project I decided to use 
what I had already made as my base.

Although Compute Shaders were discussed heavily in classes, I've elected to forgo the use of one for the generation of my Mandlebrot Set,
as my base was working without a Compute Shader and added levels of complication I couldn't work around to get my Mandlebrot set functioning
again.

ALSO you'll probably need to re-set the 'libraries' and 'includes' directories in the Properties menu (found in the Debug dropdown menu)
     under Configuration Properties -> VC++ Directories -> General -> Include Directories & Library Directories 
	change these to the 'lib' and 'include' folders in your projects extracted location.


Note*** -EBO, VBO, VAO & shaderClass Header and CPP files for OpenGL setup were demonstrated on the
	 OpenGL Course - Create 3D and 2D Graphics With C++ referenced below, I merely coded along to 
	 the video to construct them.

	-the default.vert & default.frag shaders were setup with the same video, then manipulated by me 
	 with the other resources referenced below to get my desired output.

Using the program:
-Arrow keys to pan
'+' & '-' keys on the NumPad to zoom in & out, respectively.



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