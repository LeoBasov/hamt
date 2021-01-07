SetFactory("OpenCASCADE");

L = DefineNumber[ 1.0 , Min 0.1, Max 2, Step 0.01,
  Name "Parameters/Length" ];
H = DefineNumber[ 2.0 , Min 0.1, Max 2, Step 0.01,
  Name "Parameters/Height" ];
M = DefineNumber[ 1.0, Min 0.1, Max 2, Step 0.01,
  Name "Parameters/Midth" ];

N_top = 10;
N_buttom = 10;
N_vertical = 10;

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

Line(6) = {4, 6};
Line(7) = {6, 5};
Line(8) = {5, 3};

Physical Curve("left_top", 6) = {6};
Physical Curve("top", 7) = {7};
Physical Curve("right_top", 8) = {8};

Curve Loop(2) = {3, 6, 7, 8};
Plane Surface(2) = {2};

Physical Surface("top_surf", 2) = {2};

Transfinite Surface {1} = {1, 2, 3, 4};
Transfinite Surface {2} = {4, 3, 5, 6};

Recombine Surface {2, 1};

Transfinite Curve {7, 3, 1} = N_vertical Using Progression 1;
Transfinite Curve {6, 8} = N_top Using Progression 1;
Transfinite Curve {4, 2} = N_vertical Using Progression 1;
