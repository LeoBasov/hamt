//+
Point(1) = {-0.5, 1.0, 0, 1.0};
//+
Point(2) = {0.5, 1.0, 0, 1.0};
//+
Point(3) = {0.5, 2.0, 0, 1.0};
//+
Point(4) = {-0.5, 2.0, 0, 1.0};
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
Physical Curve("buttom", 5) = {1};
//+
Physical Curve("right", 6) = {2};
//+
Physical Curve("top", 7) = {3};
//+
Physical Curve("left", 8) = {4};
//+
Physical Surface("surf", 9) = {1};
