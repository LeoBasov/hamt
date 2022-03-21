//+
SetFactory("OpenCASCADE");
Circle(1) = {0, 0, 0, 0.5, 0, Pi};
//+
Circle(2) = {0, 0, 0, 1, 0, Pi};
//+
Line(3) = {4, 2};
//+
Line(4) = {1, 3};
//+
Curve Loop(1) = {2, 3, -1, 4};
//+
Plane Surface(1) = {1};
//+
Physical Curve("outer") = {2};
//+
Physical Curve("inner") = {1};
//+
Physical Curve("cut") = {4, 3};
//+
Physical Surface("surf") = {1};
