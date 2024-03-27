//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {2, 0, 0, 1.0};
//+
Point(4) = {0, 1, 0, 1.0};
//+
Point(5) = {0, 2, 0, 1.0};
//+
Point(6) = {-1, 0, 0, 1.0};
//+
Point(7) = {-2, 0, 0, 1.0};
//+
Line(1) = {7, 6};
//+
Circle(2) = {6, 1, 4};
//+
Line(3) = {4, 5};
//+
Circle(4) = {5, 1, 7};
//+
Circle(5) = {5, 1, 3};
//+
Line(6) = {3, 2};
//+
Circle(7) = {2, 1, 4};
//+
Curve Loop(1) = {4, 1, 2, 3};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {5, 6, 7, 3};
//+
Plane Surface(2) = {2};
//+
Physical Curve("mirrow_left") = {1};
//+
Physical Curve("mirrow_right") = {6};
//+
Physical Curve("inner_right") = {7};
//+
Physical Curve("inner_left") = {2};
//+
Physical Curve("outer_left") = {4};
//+
Physical Curve("outer_right") = {5};
//+
Physical Surface("surface_right") = {2};
//+
Physical Surface("surface_left") = {1};
