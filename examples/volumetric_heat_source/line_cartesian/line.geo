//+
Point(1) = {0.01, 0, 0, 1.0};
//+
Point(2) = {0.01, 0.5, 0, 1.0};
//+
Point(3) = {0.01, 1, 0, 1.0};
//+
Point(4) = {-0.01, 1, 0, 1.0};
//+
Point(5) = {-0.01, 0.5, 0, 1.0};
//+
Point(6) = {-0.01, 0, 0, 1.0};
//+
Line(1) = {6, 1};
//+
Line(2) = {1, 2};
//+
Line(3) = {2, 5};
//+
Line(4) = {5, 6};
//+
Line(5) = {5, 4};
//+
Line(6) = {4, 3};
//+
Line(7) = {3, 2};
//+
Curve Loop(1) = {1, 2, 3, 4};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {6, 7, 3, 5};
//+
Plane Surface(2) = {2};
//+
Physical Curve("buttom") = {1};
//+
Physical Curve("right_buttom") = {2};
//+
Physical Curve("right_top") = {7};
//+
Physical Curve("top") = {6};
//+
Physical Curve("left_top") = {5};
//+
Physical Curve("left_buttom") = {4};
//+
Physical Surface("surf_buttom") = {1};
//+
Physical Surface("surf_top") = {2};
