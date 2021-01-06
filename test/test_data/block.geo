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
Line(1) = {3, 6};
//+
Line(2) = {6, 7};
//+
Line(3) = {7, 4};
//+
Line(4) = {4, 3};
//+
Curve Loop(1) = {4, 1, 2, 3};
//+
Plane Surface(1) = {1};
//+
Transfinite Surface {1} = {3, 6, 7, 4};
//+
Transfinite Curve {4, 2} = 3 Using Progression 1;
//+
Transfinite Curve {3, 1} = 3 Using Progression 1;
//+
Recombine Surface {1};
//+
Physical Curve("ls", 4) = {4};
//+
Physical Curve("bs", 1) = {1};
//+
Physical Curve("rs", 2) = {2};
//+
Physical Curve("ts", 3) = {3};
//+
Line(5) = {1, 2};
//+
Line(6) = {2, 4};
//+
Line(7) = {4, 5};
//+
Line(8) = {5, 1};
//+
Curve Loop(2) = {8, 5, 6, 7};
//+
Plane Surface(2) = {2};
//+
Physical Curve("lb", 8) = {8};
//+
Physical Curve("bb", 5) = {5};
//+
Physical Curve("rb", 6) = {6};
//+
Physical Curve("tb", 7) = {7};
//+
Transfinite Surface {2} = {1, 2, 4, 5};
//+
Transfinite Curve {8, 6} = 5 Using Progression 1;
//+
Transfinite Curve {5, 7} = 5 Using Progression 1;
//+
Recombine Surface {2};
//+
Physical Surface("surf_big", 2) = {2};
//+
Physical Surface("surf_small", 1) = {1};
