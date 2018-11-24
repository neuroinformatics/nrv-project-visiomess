#
# Plot graph by SATELLITE
#               H.Ikeno 2003/05/06
#

func plotGraph( x, y, Ymin, Ymax, name ) {
  title( 1, "voltage (mV)", "current (A)" );
  scale( "N", "F", "N", "F", -100, 50, Ymin, Ymax );
  graph(y, x[0],0,2,0,1,3.5);
  axis(1,1,"XY","XY",3.5,0,0,0,0,0);
  frame();
  draw( "X", 0 );
  draw( "Y", 0 );
  label("I", 2, 82,5.0,0,name);

  return 0;
}

# read data (fastINa)

string name;
series y[2];

wopen( 1, "A4", 0, 2 );
size( 80, 80 );

# plot fast INa

x = text2buffer( "fastINa.csv" );
num_data = index( x[0] );
x[0] = cut( x[0], 1, num_data-1 );
y[0] = cut( x[1], 1, num_data-1 );
y[1] = cut( x[2], 1, num_data-1 );

origin( 20, 170 );
plotGraph( x, y, -500e-12, 100e-12, "fast INa" );

# plot persistent INa

x = text2buffer( "INaP.csv" );
num_data = index( x[0] );
x[0] = cut( x[0], 1, num_data-1 );
y[0] = cut( x[1], 1, num_data-1 );
y[1] = cut( x[2], 1, num_data-1 );

origin( 120, 170 );
plotGraph( x, y, -500e-12, 100e-12, "persistent INa" );

# plot ICa

x = text2buffer( "ICa.csv" );
num_data = index( x[0] );
x[0] = cut( x[0], 1, num_data-1 );
y[0] = cut( x[1], 1, num_data-1 );
y[1] = cut( x[2], 1, num_data-1 );

origin( 20, 70 );
plotGraph( x, y, -500e-12, 100e-12, "ICa" );
