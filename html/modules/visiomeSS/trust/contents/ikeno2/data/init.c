/*****************************************************************************

 Bee Vision  - Simulation Program of Compound Eye Vision -

 ----------------------------------------------------------------------------
 
 ������ط��δؿ� 

********************************************** (c) Hidetoshi Ikeno **********/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "beeVision.h"

extern compound_eye rightEye[NUM_CE], leftEye[NUM_CE];
extern VPL1cell     rightVPL1[NUM_VPL1], leftVPL1[NUM_VPL1];
extern VPL2cell     rightVPL2[NUM_VPL2], leftVPL2[NUM_VPL2];

extern parameters   beeParam;
extern target figure[N_FIGURE];

/*****************************************************************************

  ���ϥե�����ξõ�
 ---------------------------------------------------------------------------
   ./TIFF/bothEyeXY.tif
   ./TIFF/bothEyeYZ.tif
   ./TIFF/leftEyeXZ.tif
   ./TIFF/rightEyeXZ.tif

   ./TIFF/bothVPL1.tif
   ./TIFF/bothVPL2.tif

*****************************************************************************/

void rmFiles() {
  system( "rm ./TIFF/bothEyeXY.tif" );
  system( "rm ./TIFF/bothEyeYZ.tif" );
  system( "rm ./TIFF/leftEyeXZ.tif" );
  system( "rm ./TIFF/rightEyeXZ.tif" );
  system( "rm ./TIFF/bothEyeXZ.tif" );
  system( "rm ./TIFF/greyBothEyeXZ.tif" );
  system( "rm ./TIFF/greyRightEyeXZ.tif" );
  system( "rm ./TIFF/greyLeftEyeXZ.tif" );

  system( "rm ./TIFF/bothVPL1.tif" );
  system( "rm ./TIFF/bothVPL2.*.tif" );
}

/*****************************************************************************

  beeVsion.conf���ɤ߹���
 ---------------------------------------------------------------------------
  headR: �ߥĥХ�Ƭ����Ⱦ��

  flightAngle: ���Ƴ���

  figCenter: �󼨿޷����濴��ɸ
  figCenter: �޷����󼨳���

*****************************************************************************/

void readConfig() {
  char  line[256];
  char  *pline, *keyword, *value;
  FILE  *fp;
  double a;
  int    figNum;

  fp = fopen( "beeVision.conf", "r" );

  while ( 1 ) {
    if ( fgets( line, 256, fp ) == NULL ) break;

    // ��Ƭ��#�ξ�硢�����=���ʤ��Ԥ��ɤ����Ф�
    if ( line[0] == '#' ) continue;
    if ( strstr( line, "=" ) == NULL ) continue;

    // #�ʹߤϥ����ȤȤ���
    if ( !(strstr( line, "#" ) == NULL) ) {
      pline = strtok( line, "#" );
      strcpy( line, pline );
    }

    keyword = strtok( line, "=" );

    // �ߥĥХ��δ����إѥ�᡼��

    if ( !(strstr( keyword, "headR" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.headR );
       printf( "headR: %lf\n", beeParam.headR );
    }

    if ( !(strstr( keyword, "maxVC" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.maxVC );
       printf( "maxVC: %lf\n", beeParam.maxVC );
    }
    if ( !(strstr( keyword, "minVC" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.minVC );
       printf( "minVC: %lf\n", beeParam.minVC );
    }

    if ( !(strstr( keyword, "venPh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.venPh );
       printf( "venPh: %lf\n", beeParam.venPh );
    }

    if ( !(strstr( keyword, "dorPh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.dorPh );
       printf( "dorPh: %lf\n", beeParam.dorPh );
    }

    if ( !(strstr( keyword, "stepPh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.stepPh );
       printf( "stepPh: %lf\n", beeParam.stepPh );
    }

    if ( !(strstr( keyword, "venLimit" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.venLimit );
       printf( "venLimit: %lf\n", beeParam.venLimit );
    }
    if ( !(strstr( keyword, "dorLimit" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.dorLimit );
       printf( "dorLimit: %lf\n", beeParam.dorLimit );
    }

    // �Ĵ��ʿ�����Υѥ�᡼��

    if ( !(strstr( keyword, "frontTh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.frontTh );
       printf( "frontTh: %lf\n", beeParam.frontTh );
    }
    if ( !(strstr( keyword, "rearTh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.rearTh );
       printf( "rearTh: %lf\n", beeParam.rearTh );
    }
    beeParam.thW2 = (beeParam.frontTh - beeParam.rearTh)/2.; 
    beeParam.centerTh = beeParam.rearTh + beeParam.thW2;

    if ( !(strstr( keyword, "stepTh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.stepTh );
       printf( "stepTh: %lf\n", beeParam.stepTh );
    }

// initEye3()�ǻ��Ѥ���

    if ( !(strstr( keyword, "xPostMax" ) == NULL) ) {
       value = strtok( NULL, "," );
       sscanf( value, "%lf", &beeParam.xPostMax );
       printf( "xPostMax: %lf\n", beeParam.xPostMax );
    }

    if ( !(strstr( keyword, "xAntMax" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.xAntMax );
       printf( "xAntMax: %lf\n", beeParam.xAntMax );
    }

    if ( !(strstr( keyword, "rotAng" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.rotAng );
       printf( "rotMax: %lf\n", beeParam.rotAng );
    }

    if ( !(strstr( keyword, "rotXoff" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.rotXoff );
       printf( "rotXoff: %lf\n", beeParam.rotXoff );
    }

    if ( !(strstr( keyword, "rotYoff" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.rotYoff );
       printf( "rotYoff: %lf\n", beeParam.rotYoff );
    }

    // �Ĵ�λ������

    if ( !(strstr( keyword, "omDeg" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omDeg );
       printf( "omDeg: %lf\n", beeParam.omDeg );
    }

    // �Ĵ��������

    if ( !(strstr( keyword, "omVenMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omVenMax );
       printf( "omVenMax: %lf\n", beeParam.omVenMax );
    }
    if ( !(strstr( keyword, "omDorMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omDorMax );
       printf( "omDorMax: %lf\n", beeParam.omDorMax );
    }

    if ( !(strstr( keyword, "omFrMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omFrMax );
       printf( "omFrMax: %lf\n", beeParam.omFrMax );
    }
    if ( !(strstr( keyword, "omReMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omReMax );
       printf( "omReMax: %lf\n", beeParam.omReMax );
    }

    // �Ĵ�μ������ɽ���������ؿ��η���

    if ( !(strstr( keyword, "omRFcoef" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.omRFcoef );
       printf( "omRFcoef: %lf\n", beeParam.omRFcoef );
    }

    // �Ĵ�α����򵬳ʲ�����Ȥ��η���

    if ( !(strstr( keyword, "sigCoef" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.sigCoef );
       printf( "sigCoef: %lf\n", beeParam.sigCoef );
    }

    // ���Ƴ���

    if ( !(strstr( keyword, "flightAngle" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.flightAngle );
       printf( "flightAngle: %lf\n", beeParam.flightAngle );
    }

    // VPL1: ������������غ�˦��������

    if ( !(strstr( keyword, "numOfVPL1" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%d", &beeParam.numOfVPL1 );
       printf( "numOfVPL1: %d\n", beeParam.numOfVPL1 );
    }

    // VPL1: ���������غ�˦�κǾ����������

    if ( !(strstr( keyword, "VPL1rf_min" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL1rf_min );
       printf( "VPL1rf_min: %lf\n", beeParam.VPL1rf_min );
    }

    //VPL1: ���������غ�˦�κ�����������

    if ( !(strstr( keyword, "VPL1rf_max" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL1rf_max );
       printf( "VPL1rf_max: %lf\n", beeParam.VPL1rf_max );
    }

    // VPL2: ������������غ�˦��������

    if ( !(strstr( keyword, "numOfVPL2" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%d", &beeParam.numOfVPL2 );
       printf( "numOfVPL2: %d\n", beeParam.numOfVPL2 );
    }

    // VPL2: ���������غ�˦�κǾ����������

    if ( !(strstr( keyword, "VPL2rf_min" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL2rf_min );
       printf( "VPL2rf_min: %lf\n", beeParam.VPL2rf_min );
    }

    // VPL2: ���������غ�˦�κ�����������

    if ( !(strstr( keyword, "VPL2rf_max" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL2rf_max );
       printf( "VPL2rf_max: %lf\n", beeParam.VPL2rf_max );
    }

    /***************** �޷����ɤ߹��� **************************************/ 

    // �޷����濴��ɸ���ɤ߹���

    if ( !(strstr( keyword, "figNumber" ) == NULL) ) {
      value = strtok( NULL, "," ); sscanf( value, "%d", &figNum );
    }

    // �޷����濴��ɸ���ɤ߹���

    if ( !(strstr( keyword, "figCenter" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].centerX );
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].centerY );
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].centerZ );
      printf( "figCenter: %lf, %lf, %lf\n",
              figure[figNum].centerX, 
              figure[figNum].centerY, 
              figure[figNum].centerZ );
    }

    // �޷����󼨳��٤��ɤ߹���

    if ( !(strstr( keyword, "figAngle" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].angleX );
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].angleY );
      printf( "figAngle: %lf, %lf\n",
              figure[figNum].angleX, figure[figNum].angleY );
    }

    // �޷����������ɥåȿ����ɤ߹���

    if ( !(strstr( keyword, "figDotX" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].dotX );
      printf( "figDotX: %d\n", figure[figNum].dotX );
    }
    if ( !(strstr( keyword, "figDotY" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].dotY );
      printf( "figDotY: %d\n", figure[figNum].dotY );
    }

    // �޷����������ɥåȥ��������ɤ߹���

    if ( !(strstr( keyword, "figDotD" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].dotDiam );
      printf( "figDotD: %lf\n", figure[figNum].dotDiam );
    }

    // �޷��ѥ����� -1: pgm file, 0: +, 1: X, 2: ��

    if ( !(strstr( keyword, "figPattern" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].pattern );
      printf( "figPatten: %d\n", figure[figNum].pattern );
    }

    // �޷����󼨤��뤫�����ʤ���  1: �󼨤��롢0: �󼨤��ʤ���

    if ( !(strstr( keyword, "figShow" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].show );
      printf( "figShow: %d\n", figure[figNum].show );
    }

    // �޷��Υ��顼  1, -1��Ȥꤢ�������Ѥ���

    if ( !(strstr( keyword, "figColor" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].color );
      printf( "figColor: %d\n", figure[figNum].color );
    }

    // �޷��ե�����̾

    if ( !(strstr( keyword, "figFile" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%s", &figure[figNum].fileName );
      printf( "figFile: %s\n", figure[figNum].fileName );
    }

  }
  fclose( fp );

  beeParam.numOfFig = figNum+1;  
}

/*****************************************************************************

 ʣ��ν����
 ---------------------------------------------------------------------------
 initEye()����Ѥ���Ȥ���beeVision.conf.base.1���Ѥ���

*****************************************************************************/

int initEye() {
  int    i, p_flag;
  double ph, th; 
  double ven_len, dor_len, c_ven, c_dor;
  double front_th, rear_th, x, w;

  ven_len = beeParam.venPh - beeParam.venLimit;      // ʢ¦�����γ���
  dor_len = beeParam.dorPh - beeParam.dorLimit;      // ��¦�����γ���
  c_ven = ven_len/((beeParam.thW2)*(beeParam.thW2));
  c_dor = dor_len/((beeParam.thW2)*(beeParam.thW2));

  i = 0;
  p_flag = 0;

  // ʢ¦(ventral)��ʣ�������

  for ( ph = beeParam.venPh; ph > 0; ph -= beeParam.stepPh ) {
    if ( ph < beeParam.venLimit ) {
      front_th = beeParam.frontTh; rear_th = beeParam.rearTh;
    } else {
      x = beeParam.venPh - ph; 
      w = sqrt( x/c_ven );
      front_th = beeParam.centerTh + w; rear_th = beeParam.centerTh - w; 
    }
    for ( th = rear_th+p_flag*beeParam.stepTh; 
          th < front_th; 
          th += 2.*beeParam.stepTh ) {
      leftEye[i].r  = beeParam.maxVC;
      rightEye[i].r = beeParam.maxVC;

      leftEye[i].th = th * TO_RAD;          // ��ʿ��������
      leftEye[i].ph = -ph * TO_RAD;         // ��ľ��������
      leftEye[i].br = 0.;                      // ���뤵

      rightEye[i].th = th * TO_RAD;         // ��ʿ��������
      rightEye[i].ph = -ph * TO_RAD;        // ��ľ��������
      rightEye[i].br = 0.;                     // ���뤵

      leftEye[i].z = leftEye[i].r * sin( leftEye[i].ph );
      leftEye[i].x = leftEye[i].r * cos( leftEye[i].ph )
                    * sin( leftEye[i].th );
      leftEye[i].y = leftEye[i].r * cos( leftEye[i].ph )
                    * cos( leftEye[i].th );

      rightEye[i].z = rightEye[i].r * sin( rightEye[i].ph );
      rightEye[i].x = rightEye[i].r * cos( rightEye[i].ph )
                    * sin( rightEye[i].th );
      rightEye[i].y = -rightEye[i].r * cos( rightEye[i].ph )
                    * cos( rightEye[i].th );

      leftEye[i].alpha = ( -beeParam.omReMax 
          + (beeParam.omFrMax+beeParam.omReMax)*(th-beeParam.rearTh)
            /(beeParam.frontTh-beeParam.rearTh)
        ) * TO_RAD;
      leftEye[i].beta = -beeParam.omVenMax * ph/beeParam.venPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      /*
      printf( "om(%d): %lf, %lf, %lf, %lf\n",  
             i, leftEye[i].alpha*TO_DEG,   leftEye[i].beta*TO_DEG,
                rightEye[i].alpha*TO_DEG,  rightEye[i].beta*TO_DEG );
      */

      i++;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;
  }

  // ��¦(dorsal)��ʣ�������

  for ( ph = 0; ph < beeParam.dorPh; ph += beeParam.stepPh ) {
    if ( ph < beeParam.dorLimit ) {
      front_th = beeParam.frontTh; rear_th = beeParam.rearTh;
    } else {
      x = beeParam.dorPh - ph; 
      w = sqrt( x/c_dor );
      front_th = beeParam.centerTh + w; rear_th = beeParam.centerTh - w; 
    }
    for ( th = rear_th+p_flag*beeParam.stepTh; 
          th < front_th; 
          th += 2.*beeParam.stepTh ) {
      leftEye[i].r  = beeParam.maxVC;
      rightEye[i].r = beeParam.maxVC;

      leftEye[i].th = th * TO_RAD; 
      leftEye[i].ph = ph * TO_RAD;
      leftEye[i].br = 0.; 

      rightEye[i].th = th * TO_RAD;         // ��ʿ��������
      rightEye[i].ph = ph * TO_RAD;         // ��ľ��������
      rightEye[i].br = 0.;                     // ���뤵

      leftEye[i].z = leftEye[i].r * sin( leftEye[i].ph );
      leftEye[i].x = leftEye[i].r * cos( leftEye[i].ph )
                    * sin( leftEye[i].th );
      leftEye[i].y = leftEye[i].r * cos( leftEye[i].ph )
                    * cos( leftEye[i].th );

      rightEye[i].z = rightEye[i].r * sin( rightEye[i].ph );
      rightEye[i].x = rightEye[i].r * cos( rightEye[i].ph )
                    * sin( rightEye[i].th );
      rightEye[i].y = -rightEye[i].r * cos( rightEye[i].ph )
                    * cos( rightEye[i].th );

      leftEye[i].alpha = ( -beeParam.omReMax 
          + (beeParam.omFrMax+beeParam.omReMax)*(th-beeParam.rearTh)
            /(beeParam.frontTh-beeParam.rearTh)
        ) * TO_RAD;
      leftEye[i].beta = beeParam.omDorMax * ph/beeParam.dorPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      /*
      printf( "om(%d): %lf, %lf, %lf, %lf\n",  
             i, leftEye[i].alpha*TO_DEG,  leftEye[i].beta*TO_DEG,
                rightEye[i].alpha*TO_DEG, rightEye[i].beta*TO_DEG );
      */

      i++;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;
  }

  beeParam.numOfOM = i;
  printf( "number of compound eyes: %d\n", beeParam.numOfOM );

  return 0;
}

/*****************************************************************************

 ʣ��ν���� 2
 ---------------------------------------------------------------------------
 initEye2()����Ѥ���Ȥ���beeVision.conf.base.2���Ѥ���

*****************************************************************************/

double calcOmFrMax( double ph ) {
  double y, x;

  x = -ph/10. + 6.;
  y = -0.0004 * pow( x, 6 ) + 0.0161 * pow( x, 5 ) - 0.2359 * pow( x, 4 )
    +  1.8472 * pow( x, 3 ) - 7.5935 * x * x + 12.858 * x + 12.827;
  y = y + 90.;

  return y;
}

// ʣ��ü�ο�ʿ�������٤�׻�����

double calcFrontTh( double ph ) {
  double y, x;

  if ( ph > 0. ) {
      y = beeParam.frontTh + 45.*(ph/50.)*(ph/50.);
  } else {
      x = ph/5. + 11.;
      y = -0.0006 * pow( x, 4 ) + 0.0172 * pow( x, 3 )
          -0.1779 * x * x + 0.8148 * x - 0.6364;
      y = y/0.9655 * beeParam.frontTh;
  }

  return  y;
}

double calcRearTh( double ph ) {
  double y, x;

  if ( ph > 0. ) {
      y = beeParam.rearTh - 40.*(ph/50.)*(ph/50.);
  } else {
      x = ph/5. + 11.;
      y = -0.0004 * pow( x, 4 ) + 0.0124 * pow( x, 3 )
          -0.1358 * x * x + 0.6974 * x - 0.5688;
      y = y/1.3 * (beeParam.rearTh);
  }

  return y;
}

// ʣ�㶭����Y��ɸ�����

double compY( double ph ) {
  double x, y;

  x = ph/5. + 10.;
  y = -0.2021 * x * x + 3.5735 * x + 31.53;
  y = y/47.5 * beeParam.headR;

  return y;
}

// ʣ�㶭����Z��ɸ�����

double compZ( double ph ) {
  double x, y;

  if ( ph > 0. ) {
      x = ph/5. + 1.;
      y = -0.1629 * x * x + 4.7947 * x - 4.55;
      y = y/47.5 * beeParam.headR;
  } else {
      x = ph/5. + 10.;
      y = -0.0663 * x * x - 3.1617 * x + 38.042;
      y = -y/47.5 * beeParam.headR;
  }

  return y;
}

int initEye2() {
  int    i, p_flag;
  double ph, th; 
  double front_th, rear_th, x, w;
  double omFrMax;

  i = 0;
  p_flag = 0;

  // ʢ¦(ventral)��ʣ�������

  ph = beeParam.venPh;
  while ( ph > 0. ) {
    front_th = calcFrontTh( -ph );
    rear_th = calcRearTh( -ph );
    omFrMax = calcOmFrMax( -ph );

    th = rear_th + p_flag*beeParam.stepTh;
    while( th < front_th ) { 
      leftEye[i].th = th * TO_RAD;          // ��ʿ��������
      leftEye[i].ph = -ph * TO_RAD;         // ��ľ��������
      leftEye[i].br = 0.;                      // ���뤵

      rightEye[i].th = th * TO_RAD;         // ��ʿ��������
      rightEye[i].ph = -ph * TO_RAD;        // ��ľ��������
      rightEye[i].br = 0.;                     // ���뤵

      leftEye[i].z = compZ( -ph );
      leftEye[i].y = (compY( -ph )-1.0)*cos(th*TO_RAD) + 1.0;
      leftEye[i].x = (compY( -ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
			   leftEye[i].y * leftEye[i].y +  
			   leftEye[i].z * leftEye[i].z );  

      rightEye[i].z = compZ( -ph );
      rightEye[i].y = -(compY( -ph )-1.0)*cos(th*TO_RAD) - 1.0;
      rightEye[i].x = (compY( -ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );  

      if ( front_th != rear_th ) {
        leftEye[i].alpha = ( -beeParam.omReMax 
            + (omFrMax+beeParam.omReMax)*(th-rear_th)
              /(front_th-rear_th)
          ) * TO_RAD;
      } else {
	  leftEye[i].alpha = 25. * TO_RAD;
      }
      leftEye[i].beta = -beeParam.omVenMax * ph/beeParam.venPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      /*
      printf( "om(%d): %lf, %lf, %lf, %lf\n",  
             i, leftEye[i].alpha*TO_DEG,   leftEye[i].beta*TO_DEG,
                rightEye[i].alpha*TO_DEG,  rightEye[i].beta*TO_DEG );
      */

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph -= beeParam.stepPh;
  }

  // ��¦(dorsal)��ʣ�������

  ph = 0.;
  while ( ph < beeParam.dorPh ) {
    front_th = calcFrontTh( ph );
    rear_th = calcRearTh( ph );
    omFrMax = calcOmFrMax( ph );

    th = rear_th + p_flag*beeParam.stepTh; 
    while ( th < front_th ) {
      leftEye[i].th = th * TO_RAD; 
      leftEye[i].ph = ph * TO_RAD;
      leftEye[i].br = 0.; 

      rightEye[i].th = th * TO_RAD;         // ��ʿ��������
      rightEye[i].ph = ph * TO_RAD;         // ��ľ��������
      rightEye[i].br = 0.;                     // ���뤵

      leftEye[i].z = compZ( ph );
      leftEye[i].y = (compY( ph )-1.0)*cos(th*TO_RAD) + 1.0;
      leftEye[i].x = (compY( ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
			   leftEye[i].y * leftEye[i].y +  
			   leftEye[i].z * leftEye[i].z );  


      rightEye[i].z = compZ( ph );
      rightEye[i].y = -(compY( ph )-1.0)*cos(th*TO_RAD) - 1.0;
      rightEye[i].x = (compY( ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );

      if ( front_th != rear_th ) {
        leftEye[i].alpha = ( -beeParam.omReMax 
            + (omFrMax+beeParam.omReMax)*(th-rear_th)
              /(front_th-rear_th)
          ) * TO_RAD;
      } else {
	  leftEye[i].alpha = 25. * TO_RAD;
      }

      leftEye[i].beta = beeParam.omDorMax * ph/beeParam.dorPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph += beeParam.stepPh;
  }

  beeParam.numOfOM = i;
  printf( "number of compound eyes: %d\n", beeParam.numOfOM );

  return 0;
}

/*****************************************************************************

 ʣ��ν���� 3
 ʣ��������ʱߤǶ�����ƥ�ǥ벽����
 ---------------------------------------------------------------------------
 initEye3()����Ѥ���Ȥ���beeVision.conf.base.3���Ѥ���

*****************************************************************************/

double rMapping( double ph ) {
  double x, f, rMax;

  x = ph/5. + 11.;
  f = -0.0008 * x * x + 0.0042 * x + 1.0509;
  rMax = beeParam.headR * f; 

  return rMax;
}

int initEye3() {
  int    i, p_flag;
  double ph, th; 
  double antTh, postTh, x, w;
  double omFrMax;

  double rMax, z, xPost, xAnt, y, zMax, r2;
  double rotA, xOff, yOff;

  i = 0;
  p_flag = 0;   // �Ĵ��ߤ��㤤�����֤��뤿��Τդ餰

  // ʢ¦(ventral)��ʣ�������

  ph = beeParam.venPh;   // Z�����γ���
  zMax = beeParam.headR * atan( -beeParam.venPh * TO_RAD ); // �����Z���� 
  while ( ph > 0. ) {
    z = beeParam.headR * atan( -ph * TO_RAD ); 
    xPost = sqrt( beeParam.xPostMax * beeParam.xPostMax 
                  * (1. - (z*z)/(zMax*zMax))
                );
    xAnt  = sqrt( beeParam.xAntMax * beeParam.xAntMax 
                  * (1. - (z*z)/(zMax*zMax))
                );
    
    postTh = -tan( xPost/beeParam.headR ) * TO_DEG;  // �������γ���
    antTh = tan( xAnt/beeParam.headR ) * TO_DEG;  // �������γ���
    omFrMax = calcOmFrMax( -ph );   // �������κ���������������

    rMax = rMapping( -ph );

    th = postTh + p_flag*beeParam.stepTh;
    while( th < antTh ) { 
      leftEye[i].ph = -ph * TO_RAD;         // ��ľ��������
      leftEye[i].br = 0.;                      // ���뤵
     
      leftEye[i].z = rMax * sin( -ph * TO_RAD );
      leftEye[i].y = rMax * cos( -ph * TO_RAD ) * cos( th * TO_RAD );
      leftEye[i].x = rMax * cos( -ph * TO_RAD ) * sin( th * TO_RAD );

      // ��ž������

      rotA = beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = beeParam.rotYoff;

      leftEye[i].y = (leftEye[i].y-yOff) * cos(rotA) 
	           - (leftEye[i].x-xOff) * sin(rotA) + yOff;
      leftEye[i].x = (leftEye[i].y-yOff) * sin(rotA)
                   + (leftEye[i].x-xOff) * cos(rotA) + xOff;

/*
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
           leftEye[i].y * leftEye[i].y +  
	   leftEye[i].z * leftEye[i].z );
      leftEye[i].th = atan( leftEye[i].x/(-leftEye[i].y) );
      leftEye[i].ph = atan( leftEye[i].z/(-leftEye[i].y) );
*/
      // ���ܤˤĤ���

      rightEye[i].ph = -ph * TO_RAD;        // ��ľ��������
      rightEye[i].br = 0.;                     // ���뤵

      rightEye[i].z = rMax * sin( -ph * TO_RAD );
      rightEye[i].y = -rMax * cos( -ph * TO_RAD ) * cos( th * TO_RAD );
      rightEye[i].x = rMax * cos( -ph * TO_RAD ) * sin( th * TO_RAD );

      // ��ž������

      rotA = -beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = -beeParam.rotYoff;

      rightEye[i].y = (rightEye[i].y-yOff) * cos(rotA) 
                    - (rightEye[i].x-xOff) * sin(rotA) + yOff;
      rightEye[i].x = (rightEye[i].y-yOff) * sin(rotA)
                    + (rightEye[i].x-xOff) * cos(rotA) + xOff;

/*
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );  
*/

      // ���������

      leftEye[i].alpha = ( -beeParam.omReMax  
            + (omFrMax+beeParam.omReMax)*(th-postTh)/(antTh-postTh)
           ) * TO_RAD;
      leftEye[i].beta = -beeParam.omVenMax * ph/beeParam.venPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph -= beeParam.stepPh;
  }

  // ��¦(dorsal)��ʣ�������

  ph = 0.;   // Z�����γ���
  zMax = beeParam.headR * atan( beeParam.dorPh * TO_RAD ); // �����Z���� 
  while ( ph < beeParam.dorPh ) {
    z = beeParam.headR * atan( ph * TO_RAD ); 
    xPost = pow( beeParam.xPostMax * beeParam.xPostMax 
		 * beeParam.xPostMax * beeParam.xPostMax 
		 * (1. - (z*z)/(zMax*zMax)), 0.25 );
    xAnt  = pow( beeParam.xAntMax * beeParam.xAntMax
                 * beeParam.xAntMax * beeParam.xAntMax		 
		 * (1. - (z*z)/(zMax*zMax)), 0.25 );

    //   xAnt =  beeParam.xAntMax * (ph/50.+1.);

    postTh = -tan( xPost/beeParam.headR ) * TO_DEG;  // �������γ���
    antTh = tan( xAnt/beeParam.headR ) * TO_DEG;  // �������γ���
    omFrMax = calcOmFrMax( ph );   // �������κ���������������

    rMax = rMapping( ph );

    th = postTh + p_flag*beeParam.stepTh;
    while( th < antTh ) { 
      leftEye[i].ph = ph * TO_RAD;         // ��ľ��������
      leftEye[i].br = 0.;                      // ���뤵
     
      leftEye[i].z = rMax * sin( ph * TO_RAD );
      leftEye[i].y = rMax * cos( ph * TO_RAD ) * cos( th * TO_RAD );
      leftEye[i].x = rMax * cos( ph * TO_RAD ) * sin( th * TO_RAD );

      // ��ž������

      rotA = beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = beeParam.rotYoff;

      leftEye[i].y = (leftEye[i].y-yOff) * cos(rotA) 
	           - (leftEye[i].x-xOff) * sin(rotA) + yOff;
      leftEye[i].x = (leftEye[i].y-yOff) * sin(rotA)
                   + (leftEye[i].x-xOff) * cos(rotA) + xOff;

/*
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
			   leftEye[i].y * leftEye[i].y +  
			   leftEye[i].z * leftEye[i].z );  
      leftEye[i].th = atan( leftEye[i].x/leftEye[i].y );
      leftEye[i].ph = atan( leftEye[i].z/leftEye[i].y );
*/

      // ���ܤˤĤ���

      rightEye[i].ph = ph * TO_RAD;        // ��ľ��������
      rightEye[i].br = 0.;                     // ���뤵

      rightEye[i].z = rMax * sin( ph * TO_RAD );
      rightEye[i].y = -rMax * cos( ph * TO_RAD ) * cos( th * TO_RAD );
      rightEye[i].x = rMax * cos( ph * TO_RAD ) * sin( th * TO_RAD );

      // ��ž������

      rotA = -beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = -beeParam.rotYoff;

      rightEye[i].y = (rightEye[i].y-yOff) * cos(rotA) 
                    - (rightEye[i].x-xOff) * sin(rotA) + yOff;
      rightEye[i].x = (rightEye[i].y-yOff) * sin(rotA)
                    + (rightEye[i].x-xOff) * cos(rotA) + xOff;

/*
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );  
*/

      // ���������

      leftEye[i].alpha = ( -beeParam.omReMax  
            + (omFrMax+beeParam.omReMax)*(th-postTh)/(antTh-postTh)
           ) * TO_RAD;
      leftEye[i].beta = beeParam.omVenMax * ph/beeParam.dorPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }

      rightEye[i].beta = leftEye[i].beta;

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph += beeParam.stepPh;
  }

  beeParam.numOfOM = i;
  printf( "number of compound eyes: %d\n", beeParam.numOfOM );

  return 0;
}


/*****************************************************************************

 ����������(VPL1)���к�˦�ν����
 ---------------------------------------------------------------------------

*****************************************************************************/

int initVPL1() {
  int    i, j, k, refOM;
  double degRF, radRF;
  double diffTh, diffPh, diffAngle;

  for ( i = 0; i < beeParam.numOfVPL1; i++ ) {

    // ��¦

    leftVPL1[i].respMode = 0;
//    leftVPL1[i].RFtype = rand() % VPL1_RF_NUM;
    leftVPL1[i].RFtype = 0;
    leftVPL1[i].RFcoef = 0.;
    //    leftVPL1[i].RFcoef = VPL1_RF_COEF * (double)rand()/RAND_MAX * TO_RAD;

    // ���Ȥʤ�Ĵ�����ʺ�¦��

    refOM = rand() % beeParam.numOfOM;

    leftVPL1[i].x = leftEye[refOM].x;    
    leftVPL1[i].y = leftEye[refOM].y;    
    leftVPL1[i].z = leftEye[refOM].z;    

    leftVPL1[i].r  = leftEye[refOM].r;    
    leftVPL1[i].th = leftEye[refOM].th;    
    leftVPL1[i].ph = leftEye[refOM].ph;    

    leftVPL1[i].alpha = leftEye[refOM].alpha;    
    leftVPL1[i].beta  = leftEye[refOM].beta;    

    // ��¦�ˤĤ��Ƽ�����ȤĤʤ��äƤ���Ĵ������

    //    radRF = beeParam.VPL1rf_max * TO_RAD;
    degRF = beeParam.VPL1rf_min 
          + (beeParam.VPL1rf_max-beeParam.VPL1rf_min) 
          * (double)rand()/RAND_MAX; 
    radRF = degRF * TO_RAD;
    leftVPL1[i].rfAngle = radRF;

    leftVPL1[i].rfAngle = beeParam.VPL1rf_min;

    k = 0;
    for ( j = 0; j < beeParam.numOfOM; j++ ) {
      diffTh = fabs( leftEye[j].alpha - leftVPL1[i].alpha );
      diffPh = fabs( leftEye[j].beta - leftVPL1[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        leftVPL1[i].connectOM[k] = j; k++;
      }
    }
    leftVPL1[i].conNumOfOM = k;    
//    printf( "leftVPL1[%d]: %d, %d, %lf\n", i, k, 
//    leftVPL1[i].RFtype, leftVPL1[i].RFcoef  );

    // ��¦

    rightVPL1[i].respMode = 0;
//    rightVPL1[i].RFtype = rand() % VPL1_RF_NUM;
    rightVPL1[i].RFtype = 0;
    rightVPL1[i].RFcoef = 0.;
    // rightVPL1[i].RFcoef = VPL1_RF_COEF * (double)rand()/RAND_MAX * TO_RAD;

    // ���Ȥʤ�Ĵ�����ʱ�¦��

//  �����оݤˤ���Ȥ��ˤϥ����Ȥˤ���
//    refOM = rand() % beeParam.numOfOM;

    rightVPL1[i].x = rightEye[refOM].x;    
    rightVPL1[i].y = rightEye[refOM].y;    
    rightVPL1[i].z = rightEye[refOM].z;    

    rightVPL1[i].r  = rightEye[refOM].r;    
    rightVPL1[i].th = rightEye[refOM].th;    
    rightVPL1[i].ph = rightEye[refOM].ph;    

    rightVPL1[i].alpha = rightEye[refOM].alpha;    
    rightVPL1[i].beta  = rightEye[refOM].beta;    

    // ��¦�ˤĤ��Ƽ�����ȤĤʤ��äƤ���Ĵ������

    //    radRF = beeParam.VPL1rf_max * TO_RAD;
//  �����оݤˤ���Ȥ��ˤϥ����Ȥˤ���
//    degRF = beeParam.VPL1rf_min 
//          + (beeParam.VPL1rf_max-beeParam.VPL1rf_min) 
//          * (double)rand()/RAND_MAX; 
//    radRF = degRF * TO_RAD; 
    rightVPL1[i].rfAngle = radRF;

    k = 0;
    for ( j = 0; j < beeParam.numOfOM; j++ ) {
      diffTh = fabs( rightEye[j].alpha - rightVPL1[i].alpha );
      diffPh = fabs( rightEye[j].beta - rightVPL1[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        rightVPL1[i].connectOM[k] = j; k++;
      }
    }
    rightVPL1[i].conNumOfOM = k;    
    //printf( "rightVPL1[%d]: %d\n", i, k );

  }

  return 0;
}

/*****************************************************************************

 ����������(VPL2)���к�˦�ν����
 ---------------------------------------------------------------------------

*****************************************************************************/

int initVPL2() {
  int    i, j, k, refVPL1;
  double degRF, radRF;
  double diffTh, diffPh, diffAngle;

  for ( i = 0; i < beeParam.numOfVPL2; i++ ) {

    // ��¦

    leftVPL2[i].respMode = 0;
    leftVPL2[i].RFtype = rand() % VPL2_RF_NUM;
    //    leftVPL2[i].RFtype = 0;

    // ���Ȥʤ�Ĵ�����ʺ�¦��

    refVPL1 = rand() % beeParam.numOfVPL1;

    leftVPL2[i].x = leftVPL1[refVPL1].x;    
    leftVPL2[i].y = leftVPL1[refVPL1].y;    
    leftVPL2[i].z = leftVPL1[refVPL1].z;    

    leftVPL2[i].r  = leftVPL1[refVPL1].r;    
    leftVPL2[i].th = leftVPL1[refVPL1].th;    
    leftVPL2[i].ph = leftVPL1[refVPL1].ph;    

    leftVPL2[i].alpha = leftVPL1[refVPL1].alpha;    
    leftVPL2[i].beta  = leftVPL1[refVPL1].beta;    

    // ��¦�ˤĤ��Ƽ�����ȤĤʤ��äƤ���Ĵ������

    degRF = beeParam.VPL2rf_min 
          + (beeParam.VPL2rf_max-beeParam.VPL2rf_min) 
          * (double)rand()/RAND_MAX; 
    radRF = degRF * TO_RAD; 
    leftVPL2[i].rfAngle = radRF;

    k = 0;
    for ( j = 0; j < beeParam.numOfVPL1; j++ ) {
      diffTh = fabs( leftVPL1[j].alpha - leftVPL2[i].alpha );
      diffPh = fabs( leftVPL1[j].beta - leftVPL2[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        leftVPL2[i].connectVPL1[k] = j; k++;
      }
    }
    leftVPL2[i].conNumOfVPL1 = k;    
    //    printf( "leftVPL2[%d]: %d\n", i, k );

    // ��¦

    rightVPL2[i].respMode = 0;

// ��������פ�����Ȥ��ˤϺ���RFtype�򥳥ԡ����� 
//    rightVPL2[i].RFtype = rand() % VPL2_RF_NUM;
    rightVPL2[i].RFtype = leftVPL2[i].RFtype;

    // ���Ȥʤ�Ĵ�����ʱ�¦��

// ��������פ�����Ȥ��ˤϥ����Ȥˤ���
//    refVPL1 = rand() % beeParam.numOfVPL1;

    rightVPL2[i].x = rightVPL1[refVPL1].x;    
    rightVPL2[i].y = rightVPL1[refVPL1].y;    
    rightVPL2[i].z = rightVPL1[refVPL1].z;    

    rightVPL2[i].r  = rightVPL1[refVPL1].r;    
    rightVPL2[i].th = rightVPL1[refVPL1].th;    
    rightVPL2[i].ph = rightVPL1[refVPL1].ph;    

    rightVPL2[i].alpha = rightVPL1[refVPL1].alpha;    
    rightVPL2[i].beta  = rightVPL1[refVPL1].beta;    

    // ��¦�ˤĤ��Ƽ�����ȤĤʤ��äƤ���Ĵ������

// ��������פ�����Ȥ��ˤϥ����Ȥˤ���
//    degRF = beeParam.VPL2rf_min 
//          + (beeParam.VPL2rf_max-beeParam.VPL2rf_min) 
//          * (double)rand()/RAND_MAX; 
//    radRF = degRF * TO_RAD; 
    rightVPL2[i].rfAngle = radRF;

    k = 0;
    for ( j = 0; j < beeParam.numOfVPL1; j++ ) {
      diffTh = fabs( rightVPL1[j].alpha - rightVPL2[i].alpha );
      diffPh = fabs( rightVPL1[j].beta - rightVPL2[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        rightVPL2[i].connectVPL1[k] = j; k++;
      }
    }
    rightVPL2[i].conNumOfVPL1 = k;    
    // printf( "rightVPL2[%d]: %d\n", i, k );

  }
  return 0;
}

