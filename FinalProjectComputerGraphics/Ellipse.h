#ifndef FINALPROJECTCOMPUTERGRAPHICS_ELLIPSE_H
#define FINALPROJECTCOMPUTERGRAPHICS_ELLIPSE_H

#include "MyUtilities.h"

// This function draws an ellipse using the Cartesian equation and the Draw4Points function
// The ellipse is centered at the point pStart, and has major and minor axis lengths A and B respectively
// The ellipse is drawn using the specified color
void DrawEllipseCart(HDC hdc, Point pStart, int A, int B, COLORREF c) {
    int x = 0;
    double y = B;
    Draw4Points(hdc, pStart.x, pStart.y, 0, B, c);
    while (x * B * B < y * A * A)
    {
        x++;
        y = B * sqrt(1.0 - (double)x * x / (A * A));
        Draw4Points(hdc, pStart.x, pStart.y, x, Round(y), c);
    }
    int y1 = 0;
    double x1 = A;
    Draw4Points(hdc, pStart.x, pStart.y, A, 0, c);
    while (x1 * B * B > y1 * A * A)
    {
        y1++;
        x1 = A * sqrt(1.0 - (double)y1 * y1 / (B * B));
        Draw4Points(hdc, pStart.x, pStart.y, Round(x1), y1, c);
    }
}

// This function draws an ellipse on a given device context using the polar form of the ellipse equation
// The ellipse is centered at the point pStart, and has major and minor axis lengths A and B respectively
// The ellipse is drawn using the specified color c
void DrawEllipsePolar(HDC hdc, Point pStart, int A, int B, COLORREF c)
{
    double x = A, y = 0, theta = 0, dtheta = 1.0 / max(A, B);  // Initialize variables for drawing points on the ellipse
    Draw4Points(hdc, pStart.x, pStart.y, x, y, c);  // Draw first point on ellipse at (x,y)=(A,0)

    // Iterate through all angles between 0 and 2*pi, and draw points on the ellipse
    while (x > 0) {
        theta += dtheta;                    // Increment angle
        x = A * cos(theta);                   // Calculate x-coordinate based on polar equation
        y = B * sin(theta);                   // Calculate y-coordinate based on polar equation
        Draw4Points(hdc, pStart.x, pStart.y, x, y, c);  // Draw points on the ellipse
    }
}

// This function draws an ellipse on a given device context using an iterative polar algorithm
// The ellipse is centered at the point pStart, and has major and minor axis lengths A and B respectively
// The ellipse is drawn using the specified color c
void DrawEllipseIterativePolar(HDC hdc, Point pStart, int A, int B, COLORREF c)
{
    double x = A, y = 0, dtheta = 1.0 / max(A, B);   // Initialize variables for drawing points on the ellipse
    double ct = cos(dtheta), st = sin(dtheta);

    // Iterate through all angles between 0 and 2*pi, and draw points on the ellipse
    while (x > 0) {
        double x1 = (x * ct) - (A * y * st / B);   // Calculate new x-coordinate based on iterative polar equation
        y = (B * x * st / A) + (y * ct);           // Calculate new y-coordinate based on iterative polar equation
        x = x1;                          // Update x-coordinate
        Draw4Points(hdc, pStart.x, pStart.y, Round(x), Round(y), c);  // Draw points on the ellipse
    }
}

// This function draws an ellipse with center at point pStart,
// with horizontal and vertical radii A and B respectively,
// using the midpoint ellipse algorithm, and with color 'color'
void DrawEllipseMidPoint(HDC hdc, Point pStart, int A, int B, COLORREF color)
{
    // Initialize the starting points of the algorithm
    int x = 0;
    int y = B;
    int Apow = A * A;
    int Bpow = B * B;
    // Calculate the initial value of the decision parameter delta
    int delta = (-4 * Apow * Bpow) + (4 * Apow * y * y) + (4 * Bpow * x * x) - (4 * Apow * y) + (8 * Bpow * x) + Apow + (4 * Bpow);

    // Iterate until the slope of the ellipse becomes greater than -1
    while (Apow * (2 * y - 1) > 2 * Bpow * (x + 1))
    {
        // Plot the current point and its symmetrical counterparts
        Draw4Points(hdc, pStart.x, pStart.y, x, y, color);
        // Check if the midpoint is inside or outside the ellipse
        if (delta < 0)
        {
            // If the midpoint is inside the ellipse, move to the right
            x++;
            // Update delta for the new point
            delta += 4 * Bpow * (2 * x + 3);
        }
        else
        {
            // If the midpoint is outside the ellipse, move diagonally up and to the right
            x++;
            delta += 4 * Bpow * (2 * x + 3) - 8 * Apow * (y - 1);
            y--;
        }
    }

    // Calculate the initial value of the decision parameter delta for the next iteration
    delta = Bpow * ((2 * x + 1) * (2 * x + 1)) + 4 * Apow * ((y + 1) * (y + 1)) - 4 * Apow * Bpow;

    // Iterate until the slope of the ellipse becomes less than or equal to -1
    while (y + 1 != 0)
    {
        // Plot the current point and its symmetrical counterparts
        Draw4Points(hdc, pStart.x, pStart.y, x, y, color);
        // Check if the midpoint is inside or outside the ellipse
        if (delta < 0)
        {
            // If the midpoint is inside the ellipse, move diagonally up and to the right
            y--;
            delta += 4 * Apow * (2 * y + 3);
        }
        else
        {
            // If the midpoint is outside the ellipse, move to the right
            y--;
            delta += 4 * Apow * (2 * y + 3) - 8 * Bpow * (x + 1);
            x++;
        }
    }
}


#endif //FINALPROJECTCOMPUTERGRAPHICS_ELLIPSE_H
