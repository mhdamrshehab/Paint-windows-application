#ifndef FINALPROJECTCOMPUTERGRAPHICS_Circle_H
#define FINALPROJECTCOMPUTERGRAPHICS_Circle_H

#include "MyUtilities.h"
#include "Line.h"

// Circle
void DrawCirclePolorSimilarity(HDC hdc, Point pStart, int R, COLORREF c) {
    double dtheta = 1.0 / R; // Calculate the change in angle per pixel distance from the center
    double x = R, y = 0, theta = 0; // Set initial values for x, y, and angle
    Draw8Points(hdc, pStart, R, 0, c); // Draw the first set of points at (R,0) and its 8 symmetrical points

    // Iterate while the x-coordinate is greater than the y-coordinate
    while (x > y) {
        theta += dtheta; // Increment the angle
        x = R * cos(theta); // Calculate the new x-coordinate
        y = R * sin(theta); // Calculate the new y-coordinate
        Draw8Points(hdc, pStart, round(x), round(y), c); // Draw the eight symmetrical points for the new coordinates
    }
}

void DrawCircleIterativePolar(HDC hdc, Point pStart, int R, COLORREF c) {
    // Calculate the change in theta per pixel.
    double dtheta = 1.0 / R;

    // Initialize the starting point of the circle.
    double x = R, y = 0;

    // Pre-calculate the cosine and sine of the change in theta.
    double ct = cos(dtheta), st = sin(dtheta);

    // Draw the first 8 points of the circle.
    Draw8Points(hdc, pStart, x, y, c);

    // Iteratively calculate the next set of points until the entire circle is drawn.
    while (x > y) {
        // Calculate the next point using the polar equation for a circle.
        x = x * ct - y * st;
        y = x * st + y * ct;

        // Draw the next set of points.
        Draw8Points(hdc, pStart, round(x), round(y), c);
    }
}

void DrawCircleDirect(HDC hdc, Point pStart, int R, COLORREF c) {
    // Initialize starting values for x and y
    int x = 0;
    double y = R;
    // Draw the initial set of points using Draw8Points
    Draw8Points(hdc, pStart, x, y, c);
    // Loop while x is less than y
    while (x < y) {
        // Increment x and calculate the corresponding y value
        x++;
        y = sqrt(R * R - x * x);
        // Draw the new set of points using Draw8Points
        Draw8Points(hdc, pStart, x, round(y), c);
    }
}

void DrawCircleBresenhamMidPoint(HDC hdc, Point pStart, int R, COLORREF c) {
    // Initialize starting values of x and y
    int x = 0, y = R;
    // Draw the first set of 8 points
    Draw8Points(hdc, pStart, x, y, c);
    // Loop until x is equal to or greater than y
    while (x < y)
    {
        // Calculate the value of d using the Bresenham's algorithm formula
        int d = 4 * (x + 1) * (x + 1) + (2 * y - 1) * (2 * y - 1) - 4 * R * R;
        // If d is less than 0, increment x
        if (d < 0) {
            x++;
        }
        // If d is greater than or equal to 0, increment x and decrement y
        else
        {
            x++;
            y--;
        }
        // Draw the set of 8 points for the current x and y values
        Draw8Points(hdc, pStart, x, y, c);
    }
}

void DrawCircleBresenhamImproveI(HDC hdc, Point pStart, int R, COLORREF c)
{
    int x = 0, y = R;    // Set initial values for x and y
    int d = 1 - R;       // Initialize the decision variable
    Draw8Points(hdc, pStart, x, y, c);  // Draw the first 8 points

    while (x < y) {  // Continue until the entire circle is drawn
        if (d < 0) {  // Check if the decision variable is less than zero
            d += 2 * x + 3;  // Update the decision variable
            x++;  // Increment x
        }
        else {  // If the decision variable is greater than or equal to zero
            d += 2 * (x - y) + 5;  // Update the decision variable
            x++;  // Increment x
            y--;  // Decrement y
        }
        Draw8Points(hdc, pStart, x, y, c);  // Draw the current 8 points
    }
}

void DrawCircleBresenhamImproveII(HDC hdc, Point pStart, int R, COLORREF c) {
    int x = 0, y = R; // Initialize x and y to the starting point of the circle
    int d = 1 - R; // Initialize the decision variable
    int d1 = 3, d2 = 5 - 2 * R; // Initialize the values of d1 and d2
    Draw8Points(hdc, pStart, x, y, c); // Draw the first eight points of the circle

    // Loop until the x-coordinate becomes greater than or equal to the y-coordinate
    while (x < y) {
        if (d < 0) {
            // If the decision variable is less than 0, update d and d2
            d += d1;
            d2 += 2;
        }
        else {
            // If the decision variable is greater than or equal to 0, update d, y, and d2
            d += d2;
            y--;
            d2 += 4;
        }
        x++; // Increment x
        d1 += 2; // Update d1
        Draw8Points(hdc, pStart, x, y, c); // Draw the eight points of the circle at the current (x, y) position
    }
}

// Filling Circle
void FillingCircleWithLines(HDC hdc, Point pStart, int R, int Q, double ratio, COLORREF c) {
    double dTheta = 5.0 / R;
    double theta = (Q - 1) * ratio;
    while (theta < Q * ratio) {
        double x = pStart.x + R * cos(theta);
        double y = pStart.y + R * sin(theta);
        DrawLine(hdc, Line(pStart, Point(round(x), round(y))), c);
        theta += dTheta;
    }
}

void FillingCircleWithCircles(HDC hdc, Point pStart, int R, int Q, double ratio, COLORREF c) {
    double R2 = R;
    double x = pStart.x + R2 * cos((Q - 1) * ratio);
    double y = pStart.y + R2 * sin((Q - 1) * ratio);
    double dTheta = 1.0 / R2;
    DrawLine(hdc, Line(pStart, Point(round(x), round(y))), c);
    while (R2 > 0) {
        for (double theta = (Q - 1) * ratio; theta < Q * ratio; theta += dTheta) {
            x = pStart.x + R2 * cos(theta);
            y = pStart.y + R2 * sin(theta);
            SetPixel(hdc, round(x), round(y), c);
        }
        R2 -= 6;
    }
    x = pStart.x + R * cos(Q * ratio);
    y = pStart.y + R * sin(Q * ratio);
    DrawLine(hdc, Line(pStart, Point(round(x), round(y))), c);
}

#endif
