/*
    This fragment shader script processes a single fragment by taking in a set of colours & depth value,
    it then performs the operations below on the fragment and outputs it with new coordinates and color data. 
    this happens after the rasterization stage on the OpenGL pipeline.
    for every fragment, or pixel, on the screen, this code will run through the GPU. i.e 1 million pixels == 1 million runs
    This happens in parrallel, and needs to be run once for every pixel, because pixels are "blind" to one another and will not
    communicate between themsleves.
*/

#version 330 core

in vec4 gl_FragCoord; // take in vertex position
out vec4 frag_color; // send out the fragment colour
 
// ZOOM & PAN
uniform float centerX;
uniform float centerY;
uniform float zoom;

// COLOUR
out float gl_FragDepth;
uniform vec4 color_ranges;

#define MAX_ITERATIONS 1000 // determine depth of detail
 
int generate_mandlebrot()
{
    // set up real and imaginary positions
    vec2 c, d;
    c.x = ((gl_FragCoord.x / 1500.0 - 0.5) * zoom + centerX ) * 5.0; // c.real number
    c.y = ((gl_FragCoord.y / 850.0 - 0.6) * zoom + centerY ) * 5.0; // c.imaginary number
 
    //d = c; // assign d vec 2 for original values
    // let d = 0 for first complex iteration
    d.x = 0.0;
    d.y = 0.0;
    int iterations = 0;
 
    while (iterations < MAX_ITERATIONS)
    {
        
        float a = (d.x * d.x - d.y * d.y) + c.x;
        float b = (d.y * d.x + d.x * d.y) + c.y;
         
        float distance = (a * a + b * b);
         
        if (distance > 5.0) break;
        d.x = a;
        d.y = b; 
 
        iterations++;
    }
    return iterations;
}


vec4 generate_colour()
{
    int iter = generate_mandlebrot();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragDepth = 0.0f;
        return vec4(0.1f, 0.1f, 0.1f, 0.5f); // inside colour
    }

    float iterations = float(iter) / MAX_ITERATIONS;    
    gl_FragDepth = iterations;
    //return vec4(0.2f, iterations, 0.3f, 1.0f); // edge of Mandlebrot set colour GIVE US 3 COLOURS

    // COLOUR USING THE COLOR_RANGES, UPDATED AND SET IN MAIN WHILE LOOP WITH glReadPixels() & assigning to "ranges"
    //                    R  ,  G  ,  B  ,  Opacity
    // CMYK - colour setting
    vec4 color0 = vec4(0.0f, 1.0f, 1.0f, 1.0f); // Background-Colour: Cyan
    vec4 color1 = vec4(1.0f, 0.0f, 1.0f, 1.0f); // Outer-Colour     : Magenta
    vec4 color2 = vec4(1.0f, 1.0f, 0.0f, 1.0f); // Inner-Colour     : Yellow
    vec4 color3 = vec4(1.0f, 0.0f, 1.0f, 1.0f); // Edge-Colour      : Magenta
    vec4 color4 = vec4(0.0f, 1.0f, 1.0f, 1.0f); // inner edge-colour: Cyan
    
    float fraction = 0.0f;
    if (iterations < color_ranges[1])
    {
         fraction = (iterations - color_ranges[0]) / (color_ranges[1] - color_ranges[0]);
         return mix(color0, color2, fraction);
    }
    else if (iterations < color_ranges[2])
    {
        fraction = (iterations - color_ranges[1]) / (color_ranges[2] - color_ranges[1]);
        return mix(color1, color2, fraction);
    }
    else if (iterations < color_ranges[3])
    {
        fraction = (iterations - color_ranges[2]) / (color_ranges[3] - color_ranges[2]);
        return mix(color4, color3, fraction);
    }
    else
    {
        fraction = (iterations - color_ranges[2]) / (color_ranges[3] - color_ranges[2]);
        return mix(color2, color3, fraction);
    }
}
 
void main()
{
    frag_color = generate_colour();
}