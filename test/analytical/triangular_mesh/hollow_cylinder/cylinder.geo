//+
SetFactory("OpenCASCADE");
Circle(1) = {0, 0, 0, 1, 0, Pi};
//+
Circle(2) = {0, 0, 0, 2, 0, Pi};
//+
Line(3) = {3, 1};
//+
Line(4) = {2, 4};
//+
Physical Curve("left") = {3};
//+
Physical Curve("inner") = {1};
//+
Physical Curve("right") = {4};
//+
Physical Curve("outer") = {2};
//+
Curve Loop(1) = {2, -4, -1, -3};
//+
Plane Surface(1) = {1};
//+
Physical Surface("surf") = {1};
