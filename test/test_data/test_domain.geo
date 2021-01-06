//+
Point(1) = {0.0, 0, 0, 1.0};
//+
Point(2) = {1.0, 0, 0, 1.0};
//+
Point(3) = {1, 1, 0, 1.0};
//+
Point(4) = {0, 1, 0, 1.0};
//+
Line(1) = {1, 4};
//+
Line(2) = {4, 3};
//+
Line(3) = {3, 2};
//+
Line(4) = {2, 1};
//+
Line Loop(1) = {1, 2, 3, 4};
//+
Plane Surface(1) = {1};
//+
Physical Line("buttom") = {4};
//+
Physical Line("right") = {3};
//+
Physical Line("top") = {2};
//+
Physical Line("left") = {1};
//+
Transfinite Surface {1} = {1, 2, 3, 4};
//+
Transfinite Line {1, 3} = 10 Using Progression 1;
//+
Transfinite Line {2, 4} = 10 Using Progression 1;
//+
Recombine Surface {1};
