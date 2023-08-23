#ifndef FINALPROJECTCOMPUTERGRAPHICS_Line_H
#define FINALPROJECTCOMPUTERGRAPHICS_Line_H

#include "MyUtilities.h"

class Line {
public:
    Point S, E;
    double slope;
    Line() {}

    Line(Point P1, Point P2) :S(P1), E(P2) {}

    Line(int X1, int Y1, int X2, int Y2) {
        S.x = X1, S.y = Y1;
        E.x = X2, E.y = Y2;
        slope = calcSlope();
    }

    double calcSlope() {
        return (double)(E.y - S.y) / (double)(E.x - S.x);
    }

};

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int dx = x2 - x1, dy = y2 - y1;
    int x, y;

    if (abs(dx) > abs(dy)) {
        if (dx < 0) {
            swap(x1, x2);
            swap(y1, y2);
        }
        x = x1, y = y1;
        SetPixel(hdc, x, y, c);
        while (x < x2) {
            x++;
            y = y1 + round(x - x1) * calcSlope(x1, y1, x2, y2);
            SetPixel(hdc, x, y, c);
        }
    }
    else {
        if (dy < 0) {
            swap(x1, x2);
            swap(y1, y2);
        }
        x = x1, y = y1;
        SetPixel(hdc, x, y, c);
        while (y < y2) {
            y++;
            x = x1 + round((y - y1) * (1 / calcSlope(x1, y1, x2, y2)));
            SetPixel(hdc, x, y, c);
        }
    }
}

void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    // Calculate the differences in x and y coordinates
    int dX = x2 - x1;
    int dY = y2 - y1;

    // Check if the line is steep or shallow
    if (abs(dX) >= abs(dY)) {
        // If the line is shallow, make sure we iterate from left to right
        if (dX < 0) {
            swap(x1, x2);
            swap(y1, y2);
        }

        // Calculate the slope of the line
        double m = (double)dY / (double)dX;
        double x = x1;
        double y = y1;

        // Draw the first pixel at the starting point
        SetPixel(hdc, x1, y1, c);

        // Iterate over the x coordinates and calculate the corresponding y coordinates
        while (x < x2) {
            x++;
            y += m;
            SetPixel(hdc, x, round(y), c); // Draw the pixel at the current (x, y) position
        }
    }
    else {
        // If the line is steep, make sure we iterate from bottom to top
        if (dY < 0) {
            swap(x1, x2);
            swap(y1, y2);
        }

        // Calculate the inverse slope of the line
        double mi = (double)dX / (double)dY;
        double x = x1, y = y1;

        // Draw the first pixel at the starting point
        SetPixel(hdc, x1, y1, c);

        // Iterate over the y coordinates and calculate the corresponding x coordinates
        while (y < y2) {
            y++;
            x += mi;
            SetPixel(hdc, round(x), y, c); // Draw the pixel at the current (x, y) position
        }
    }
}

void DrawLineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF C) {
    // Calculate the absolute differences in x and y coordinates of the line
    int dx = abs(x2 - x1), dy = abs(y2 - y1);

    // Determine the direction of the line by checking the sign of the differences
    int cx = x1 < x2 ? 1 : -1, cy = y1 < y2 ? 1 : -1;

    // Initialize the decision parameter and increments for updating the decision parameter
    int d, change1, change2;

    // Check if the slope of the line is less than or equal to 1 (i.e. x difference is greater than y difference)
    if (dx >= dy) {

        // Initialize the decision parameter and increments for updating the decision parameter for the case where slope <= 1
        d = 2 * dy - dx;
        change1 = 2 * (dy - dx);
        change2 = 2 * dy;

        // Initialize the starting point of the line
        int x = x1;
        int y = y1;

        // Set the first pixel of the line
        SetPixel(hdc, x1, y1, C);

        // Loop through each x coordinate and calculate the corresponding y coordinate
        while (x != x2) {

            // Update the decision parameter
            if (d < 0) {
                d += change2;
            }
            else {
                y += cy;
                d += change1;
            }

            // Move to the next x coordinate
            x += cx;

            // Draw the pixel at the corresponding y coordinate
            SetPixel(hdc, x, y, C);
        }
    }

    // If the slope of the line is greater than 1 (i.e. y difference is greater than x difference)
    else {

        // Initialize the decision parameter and increments for updating the decision parameter for the case where slope > 1
        d = 2 * dx - dy;
        change1 = 2 * (dx - dy);
        change2 = 2 * dx;

        // Initialize the starting point of the line
        int x = x1;
        int y = y1;

        // Set the first pixel of the line
        SetPixel(hdc, x1, y1, C);

        // Loop through each y coordinate and calculate the corresponding x coordinate
        while (y != y2) {

            // Update the decision parameter
            if (d < 0) {
                d += change2;
            }
            else {
                x += cx;
                d += change1;
            }

            // Move to the next y coordinate
            y += cy;

            // Draw the pixel at the corresponding x coordinate
            SetPixel(hdc, x, y, C);
        }
    }
}

void DrawLine(HDC hdc, Line L, COLORREF c) {
    DrawLine(hdc, L.S.x, L.S.y, L.E.x, L.E.y, c);
}

void DrawLineDDA(HDC hdc, Line L, COLORREF c) {
    DrawLineDDA(hdc, L.S.x, L.S.y, L.E.x, L.E.y, c);
}

void DrawLineMidPoint(HDC hdc, Line L, COLORREF c) {
    DrawLineMidPoint(hdc, L.S.x, L.S.y, L.E.x, L.E.y, c);
}



// Define the Hermite basis functions
double h00(double t) { return 2 * t * t * t - 3 * t * t + 1; }
double h10(double t) { return t * t * t - 2 * t * t + t; }
double h01(double t) { return -2 * t * t * t + 3 * t * t; }
double h11(double t) { return t * t * t - t * t; }

// Function to draw a straight line using Hermite interpolation of the first degree
void drawLineHermite(HDC hdc, double x0, double y0, double x1, double y1, COLORREF c) {
    // Calculate the slope of the line
    double m = (y1 - y0) / (x1 - x0);

    // Calculate the tangent vectors at the endpoints
    double t0[2] = { 1, m };
    double t1[2] = { 1, m };

    // Calculate the distance between x0 and x1
    double dx = x1 - x0;

    int numPoints = (int)CalcDistance(x0, y0, x1, y1);

    // Loop over the desired number of points
    for (int i = 0; i < numPoints; i++) {
        // Calculate the t-value for the current point
        double ti = (double)i / (numPoints - 1);

        // Calculate the interpolated y-value for the current point
        double yi = h00(ti) * y0 + h10(ti) * dx * m + h01(ti) * y1 + h11(ti) * dx * m;

        // Draw a point at the (xi, yi) position
        SetPixel(hdc, x0 + ti * dx, yi, c);
        //cout << "(" << x0 + ti * dx << ", " << yi << ")" << endl;
    }
}


#endif
