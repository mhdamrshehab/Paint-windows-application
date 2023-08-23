#ifndef FINALPROJECTCOMPUTERGRAPHICS_HERMITECURVE_H
#define FINALPROJECTCOMPUTERGRAPHICS_HERMITECURVE_H

#include "MyUtilities.h"
#include "LineClipping.h"

class Vector2 {
public:
    double x, y;

    Vector2(double x = 0, double y = 0) : x(x), y(y) {}

    Vector2(const Vector2& other) {
        x = other.x;
        y = other.y;
    }
};

class HermiteCubicCurve {
    Vector2 P1, T1, P2, T2;
public:
    HermiteCubicCurve(Vector2* V) {
        P1 = V[0]; T1 = V[1];
        T2 = V[2]; P2 = V[3];
    }

    HermiteCubicCurve(Point* P) {
        P1.x = P[0].x; P1.y = P[0].y;
        T1.x = P[1].x; T1.y = P[1].y;
        T2.x = P[2].x; T2.y = P[2].y;
        P2.x = P[3].x; P2.y = P[3].y;
    }

    HermiteCubicCurve(Vector2& V1, Vector2& V2, Vector2& V3, Vector2& V4) {
        P1 = V1; T1 = V2;
        T2 = V3; P2 = V4;
    }

    void DrawHermite(HDC hdc, COLORREF c, Window W)
    {
        double a0 = P1.x,
            a1 = T1.x,
            a2 = -3 * P1.x - 2 * T1.x + 3 * P2.x - T2.x,
            a3 = 2 * P1.x + T1.x - 2 * P2.x + T2.x;

        double b0 = P1.y,
            b1 = T1.y,
            b2 = -3 * P1.y - 2 * T1.y + 3 * P2.y - T2.y,
            b3 = 2 * P1.y + T1.y - 2 * P2.y + T2.y;

        for (double t = 0; t <= 1; t += 0.001) {
            double t2 = t * t, t3 = t2 * t;
            double x = a0 + a1 * t + a2 * t2 + a3 * t3;
            double y = b0 + b1 * t + b2 * t2 + b3 * t3;
            if (PointClipping(Point(x, y), W))
                SetPixel(hdc, Round(x), Round(y), c);
        }
    }

    static void DrawHermite(HDC hdc, HermiteCubicCurve curve, COLORREF c)
    {
        double  a0 = curve.P1.x,
            a1 = curve.T1.x,
            a2 = -3 * curve.P1.x - 2 * curve.T1.x + 3 * curve.P2.x - curve.T2.x,
            a3 = 2 * curve.P1.x + curve.T1.x - 2 * curve.P2.x + curve.T2.x;

        double  b0 = curve.P1.y,
            b1 = curve.T1.y,
            b2 = -3 * curve.P1.y - 2 * curve.T1.y + 3 * curve.P2.y - curve.T2.y,
            b3 = 2 * curve.P1.y + curve.T1.y - 2 * curve.P2.y + curve.T2.y;

        for (double t = 0; t <= 1; t += 0.001) {
            double t2 = t * t, t3 = t2 * t;
            double x = a0 + a1 * t + a2 * t2 + a3 * t3;
            double y = b0 + b1 * t + b2 * t2 + b3 * t3;
            SetPixel(hdc, Round(x), Round(y), c);
        }
    }

    void PlusX(int x) {
        P1.x += x; T1.x += x; P2.x += x; T2.x += x;
    }

};

void Spline(HDC hdc, Vector2* P, int n, double c, COLORREF s) {
    double c1 = 1 - c;
    Vector2 T0(c1 * (P[2].x - P[0].x), c1 * (P[2].y - P[0].y));
    for (int i = 2; i < n - 1; i++) {
        Vector2 T1(c1 * (P[i + 1].x - P[i - 1].x), c1 * (P[i + 1].y - P[i - 1].y));
        HermiteCubicCurve::DrawHermite(hdc, HermiteCubicCurve(P[i - 2], T0, T1, P[i - 1]), s);
        T0 = T1;
    }
}

void FillingHermite(HDC hdc, Vector2* Vect, Window W, COLORREF c) {
    HermiteCubicCurve Curve(Vect);
    for (int x = W.Left; x <= W.Right; x++) {
        Curve.DrawHermite(hdc, c, W);
        Curve.PlusX(5);
    }
}

#endif
