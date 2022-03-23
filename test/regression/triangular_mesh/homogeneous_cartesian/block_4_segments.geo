SetFactory("OpenCASCADE");

L = 1;
N_nodes = 3;

Point(1) = {0.0, 0.0, 0.0};
Point(2) = {L/2, 0.0, 0.0};
Point(3) = {L, 0.0, 0.0};

Point(4) = {L, L/2, 0.0};
Point(5) = {L/2, L/2, 0.0};
Point(6) = {0.0, L/2, 0.0};

Point(7) = {0.0, L, 0.0};
Point(8) = {L/2, L, 0.0};
Point(9) = {L, L, 0.0};


Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 9};
Line(5) = {9, 8};
Line(6) = {8, 7};
Line(7) = {7, 6};
Line(8) = {6, 1};
Line(9) = {8, 5};
Line(10) = {5, 2};
Line(11) = {6, 5};
Line(12) = {5, 4};

Curve Loop(1) = {8, 1, -10, -11};
Plane Surface(1) = {1};

Curve Loop(2) = {10, 2, 3, -12};
Plane Surface(2) = {2};

Curve Loop(3) = {9, 12, 4, 5};
Plane Surface(3) = {3};

Curve Loop(4) = {7, 11, -9, 6};
Plane Surface(4) = {4};

Transfinite Surface {1} = {1, 2, 5, 6};
Transfinite Surface {2} = {2, 3, 4, 5};
Transfinite Surface {3} = {5, 4, 9, 8};
Transfinite Surface {4} = {6, 5, 8, 7};

Transfinite Curve {8, 10, 3} = N_nodes Using Progression 1;
Transfinite Curve {7, 9, 4} = N_nodes Using Progression 1;
Transfinite Curve {6, 11, 1} = N_nodes Using Progression 1;
Transfinite Curve {5, 12, 2} = N_nodes Using Progression 1;

Physical Curve("buttom_left", 1) = {1};
Physical Curve("buttom_right", 2) = {2};
Physical Curve("right_buttom", 3) = {3};
Physical Curve("right_top", 4) = {4};
Physical Curve("top_right", 5) = {5};
Physical Curve("top_left", 6) = {6};
Physical Curve("left_top", 7) = {7};
Physical Curve("left_buttom", 8) = {8};

Physical Surface("surf_bl", 1) = {1};
Physical Surface("surf_br", 2) = {2};
Physical Surface("surf_tr", 3) = {3};
Physical Surface("surf_tl", 4) = {4};
