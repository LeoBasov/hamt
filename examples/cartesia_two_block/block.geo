SetFactory("OpenCASCADE");

L = 1.0;
H = 2.0;
M = 1.0;

N = DefineNumber[ 10, Min 2, Max 100, Step 1,
  Name "Parameters/N_cells" ];

Point(1) = {0.0, 0.0, 0.0};
Point(2) = {L, 0.0, 0.0};
Point(3) = {L, M, 0.0};
Point(4) = {0.0, M, 0.0};
Point(5) = {L, H, 0.0};
Point(6) = {0.0, H, 0.0};

Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 1};

Physical Curve("buttom", 1) = {1};
Physical Curve("right_buttom", 2) = {2};
Physical Curve("middle", 3) = {3};
Physical Curve("left_buttom", 4) = {4};

Curve Loop(1) = {1, 2, 3, 4};
Plane Surface(1) = {1};

Physical Surface("buttom_surf", 1) = {1};

Line(6) = {3, 5};
Line(7) = {5, 6};
Line(8) = {6, 4};

Physical Curve("left_top", 6) = {6};
Physical Curve("top", 7) = {7};
Physical Curve("right_top", 8) = {8};

Curve Loop(2) = {8, -3, 6, 7};
Plane Surface(2) = {2};

Physical Surface("top_surf", 2) = {2};

Transfinite Surface {1} = {1, 2, 3, 4};
Transfinite Surface {2} = {4, 3, 5, 6};

Recombine Surface {2, 1};

Transfinite Curve {7, 3, 1} = N Using Progression 1;
Transfinite Curve {6, 8} = N Using Progression 1;
Transfinite Curve {4, 2} = N Using Progression 1;

