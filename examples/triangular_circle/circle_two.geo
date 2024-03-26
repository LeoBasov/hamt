// Gmsh project created on Tue Mar 26 09:12:09 2024
SetFactory("OpenCASCADE");
//+
Point(1) = {-2, 0, 0, 1.0};
//+
Point(2) = {-1, 0, 0, 1.0};
//+
Point(3) = {0, 1, 0, 1.0};
//+
Point(4) = {0, 0, 0, 1.0};
//+
Point(5) = {1, 0, 0, 1.0};
//+
Point(6) = {2, 0, 0, 1.0};
//+
Point(7) = {0, 2, 0, 1.0};
//+
//+
Line(1) = {1, 2};
//+
Line(2) = {5, 6};
//+
Circle(3) = {2, 4, 3};
//+
Circle(4) = {3, 4, 5};
//+
Circle(5) = {6, 4, 7};
//+
Circle(6) = {7, 4, 1};
//+
Line(7) = {7, 3};
//+
Curve Loop(1) = {4, 2, 5, 7};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {6, 1, 3, -7};
//+
Plane Surface(2) = {2};
//+
Physical Curve("left", 8) = {1};
//+
Physical Curve("inner_left", 9) = {3};
//+
Physical Curve("inner_right", 10) = {4};
//+
Physical Curve("right", 11) = {2};
//+
Physical Curve("outer_right", 12) = {5};
//+
Physical Curve("outer_left", 13) = {6};
//+
Physical Surface("surf_left", 14) = {2};
//+
Physical Surface("surf_right", 15) = {1};
