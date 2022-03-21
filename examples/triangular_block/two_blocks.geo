//+
Point(1) = {-1, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {1, 1, 0, 1.0};
//+
Point(4) = {-1, 1, 0, 1.0};
//+
Point(5) = {1, 2, 0, 1.0};
//+
Point(6) = {-1, 2, 0, 1.0};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 1};
//+
Line(5) = {3, 5};
//+
Line(6) = {5, 6};
//+
Line(7) = {6, 4};
//+
Curve Loop(1) = {6, 7, -3, 5};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {1, 2, 3, 4};
//+
Plane Surface(2) = {2};
//+
Physical Surface("buttom") = {2};
//+
Physical Surface("top") = {1};
//+
Physical Curve("l_buttom") = {1};
//+
Physical Curve("l_buttom_right") = {2};
//+
Physical Curve("l_buttom_left") = {4};
//+
Physical Curve("l_top_left") = {7};
//+
Physical Curve("l_top_right") = {5};
//+
Physical Curve("l_top") = {6};
