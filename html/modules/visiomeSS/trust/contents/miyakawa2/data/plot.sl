#
# Plot graph by SATELLITE
#               H.Ikeno 2003/12/15
#

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

# set plot data

series time, LM[10], OR[10];

x = text2buffer( "FigData.csv" );
num_data = index( x[0] );
time = cut( x[1], 1, num_data-1 );
for ( i = 0; i < 10; i++ ) {
  LM[i] = cut( x[i+ 2], 1, num_data-1 );
  OR[i] = cut( x[i+12], 1, num_data-1 );
}

string lbl[10];

lbl[0]  = "location(2,7)";
lbl[1]  = "location(3,7)";
lbl[2]  = "location(4,7)";
lbl[3]  = "location(5,7)";
lbl[4]  = "location(6,7)";
lbl[5]  = "location(7,7)";
lbl[6]  = "location(8,7)";
lbl[7]  = "location(9,7)";
lbl[8]  = "location(10,7)";
lbl[9]  = "location(11,7)";

# plot graph

wopen( 1, "A4", 0, 2 );

size( 80, 18 );
#scale( "N", "F", "N", "F", 0, 95., -0.02, 0.12 );
scale( "N", "F", "N", "F", xmin, xmax, ymin, ymax );

origin(50, 265);
label( "I", 0, 0, 5.5, 0, "LM" );
origin(140, 265);
label( "I", 0, 0, 5.5, 0, "OR" );

for ( i = 0; i < 10; i++ ) {
  origin( 20, 240-i*22 );
  graph( LM[i],time,0,0,0,1,3.5);
  label( "I", 154, 9, 4.5, 0, lbl[i] ); 
  origin( 110, 240-i*22 );
  graph( OR[i],time,0,0,0,1,3.5);
}
origin( 110 );
title( 1, "time (msec)", "dF/F(%)" );
axis(1,3,"XY","XY",4.5,0,0,0,0.1,0);
