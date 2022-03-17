// Gmsh project created on Tue Jan  5 12:58:00 2021
SetFactory("OpenCASCADE");
//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {1, 1, 0, 1.0};
//+
Point(4) = {0, 1, 0, 1.0};

//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 1};
//+
Curve Loop(1) = {4, 1, 2, 3};
//+
Plane Surface(1) = {1};
//+
Physical Curve("left", 4) = {4};
//+
Physical Curve("buttom", 1) = {1};
//+
Physical Curve("right", 2) = {2};
//+
Physical Curve("top", 3) = {3};
//+
Physical Surface("surf", 1) = {1};
