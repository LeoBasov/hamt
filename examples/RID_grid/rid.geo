//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {0.5, 0.5, 0, 1.0};
//+
Point(3) = {0.5, 1, 0, 1.0};
//+
Point(4) = {0, 1, 0, 1.0};
//+
Circle(1) = {4, 3, 2};
//+
Point(5) = {-0.5, 0.5, 0, 1.0};
//+
Point(6) = {0, 0.5, 0, 1.0};

//+
Point(7) = {-0.5, 0, 0, 1.0};
//+
Circle(2) = {1, 7, 5};
//+
Point(8) = {-0.5, 1, 0, 1.0};
//+
Point(9) = {0.5, 0, 0, 1.0};
//+
Line(3) = {1, 9};
//+
Line(4) = {9, 2};
//+
Line(5) = {4, 8};
//+
Line(6) = {8, 5};
//+
Curve Loop(1) = {5, 6, -2, 3, 4, -1};
//+
Plane Surface(1) = {1};
//+
Physical Surface("surf") = {1};
//+
Physical Curve("buttom") = {3};
//+
Physical Curve("right") = {4};
//+
Physical Curve("left") = {6};
//+
Physical Curve("top") = {5};
//+
Physical Curve("cirlce_l") = {2};
//+
Physical Curve("cirlce_r") = {1};
