#version 330 core
in vec4 gl_FragCoord;
 
out vec4 frag_color;
out float gl_FragDepth;
 
uniform float centerX;
uniform float centerY;
uniform float zoom;
uniform vec4 color_ranges;

#define MAX_ITERATIONS 500
 
int generate_mandlebrot()
{
    vec2 c, d;
     c.x = ((gl_FragCoord.x / 1500.0 -0.5) * zoom + centerX ) * 4.0; // c.real number
     c.y = ((gl_FragCoord.y / 850.0 - 0.6) * zoom + centerY ) * 4.0; // c.imaginary number
 
    int iterations = 0;
    d = c; // assign d vec 2 for original values
 
    while (iterations < MAX_ITERATIONS)
    {
        
        float x = (d.x * d.x - d.y * d.y) + c.x;
        float y = (d.y * d.x + d.x * d.y) + c.y;
         
        float distance = (x * x + y * y);
         
        if (distance > 4.0) break;
        d.x = x;
        d.y = y; 
 
        iterations++;
    }
    return iterations;
}


vec4 generate_color()
{
    int iter = generate_mandlebrot();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragDepth = 0.0f;
        return vec4(0.8f, 0.0f, 0.5f, 1.0f); // inside colour
    }
 
    float iterations = float(iter) / MAX_ITERATIONS;    
    //return vec4(0.0f, iterations, 0.0f, 1.0f); // background colour
    gl_FragDepth = iterations;

    //                  R  ,  G  ,  B  ,  Opacity
    vec4 color0 = vec4(0.3f, 0.8f, 0.0f, 1.0f); // Red
    vec4 color1 = vec4(1.0f, 0.2f, 0.0f, 1.0f); // Green
    vec4 color2 = vec4(1.0f, 0.8f, 0.0f, 1.0f); // Blue
    vec4 color3 = vec4(0.2f, 1.0f, 0.2f, 1.0f); // White

    float fraction = 0.0f;
    if (iterations < color_ranges[1])
    {
         fraction = (iterations - color_ranges[0]) / (color_ranges[1] - color_ranges[0]);
         return mix(color0, color1, fraction);
    }
    else if (iterations < color_ranges[2])
    {
        fraction = (iterations - color_ranges[1]) / (color_ranges[2] - color_ranges[1]);
        return mix(color1, color2, fraction);
    }
    else
    {
        fraction = (iterations - color_ranges[2]) / (color_ranges[3] - color_ranges[2]);
        return mix(color2, color3, fraction);
    }
}
 
void main()
{
    frag_color = generate_color();
}