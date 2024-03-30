SetFactory("OpenCASCADE");
//+
Point(1) = {-1, 1, 0, 1.0};
//+
Point(2) = {1, 1, 0, 1.0};
//+
Point(3) = {1, 2, 0, 1.0};
//+
Point(4) = {-1, 2, 0, 1.0};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 1};
//+
//+
Circle(5) = {0, 1.5, 0, 0.1, 0, 2*Pi};
//+
Curve Loop(1) = {5};
//+
Curve Loop(2) = {3, 4, 1, 2};
//+
Plane Surface(1) = {1, 2};
//+
Curve Loop(3) = {5};
//+
Plane Surface(2) = {3};
//+
Physical Curve("buttom", 6) = {1};
//+
Physical Curve("right", 7) = {2};
//+
Physical Curve("top", 8) = {3};
//+
Physical Curve("left", 9) = {4};
//+
Physical Surface("surf", 10) = {1};
//+
Physical Surface("cirlce", 11) = {2};
