#ifndef FINALPROJECTCOMPUTERGRAPHICS_BEZIERCURVE_H
#define FINALPROJECTCOMPUTERGRAPHICS_BEZIERCURVE_H

#include "MyUtilities.h"
#include "Line.h"


class BezierCurve {
public:
    int n;
    Point* p;
    BezierCurve(Point* P, int s) {
        p = P;
        n = s;
    }

    Point deCasteljau(double t)
    {
        
        // Initialize a new array of points q with the same values as p
        Point* q = new Point[n];
        for (int i = 0; i < n; i++)
        {
            q[i] = p[i];
        }
        // Remember to delete the dynamically allocated array when you're done with it:
        delete[] q;
        // Perform De Casteljau's algorithm to compute the point on the curve
        for (int j = 1; j < n; j++)
        {
            for (int i = 0; i < n - j; i++)
            {
                // Calculate the next point on the curve using the previous two points
                q[i].x = (1 - t) * q[i].x + t * q[i + 1].x;
                q[i].y = (1 - t) * q[i].y + t * q[i + 1].y;
            }
        }

        // The final point in the q array is the point on the curve corresponding to the given parameter value
        return q[0];
    }

    void drawBezier(HDC hdc, Window W, COLORREF c)
    {
        // Set the time step for the Bézier curve calculation
        double dt = 0.001;

        // Initialize the starting point for drawing the curve
        Point q1, q2;
        q1 = p[0];

        // Calculate points along the Bézier curve and draw line segments between them
        for (double t = dt; t <= 1; t += dt) {
            // Calculate the next point on the curve using De Casteljau's algorithm
            q2 = deCasteljau(t);
            // Draw a line segment from the previous point to the current point on the curve
            if (PointClipping(Point(q2.x, q2.y), W))
                DrawLineMidPoint(hdc, q1.x, q1.y, q2.x, q2.y, c);
            // Update the starting point for the next line segment
            q1 = q2;
        }
    }

    // Draws a Bézier curve using the given array of control points
    // hdc: handle to the device context
    // p: an array of control points defining the Bézier curve
    // n: the number of control points in the array p
    // c: the color to use for drawing the curve
    void drawBezier(HDC hdc, COLORREF c)
    {
        // Set the time step for the Bézier curve calculation
        double dt = 0.01;

        // Initialize the starting point for drawing the curve
        Point q1, q2;
        q1 = p[0];

        // Calculate points along the Bézier curve and draw line segments between them
        for (double t = dt; t <= 1; t += dt)
        {
            // Calculate the next point on the curve using De Casteljau's algorithm
            q2 = deCasteljau(t);

            // Draw a line segment from the previous point to the current point on the curve
            DrawLine(hdc, q1.x, q1.y, q2.x, q2.y, c);

            // Update the starting point for the next line segment
            q1 = q2;
        }
    }

    void PlusY(int y) {
        p[0].y += 5;
        p[1].y += 5;
        p[2].y += 5;
        p[3].y += 5;
    }
};

void FillingBezier(HDC hdc, Point* p, int n, Window W, COLORREF c) {
    BezierCurve curve(p, n);
    for (int y = W.Top; y <= W.Bottom; y++) {
        curve.drawBezier(hdc, W, c);
        curve.PlusY(5);
    }
}

#endif
