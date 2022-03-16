//+
SetFactory("OpenCASCADE");
Circle(1) = {0, 0, 0, 0.1, 0, 2*Pi};
//+
Point(2) = {-1, -1, 0, 1.0};
//+
Point(3) = {1, -1, 0, 1.0};
//+
Point(4) = {1, 1, 0, 1.0};
//+
Point(5) = {-1, 1, 0, 1.0};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 5};
//+
Line(5) = {5, 2};
//+
Curve Loop(1) = {4, 5, 2, 3};
//+
Curve Loop(2) = {1};
//+
Plane Surface(1) = {1, 2};
//+
Physical Surface("surf") = {1};
//+
Physical Curve("buttom") = {2};
//+
Physical Curve("right") = {3};
//+
Physical Curve("top") = {4};
//+
Physical Curve("left") = {5};
//+
Physical Curve("cirlce") = {1};
