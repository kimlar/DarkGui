#pragma once

#include <SDL.h>

// Draw one quadrant arc, and mirror the other 4 quadrants
void DrawEllipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY)
{
	double pi = 3.14159265358979323846264338327950288419716939937510;
	double pih = pi / 2.0; // Half of pi

	/*
		Drew  28 lines with   4x4  circle with precision of 150 0ms
		Drew 132 lines with  25x14 circle with precision of 150 0ms
		Drew 152 lines with 100x50 circle with precision of 150 3ms
	*/
	const int prec = 27; // Precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
	double theta = 0.0;     // Angle that will be increased each loop

	// Starting point
	int x = (int)((double)radiusX * cos(theta)); // Start point
	int y = (int)((double)radiusY * sin(theta)); // Start point
	int x1 = x;
	int y1 = y;

	// Repeat until theta >= 90;
	double step = pih / (double)prec; // Amount to add to theta each time (degrees)
	for (theta = step; theta <= pih; theta += step) // Step through only a 90 arc (1 quadrant)
	{
		// Get new point location
		x1 = (int)((double)radiusX * cos(theta) + 0.5); // New point (+.5 is a quick rounding method)
		y1 = (int)((double)radiusY * sin(theta) + 0.5); // New point (+.5 is a quick rounding method)

		// Draw line from previous point to new point, ONLY if point incremented
		if ((x != x1) || (y != y1)) // Only draw if coordinate changed
		{
			SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1); // Quadrant TR
			SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1); // Quadrant TL
			SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1); // Quadrant BL
			SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1); // Quadrant BR
		}
		// Save previous points
		x = x1; // Save new previous point
		y = y1; // Save new previous point
	}
	// Arc did not finish because of rounding, so finish the arc
	if (x != 0)
	{
		x = 0;
		SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1); // Quadrant TR
		SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1); // Quadrant TL
		SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1); // Quadrant BL
		SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1); // Quadrant BR
	}
}
