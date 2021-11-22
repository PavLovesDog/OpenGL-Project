#version 410 core
in vec4 gl_FragCoord;

in vec3 ourColor; // from .vert
in vec2 TexCoord; // from .vert
uniform sampler2D ourTexture;
uniform sampler1D texture;
 
out vec4 frag_color;
out float gl_FragDepth;
 
// for zoom and pan
uniform float centerX;
uniform float centerY;
uniform float zoom;


// colour variation from other site
uniform vec4 color_ranges;

// for funky colour setting
uniform vec4 startColour;
uniform vec4 endColour;

#define MAX_ITERATIONS 500
 
int generate_mandlebrot()
{
    vec2 c, d;
    c.x = ((gl_FragCoord.x / 1500.0 - 0.5) * zoom + centerX ) * 5.0; // c.real number
    c.y = ((gl_FragCoord.y / 850.0 - 0.6) * zoom + centerY ) * 5.0; // c.imaginary number
 
    int iterations = 0;
    d = c; // assign d vec 2 for original values
 
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


vec4 generate_color()
{
    int iter = generate_mandlebrot();
    
    //return texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    //return texture1D(texture, (i == iter ? 0.0 : float(i)) / 100.0);

    //if (iter == MAX_ITERATIONS)
    //{
    //    gl_FragDepth = 0.0f;
    //    return vec4(0.8f, 0.0f, 0.5f, 1.0f); // inside colour
    //}
    //
    //float c = sqrt(float(i) / float(MAX_ITERATIONS)) / 2;
    //float x = (cos(startColour.x) / c / sin(endColour.x)) / tan(c) / sin(12.0);
    //float y = (sin(startColour.y) / c / tan(endColour.y)) / sin(c) / cos(22.0);
    //float z = (tan(startColour.z) / c / cos(endColour.z)) / cos(c) / tan(32.0);
    ////gl_FragDepth = iter / 2;
    //
    //return vec4(cos(x), sin(y), sin(z) , 1.0);
    
    if (iter == MAX_ITERATIONS)
    {
        gl_FragDepth = 0.0f;
        return vec4(0.8f, 0.1f, 0.1f, 0.5f); // inside colour
    }
    
    
    float iterations = float(iter) / MAX_ITERATIONS;    
    gl_FragDepth = iterations;
    return vec4(0.2f, iterations, 0.3f, 1.0f); // OLD background colour

    
    //                  R  ,  G  ,  B  ,  Opacity
    vec4 color0 = vec4(0.0f, 0.6f, 0.0f, 1.0f); // Green
    vec4 color1 = vec4(0.5f, 0.0f, 0.0f, 1.0f); // Red
    vec4 color2 = vec4(0.0f, 0.8f, 0.7f, 1.0f); // Blue
    vec4 color3 = vec4(0.2f, 0.0f, 0.2f, 1.0f); // White
    
    float fraction = 0.5f;
    if (iterations < color_ranges[0])
    {
         fraction = (iterations - color_ranges[0]) / (color_ranges[1] - color_ranges[0]);
         return mix(color0, color1, fraction);
    }
    else if (iterations < color_ranges[1])
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