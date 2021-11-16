#version 330 core
in vec4 gl_FragCoord

out vec4 fragmentColor;

#define MAX_ITERATIONS 500

int produce_mandlebrot()
{
	float cReal = (gl_FragCoord.x / 800.0 - 0.5) * 4.0;
	float cImaginary = (gl_FragCoord.y / 800.0 - 0.7) * 4.0;

	int numIterations = 0;
	float constReal = cReal;
	float constImaginary = cImaginary;

	while (numIterations < MAX_ITERATIONS)
	{
		float temp = cReal;
		cReal = (cReal * cReal - cImaginary * cImaginary) + constReal;
		cImaginary = (2.0 * temp * cImaginary) + constImaginary;

		float distance = cReal * cReal + cImaginary * cImaginary;

		if (distance > 4.0)
			break;

		++numIterations;
	}
	return numIterations;
}

vec4 colourFragment()
{
	int totalIterations = produce_mandlebrot();
	if (totalIterations == MAX_ITERATIONS)
	{
		gl_FragDepth = 0.0f;
		return vec4(0.0f, 0.0f, 0.0f, 1.0f); // black
	}

	float iterations = float(totalIterations) / MAX_ITERATIONS;
	return vec4(0.0f, iterations, 0.0f, 1.0f);
}

void main()
{
	fragmentColor = colourFragment();
}