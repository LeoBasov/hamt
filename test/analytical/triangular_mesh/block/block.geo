//+
Point(1) = {-1, -1, 0, 1.0};
//+
Point(2) = {0, -1, 0, 1.0};
//+
Point(3) = {1, -1, 0, 1.0};
//+
Point(4) = {1, 0, 0, 1.0};
//+
Point(5) = {1, 1, 0, 1.0};
//+
Point(6) = {0, 1, 0, 1.0};
//+
Point(7) = {-1, 1, 0, 1.0};
//+
Point(8) = {0, 0, 0, 1.0};
//+
Point(9) = {-1, 0, 0, 1.0};

//+
Line(1) = {1, 2};
//+
Line(2) = {2, 8};
//+
Line(3) = {8, 9};
//+
Line(4) = {9, 1};
//+
Line(5) = {8, 4};
//+
Line(6) = {4, 5};
//+
Line(7) = {5, 6};
//+
Line(8) = {6, 8};
//+
Line(9) = {2, 3};
//+
Line(10) = {3, 4};
//+
Line(11) = {6, 7};
//+
Line(12) = {7, 9};
//+
Curve Loop(1) = {12, -3, -8, 11};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {7, 8, 5, 6};
//+
Plane Surface(2) = {2};
//+
Curve Loop(3) = {10, -5, -2, 9};
//+
Plane Surface(3) = {3};
//+
Curve Loop(4) = {1, 2, 3, 4};
//+
Plane Surface(4) = {4};
//+
Physical Surface("s_buttom_left") = {4};
//+
Physical Surface("s_buttom_right") = {3};
//+
Physical Surface("s_top_left") = {1};
//+
Physical Surface("s_top_right") = {2};
//+
Physical Curve("l_buttom_left") = {1};
//+
Physical Curve("l_buttom_right") = {9};
//+
Physical Curve("l_right_buttom") = {10};
//+
Physical Curve("l_right_top") = {6};
//+
Physical Curve("l_top_right") = {7};
//+
Physical Curve("l_top_left") = {11};
//+
Physical Curve("l_left_top") = {12};
//+
Physical Curve("l_left_buttom") = {4};
