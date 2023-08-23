#ifndef FINALPROJECTCOMPUTERGRAPHICS_NONCONVEXFILLING_H
#define FINALPROJECTCOMPUTERGRAPHICS_NONCONVEXFILLING_H

#include "MyUtilities.h"
#include "Line.h"
#include <vector>

class Node {
public:
    double X;
    double Mi;
    double Ymax;
    Node(double x, double mi, double ymax) :X(x), Mi(mi), Ymax(ymax) {}
};

vector<vector<Node>> Table;

bool compareByX(const Node& A, const Node& B) {
    return A.X < B.X;
}

void initialization(Point* P, int n) {
    for (int i = 0; i < 3000; i++)
        Table[i].clear();

    Point v1 = P[n - 1];
    for (int i = 0; i < n; i++) {
        Point v2 = P[i];

        if (v1.y == v2.y)
            continue;

        if (v1.y > v2.y)
            swap(v1, v2);

        Node N(v1.x, ((double)v2.x - v1.x) / ((double)v2.y - v1.y), v2.y);

        Table[v1.y].push_back(N);
        v1 = P[i];
    }
}

void NonConvexFilling(HDC hdc, Point* P, int n, COLORREF c) {
    if (n < 2) return;

    if (n == 2) {
        DrawLine(hdc, P[0].x, P[0].y, P[1].x, P[1].y, c);
        return;
    }

    initialization(P, n);

    int y = 0;
    while (y < Table.size() && Table[y].empty())
        y++;

    vector<Node> Active = Table[y];
    while (!Active.empty()) {
        sort(Active.begin(), Active.end(), compareByX);
        for (int i = 0; i < Active.size(); i += 2)
            DrawLine(hdc, Active[i].X, y, Active[i + 1].X, y, c);

        y++;

        int j = 0;
        while (j < Active.size()) {
            if (Active[j].Ymax == y)
                Active.erase(Active.begin() + j);
            else
                j++;
        }

        for (int i = 0; i < Active.size(); i++)
            Active[i].X += Active[i].Mi;

        if (!Table[y].empty())
            Active.insert(Active.end(), Table[y].begin(), Table[y].end());
    }
}

void NonConvexFilling(HDC hdc, vector<Point> P, COLORREF c) {
    Point* P_ = new Point[P.size()];

    for (int i = 0; i < P.size(); i++)
        P_[i] = P[i];

    NonConvexFilling(hdc, P_, P.size(), c);
}

#endif
