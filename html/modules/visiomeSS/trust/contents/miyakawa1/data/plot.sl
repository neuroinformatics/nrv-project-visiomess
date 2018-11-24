# set parameter

string s;
param = text2buffer( "param.mdl" );
s = "xmin = " + cut( param:[1], 2, 2 );
eval( s );
s = "xmax = " + cut( param:[2], 2, 2 );
eval( s );
s = "ymin = " + cut( param:[3], 2, 2 );
eval( s );
s = "ymax = " + cut( param:[4], 2, 2 );
eval( s );

# plot graph base

wopen( 1, "A4", 0, 2 );
size( 150, 120 );
origin( 30, 50 );
#scale( "N", "F", "N", "F", -60, 60, 0.8, 1.2 );
scale( "N", "F", "N", "F", xmin, xmax, ymin, ymax );

title( 1, "ISI (ms)", "Linearity" );
axis(1,1,"XY","XY",5.5,0,0,0,0,0);
ltype( 1, 8 );
draw( "Y", 1 );
ltype( 1, 1 );

# read data (table1m.csv)

series y[10], z[2];

x = text2buffer( "table1m.csv" );
num_data = index( x[0] );

for ( i = 0; i < 10; i++ ) {
  y[i] = cut( x[i], 1, num_data-1 );
}

#color( "white", "white" );
z[0] = y[1]; z[1] = y[2];
egraph( z, y[0], 0, 1, 0, 1, 3.5 );
egraph( z, y[0], 0, 0, 0, 1, 3.5 );
label( "I", 100, 120, 5, 0, "NORMAL" );

color( "blue", "blue" );
z[0] = y[4]; z[1] = y[5];
egraph( z, y[0], 0, 1, 0, 2, 3.5 );
egraph( z, y[0], 0, 0, 0, 2, 3.5 );
label( "I", 100, 115, 5, 0, "+BIC.PIC" );

color( "red", "red" );
z[0] = y[7]; z[1] = y[8];
egraph( z, y[0], 0, 1, 0, 4, 3.5 );
egraph( z, y[0], 0, 0, 0, 4, 3.5 );
label( "I", 100, 110, 5, 0, "+BIC.PIC.CGP" );

#color( "white", "white" );
