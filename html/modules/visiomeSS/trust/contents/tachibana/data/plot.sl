wopen( 1, "A4", 0, 2 );

# plot Fig.3C-1

x = text2buffer( "Fig3C1.csv" );
num_data = index( x[0] );
x[0] = cut( x[0], 1, num_data-1 );
x[1] = cut( x[1], 1, num_data-1 );
x[2] = cut( x[2], 1, num_data-1 );

size( 80, 5 );
origin( 20, 250 );
scale( "N", "A", "N", "A" ); 
graph(x[1], x[0],0,0,0,1,3.5);

size( 80, 80 );
origin( 20, 165 );
scale( "N", "A", "N", "F", -40., 0. ); 
graph(x[2], x[0],0,0,0,1,3.5);
axis(1,1,"XY","XY",3.5,0,0,0,0,0);
frame();

label("I", 0, 100,5.0,0,"(1) Fig3C_1")

# plot Fig.3C-2

x = text2buffer( "Fig3C2.csv" );
num_data = index( x[0] );
x[0] = cut( x[0], 1, num_data-1 );
x[1] = cut( x[1], 1, num_data-1 );
x[2] = cut( x[2], 1, num_data-1 );

size( 80, 5 );
origin( 120, 250 );
scale( "N", "A", "N", "A" ); 
graph(x[1], x[0],0,0,0,1,3.5);

size( 80, 80 );
origin( 120, 165 );
scale( "N", "A", "N", "F", -40., 0. ); 
graph(x[2], x[0],0,0,0,1,3.5);
axis(1,1,"XY","XY",3.5,0,0,0,0,0);
frame();

label("I", 0, 100,5.0,0,"(2) Fig3C_2")

# plot Fig.9A-1

x = text2buffer( "Fig9A1.csv" );
num_data = index( x[0] );
x[0] = cut( x[0], 1, num_data-1 );
x[1] = cut( x[1], 1, num_data-1 );
x[2] = cut( x[2], 1, num_data-1 );

size( 80, 5 );
origin( 20, 120 );
scale( "N", "A", "N", "A" ); 
graph(x[1], x[0],0,0,0,1,3.5);

size( 80, 80 );
origin( 20, 35 );
scale( "N", "A", "N", "F", -220., -20. ); 
graph(x[2], x[0],0,0,0,1,3.5);
axis(1,1,"XY","XY",3.5,0,0,0,0,0);
frame();

label("I", 0, 100,5.0,0,"(3) Fig9A_1")

# plot Fig.9A-2

x = text2buffer( "Fig9A2.csv" );
num_data = index( x[0] );
x[0] = cut( x[0], 1, num_data-1 );
x[1] = cut( x[1], 1, num_data-1 );
x[2] = cut( x[2], 1, num_data-1 );

size( 80, 5 );
origin( 120, 120 );
scale( "N", "A", "N", "A" ); 
graph(x[1], x[0],0,0,0,1,3.5);

size( 80, 80 );
origin( 120, 35 );
scale( "N", "A", "N", "F", -220., -20. ); 
graph(x[2], x[0],0,0,0,1,3.5);
axis(1,1,"XY","XY",3.5,0,0,0,0,0);
frame();

label("I", 0, 100,5.0,0,"(4) Fig9A_2")
