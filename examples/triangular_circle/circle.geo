//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {-1, 0, 0, 1.0};
//+
Point(4) = {2, 0, 0, 1.0};
//+
Point(5) = {-2, 0, 0, 1.0};
//+
Circle(1) = {2, 1, 3};
//+
Circle(2) = {4, 1, 5};
//+
Line(3) = {2, 4};
//+
Line(4) = {5, 3};
//+
Curve Loop(1) = {2, 4, -1, 3};
//+
Plane Surface(1) = {1};
//+
Physical Curve("mirrow_left", 5) = {4};
//+
Physical Curve("inner", 6) = {1};
//+
Physical Curve("mirrow_right", 7) = {3};
//+
Physical Curve("outer", 8) = {2};
//+
Physical Surface("surf", 9) = {1};
