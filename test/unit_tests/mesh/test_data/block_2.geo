// Gmsh project created on Tue Jan  5 12:58:00 2021
SetFactory("OpenCASCADE");
//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {1, 0.5, 0, 1.0};
//+
Point(4) = {1, 1.0, 0, 1.0};
//+
Point(5) = {0, 1.0, 0, 1.0};
//+
Point(6) = {1.5, 0.5, 0, 1.0};
//+
Point(7) = {1.5, 1, 0, 1.0};
//+
Line(1) = {3, 4};
//+
Line(2) = {4, 7};
//+
Line(3) = {7, 6};
//+
Line(4) = {6, 3};
//+
Line(5) = {4, 5};
//+
Line(6) = {5, 1};
//+
Line(7) = {1, 2};
//+
Line(8) = {2, 4};
//+
Curve Loop(1) = {6, 7, 8, 5};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {4, 1, 2, 3};
//+
Plane Surface(2) = {2};
//+
Physical Surface("big") = {1};
//+
Physical Surface("small") = {2};
//+
Transfinite Curve {6, 7, 8, 5} = 5 Using Progression 1;
//+
Transfinite Curve {4, 3, 2, 1} = 3 Using Progression 1;
//+
Transfinite Surface {1};
//+
Transfinite Surface {2};
//+
Recombine Surface {1};
//+
Recombine Surface {2};
//+
Physical Curve("l_r") = {3};
//+
Physical Curve("top") = {2, 5};
//+
Physical Curve("left") = {6};
//+
Physical Curve("buttom_large") = {7};
//+
Physical Curve("centre") = {8};
//+
Physical Curve("centre_small") = {1};
//+
Physical Curve("buttom_samll") = {4};
