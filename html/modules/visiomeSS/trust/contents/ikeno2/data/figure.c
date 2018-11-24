/*****************************************************************************

Bee Vision  - Simulation Program of Compound Eye Vision -

 ----------------------------------------------------------------------------

  投射図形の設定
  2001/10/15: 現在のところ図形は1枚、濃淡画像のみ
                  明点:  1.
                  暗点: -1.
                  背景:  0.

********************************************** (c) Hidetoshi Ikeno **********/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "beeVision.h"

extern parameters beeParam;
extern target figure[N_FIGURE];

#define    BAR_W     10.
#define    BAR_W2    BAR_W/2.
#define    SIN_45    0.70710678

void initFig( int figNum ) {
  int    i, j;
  double x, y, x_dot2, y_dot2, x_half, y_half, x_angle, y_angle, dj;
  double r;
  double angleFig;
  double x_edge1, x_edge2, y_edge1, y_edge2;

  x_dot2 = (double)figure[figNum].dotX/2;
  y_dot2 = (double)figure[figNum].dotY/2;
  x_half = (double)(figure[figNum].dotX)/2. * figure[figNum].dotDiam;
  y_half = (double)(figure[figNum].dotY)/2. * figure[figNum].dotDiam;
  x_angle = figure[figNum].angleX * TO_RAD;
  y_angle = figure[figNum].angleY * TO_RAD;

  // 画像の設定

  for ( j = 0; j < figure[figNum].dotY; j++ ) {
    for ( i = 0; i < figure[figNum].dotX; i++ ) {
      figure[figNum].pixel[i][j].br = 0.;

      if ( j > (int)((y_half-BAR_W2)/figure[figNum].dotDiam) && 
           j < (int)((y_half+BAR_W2)/figure[figNum].dotDiam) ) { 
        figure[figNum].pixel[i][j].br = figure[figNum].color;
      }
      if ( i > (int)((x_half-BAR_W2)/figure[figNum].dotDiam) && 
           i < (int)((x_half+BAR_W2)/figure[figNum].dotDiam) ) { 
        figure[figNum].pixel[i][j].br = figure[figNum].color; 
      }
 
      // 斜め線

      x = (double)i * figure[figNum].dotDiam - x_half;
      y = y_half - (double)j * figure[figNum].dotDiam;

      if ( sqrt(x*x + y*y) < x_half  && 
           y < x + BAR_W2 * 1.4142 &&
           y > x - BAR_W2 * 1.4142 ) {
        figure[figNum].pixel[i][j].br = figure[figNum].color;
      }

    }
  }

  // 画像の設定はここまで

  // 視空間におけるX,Y,Z座標を求める

  for (j=0; j < figure[figNum].dotY; j++) {
    for (i=0; i < figure[figNum].dotX; i++) {

      figure[figNum].pixel[i][j].x = figure[figNum].centerX 
        - x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * sin(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * cos(x_angle);
      figure[figNum].pixel[i][j].y = figure[figNum].centerY 
        + x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * cos(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * sin(x_angle);
      figure[figNum].pixel[i][j].z = figure[figNum].centerZ 
        + y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * cos(y_angle);
    }   
  }

}

// +マーク

#define    BAR_W     10.
#define    BAR_W2    BAR_W/2.
#define    SIN_45    0.70710678

void initFigPlus( int figNum ) {
  int    i, j;
  double x, y, x_dot2, y_dot2, x_half, y_half, x_angle, y_angle, dj;
  double r;
  double angleFig;
  double x_edge1, x_edge2, y_edge1, y_edge2;

  x_dot2 = (double)figure[figNum].dotX/2;
  y_dot2 = (double)figure[figNum].dotY/2;
  x_half = (double)(figure[figNum].dotX)/2. * figure[figNum].dotDiam;
  y_half = (double)(figure[figNum].dotY)/2. * figure[figNum].dotDiam;
  x_angle = figure[figNum].angleX * TO_RAD;
  y_angle = figure[figNum].angleY * TO_RAD;

  // 画像の設定

  for ( j = 0; j < figure[figNum].dotY; j++ ) {
    for ( i = 0; i < figure[figNum].dotX; i++ ) {
      figure[figNum].pixel[i][j].br = 0.;

      if ( j > (int)((y_half-BAR_W2)/figure[figNum].dotDiam) && 
           j < (int)((y_half+BAR_W2)/figure[figNum].dotDiam) ) { 
        figure[figNum].pixel[i][j].br = -1.;
      }
      if ( i > (int)((x_half-BAR_W2)/figure[figNum].dotDiam) && 
           i < (int)((x_half+BAR_W2)/figure[figNum].dotDiam) ) { 
        figure[figNum].pixel[i][j].br = figure[figNum].color; 
      }
 
    }
  }

  // 画像の設定はここまで

  // 視空間におけるX,Y,Z座標を求める

  for (j=0; j < figure[figNum].dotY; j++) {
    for (i=0; i < figure[figNum].dotX; i++) {

      figure[figNum].pixel[i][j].x = figure[figNum].centerX 
        - x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * sin(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * cos(x_angle);
      figure[figNum].pixel[i][j].y = figure[figNum].centerY 
        + x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * cos(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * sin(x_angle);
      figure[figNum].pixel[i][j].z = figure[figNum].centerZ 
        + y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * cos(y_angle);
    }   
  }

}

// Xマーク

#define    BAR_W     10.
#define    BAR_W2    BAR_W/2.
#define    SIN_45    0.70710678

void initFigCross( int figNum ) {
  int    i, j;
  double x, y, x_dot2, y_dot2, x_half, y_half, x_angle, y_angle, dj;
  double r;
  double angleFig;
  double x_edge1, x_edge2, y_edge1, y_edge2;

  x_dot2 = (double)figure[figNum].dotX/2;
  y_dot2 = (double)figure[figNum].dotY/2;
  x_half = (double)(figure[figNum].dotX)/2. * figure[figNum].dotDiam;
  y_half = (double)(figure[figNum].dotY)/2. * figure[figNum].dotDiam;
  x_angle = figure[figNum].angleX * TO_RAD;
  y_angle = figure[figNum].angleY * TO_RAD;

  // 画像の設定

  for ( j = 0; j < figure[figNum].dotY; j++ ) {
    for ( i = 0; i < figure[figNum].dotX; i++ ) {
      figure[figNum].pixel[i][j].br = 0.;

      // 斜め線

      x = (double)i * figure[figNum].dotDiam - x_half;
      y = y_half - (double)j * figure[figNum].dotDiam;

      if ( sqrt(x*x + y*y) < x_half  && 
           y < x + BAR_W2 * 1.4142 &&
           y > x - BAR_W2 * 1.4142 ) {
        figure[figNum].pixel[i][j].br = figure[figNum].color;
      }

      if ( sqrt(x*x + y*y) < x_half  && 
           y < (-x + BAR_W2 * 1.4142) &&
           y > (-x - BAR_W2 * 1.4142) ) {
        figure[figNum].pixel[i][j].br = figure[figNum].color;
      }

    }
  }

  // 画像の設定はここまで

  // 視空間におけるX,Y,Z座標を求める

  for (j=0; j < figure[figNum].dotX; j++) {
    for (i=0; i < figure[figNum].dotY; i++) {

      figure[figNum].pixel[i][j].x = figure[figNum].centerX 
        - x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * sin(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * cos(x_angle);
      figure[figNum].pixel[i][j].y = figure[figNum].centerY 
        + x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * cos(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * sin(x_angle);
      figure[figNum].pixel[i][j].z = figure[figNum].centerZ 
        + y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * cos(y_angle);
    }   
  }

}

// ●マーク

#define    RADIUS    25.
#define    SIN_45    0.70710678

void initFigCircle( int figNum ) {
  int    i, j;
  double x, y, x_dot2, y_dot2, x_half, y_half, x_angle, y_angle, dj;
  double r;
  double angleFig;
  double x_edge1, x_edge2, y_edge1, y_edge2;

  x_dot2 = (double)figure[figNum].dotX/2;
  y_dot2 = (double)figure[figNum].dotY/2;
  x_half = (double)(figure[figNum].dotX)/2. * figure[figNum].dotDiam;
  y_half = (double)(figure[figNum].dotY)/2. * figure[figNum].dotDiam;
  x_angle = figure[figNum].angleX * TO_RAD;
  y_angle = figure[figNum].angleY * TO_RAD;

  // 画像の設定

  for ( j = 0; j < figure[figNum].dotY; j++ ) {
    for ( i = 0; i < figure[figNum].dotX; i++ ) {
      figure[figNum].pixel[i][j].br = 0.;

      x = (double)i * figure[figNum].dotDiam - x_half;
      y = y_half - (double)j * figure[figNum].dotDiam;

      if ( sqrt(x*x + y*y) < RADIUS ) {
        figure[figNum].pixel[i][j].br = figure[figNum].color;
      }
 
    }
  }

  // 画像の設定はここまで

  // 視空間におけるX,Y,Z座標を求める

  for (j=0; j < figure[figNum].dotY; j++) {
    for (i=0; i < figure[figNum].dotX; i++) {

      figure[figNum].pixel[i][j].x = figure[figNum].centerX 
        - x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * sin(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * cos(x_angle);
      figure[figNum].pixel[i][j].y = figure[figNum].centerY 
        + x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * cos(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * sin(x_angle);
      figure[figNum].pixel[i][j].z = figure[figNum].centerZ 
        + y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * cos(y_angle);
    }   
  }

}

// pgmファイルによる刺激パターン

int initFigPGM( int figNum, char *fileName ) {
  FILE   *fp;
  char   header[256];
  unsigned char pixel;
  int    x, y, level, i, j;
  double x_dot2, y_dot2, x_half, y_half, x_angle, y_angle;

  fp = fopen( fileName, "r" );
  fgets( header, 256, fp );
  if ( !strcmp(header, "P5") ) {
    printf( "not PGM file\n" );
    return 1;
  }

  while ( 1 ) {
    fgets( header, 256, fp );
    if ( header[0] > '0' && header[0] < '9' ) {
      sscanf( header, "%i %i", &x, &y );
      fgets( header, 256, fp );
      sscanf( header, "%i", &level );
//      printf( "x, y, level: %d, %d, %d\n", x, y, level );
      break;
    }
  }

  figure[figNum].dotX = x;
  figure[figNum].dotY = y;

  for ( j = 0; j < y ; j++ ) {
//    for ( i = 0; i < x ; i++ ) {
    for ( i = x-1; i >= 0 ; i-- ) {
      fread( &pixel, 1, 1, fp );
      figure[figNum].pixel[i][j].br = 2.*(double)pixel/(double)level - 1.;
/*
      if ( i == (x-1)/2 ) {
        figure[figNum].pixel[i][j].br = 0.;
      }
*/
//      printf( "%4.2lf ", figure[figNum].pixel[i][j].br );
    }
//    printf( "\n" );
  }

  fclose( fp );

  // 視空間におけるX,Y,Z座標を求める

  x_dot2 = (double)figure[figNum].dotX/2;
  y_dot2 = (double)figure[figNum].dotY/2;
  x_half = (double)(figure[figNum].dotX)/2. * figure[figNum].dotDiam;
  y_half = (double)(figure[figNum].dotY)/2. * figure[figNum].dotDiam;
  x_angle = figure[figNum].angleX * TO_RAD;
  y_angle = figure[figNum].angleY * TO_RAD;

  for (j=0; j < figure[figNum].dotY; j++) {
    for (i=0; i < figure[figNum].dotX; i++) {

      figure[figNum].pixel[i][j].x = figure[figNum].centerX 
        - x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * sin(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * cos(x_angle);
      figure[figNum].pixel[i][j].y = figure[figNum].centerY 
        + x_half * (double)(figure[figNum].dotX/2-i)/x_dot2 * cos(x_angle)
        - y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * sin(y_angle) * sin(x_angle);
      figure[figNum].pixel[i][j].z = figure[figNum].centerZ 
        + y_half * (double)(figure[figNum].dotY/2-j)/y_dot2 * cos(y_angle);
    }   
  }

  return 0;
}

// ミツバチの飛翔姿勢の影響を加える
// Y軸の周りの回転
// 2001/10/17追加、2001/10/23修正
// Xについての座標系が逆なので、回転角度の符合を反転して回転させる。

void fixFig( int figNum ) {
  int     i, j;
  double  x, z, th;

  th = - beeParam.flightAngle * TO_RAD;  // 姿勢角度の符合を逆転させる

  for (j=0; j < figure[figNum].dotY; j++) {
    for (i=0; i < figure[figNum].dotX; i++) {
      x = figure[figNum].pixel[i][j].x;
      z = figure[figNum].pixel[i][j].z;

      figure[figNum].pixel[i][j].x = x * cos( th ) - z * sin( th );
      figure[figNum].pixel[i][j].z = x * sin( th ) + z * cos( th );
    }
  }
         
}

// チェックのために投射画像をプリントアウト 

void printFig( int figNum ) {
   int   i, j;

  for (j=0; j < figure[figNum].dotY; j++) {
    for (i=0; i < figure[figNum].dotX; i++) {
      if (figure[figNum].pixel[i][j].br == 0.) {
	printf( "o" );
      } else if (figure[figNum].pixel[i][j].br == 1.) {
	printf( "*" );
      } else if (figure[figNum].pixel[i][j].br == -1.) {
	printf( "@" );
      }
    }
    printf( "\n" );
  }
}
