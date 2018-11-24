/*****************************************************************************

 Bee Vision  - Simulation Program of Honeybee Compound Eye Vision -
            (c) Hidetoshi Ikeno/Himeji Institute of Technology

 ----------------------------------------------------------------------------

$B%G%#%l%/%H%j(B
  ./ _____________        
     |__TIFF/___XY/       TIFF files of XY view
     |       |__XZleft/   TIFF files of XZ view (left eye)
     |       |__XZright/  TIFF files of XZ view (right eye)
     |       |__YZ/       TIFF files of YZ view
     |__Conf/             config files for simulation               
     |__Results/          results files
     |__Responses/        cell responses

$B%3%s%Q%$%kJ}K!(B
  (i686)
  % make

$B<B9TJ}K!(B
  % beeVision -b/-v number -plot/-noplot :
              -b : $B%P%C%A$G%7%_%e%l!<%7%g%s$r<B9T(B
              -v : $B%P!<%8%g%s$NI=<((B
              number: $B%7%_%e%l!<%7%g%s7ONs$K$*$1$k%7!<%1%s%7%c%k%J%s%P!<(B
              -plot: $B%$%a!<%8%U%!%$%k$r:n@.$9$k(B
              -noplot: $B%$%a!<%8%U%!%$%k$r:n@.$7$J$$(B

$BCm0UE@(B
  (1) $B%0%i%U%#%C%/I=<($K$O!"(BDISLIN(http://www.linmpi.mpg.de/dislin)$B$r;HMQ(B
      $B$"$i$+$8$a!"(Bdislin$B$r%$%s%9%H!<%k$7$F$*$/I,MW$,$"$k!#(B
      beeVision21.c$B$HF1$8%G%#%l%/%H%j$K(Bdislin.h$B$r$*$/!#(B
  (2) $B<B9T$K$*$$$F$O(B, beeVision.conf$B%U%!%$%k$rFI$_9~$`!#(B
  (3) Ver.3 $B$h$j!"(BbeeVision.conf$B$G%Q%i%a!<%?5Z$S;I7c>r7o$r@_Dj$9$k$h$&$K$7$?!#(B
      $B=>$C$F!"(BVer.2.*, Ver. 3.*$B$G$O(BbeeVision.conf$B$N9=@.$,Bg$-$/0[$J$k!#(B

 ----------------------------------------------------------------------------

2001/09/08: Start Project
2001/09/10: Version 2.0       $B%W%m%0%i%`$N4pK\It$,$G$-$?!#(B
2001/09/11: Version 2.1       $B;k@~%Y%/%H%k3QEY(Balpha, beta$B$rDI2C!#(B
2001/09/14: Version 2.2       $B0l1~K~B-$$$/%l%Y%k$K$J$C$?!#(B
2001/09/15: Version 2.21      $B>r7o@_Dj!"%P%C%A=hM}5!G=$rDI2C$7$?!#(B
2001/09/16: Version 2.22      $B:84c$N3QEY@_Dj$K4X$9$k%P%0$r=$@5!#(B
2001/09/17: Version 2.23      $B8D4cG[CV$NJ}K!$rJQ99(B, $BBP>]?^7A$NL@$k$5$r(B-1$B!A(B1$B$G(B
                              $BI=$;$P!"L@$k$5$K1~$8$?2hA|$,I=<($5$l$k!#(B
2001/09/17: Version 2.24      $B<B:]$N9TF0<B83%G!<%?$K9g$o$;$k$?$a$K!"Ds<(?^7A$N(B
                              $B%I%C%H%T%C%A$r(B0.5mm$B$H$7!"D>7B(B45mm$B$N1_7A?^7A$rDs<((B
                              $B$9$k$h$&$K$7$?!#(B
2001/10/15: Version 2.25      $BDs<(?^7A$N(BY$B<4$K$D$$$F$N2sE>$KBP$9$k:BI8Jd@5$K(B
                              $B$D$$$F$N%P%0$r=$@5!#(B
                              $B2hA|%T%/%;%k$NL@$k$5(B=0$B$NE@$O7W;;$7$J$$!#(B
2001/10/13: Version 2.26      $B%_%D%P%AHtfF;Q@*$K4p$E$/Jd@5(B fixFig()$B$rDI2C!#(B
2001/11/05: Version 2.30      leftEye, rightEye$B$NJQ?t$rJQ99(B
                              $B$3$l$^$G$H$O:81&$NL\$,H?BP$K$J$k(B
                              ($B%_%D%P%A$rCf?4$K:81&$r7h$a$?(B)
2001/11/14: Version 2.31      $B8D4c$K$*$1$k>HEY$O8w8;$^$G$N5wN%$N#2>h$KH?HfNc(B
                              $B$9$k$h$&$K$7$?!#(B
                              $BDL?.3X2qO@J8;oMQ$N%Q%?!<%s@8@.4X?t$rF~$l$?!#(B
2001/11/16: Version 2.32      $B;k@~%Y%/%H%k$KBP$9$k2hA|$N79$-$N1F6A$rF~$l$k(B
2001/11/26: Version 2.34      $BL\I8?^7A@_Dj$N%P%0$r=$@5(B($B%P!<$NB@$5(B)$B!$(B
                              $B>HEY7W;;$K$*$1$kC10LJQ49$rF~$l$?(B
2002/01/23: Version 2.35      $B;kLn$H%I%C%H$N=E$J$j$N7W;;ItJ,$r=$@5(B
2002/05/01: Version 3.00      conf$B%U%!%$%k$K$h$k%7%_%e%l!<%7%g%s>r7o@_Dj5!G=(B
                              $B$r6/2=$9$k(B
2003/01/14: Version 3.10      $B2hA|>pJs=hM}AX$NDI2C(B

********************************************** (c) Hidetoshi Ikeno **********/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "beeVision.h"

/*****************************************************************************

  $B6&DL%Q%i%a!<%?!"L\I8JQ?t$NDj5A(B

 ----------------------------------------------------------------------------
  rightEye, leftEye: $B:81&J#4c(B
  rightVPL1, leftVPL1: $B:81&(BVPL1$BAX(B
  rightVPL1mem, leftVPL1mem: $B0l$DA0$N;~9o$N:81&(BVPL1$BAX(B
  rightVPL2, leftVPL2: $B:81&(BVPL2$BAX(B

  beeParam: $B%7%_%e%l!<%7%g%s4XO"%Q%i%a!<%?(B
  figure: $BL\I8?^7A(B

*****************************************************************************/

compound_eye  rightEye[NUM_CE],       leftEye[NUM_CE];

VPL1cell      rightVPL1[NUM_VPL1],    leftVPL1[NUM_VPL1];
double        rightVPL1mem[VPL1_MEM][NUM_VPL1]; 
double        leftVPL1mem[VPL1_MEM][NUM_VPL1];

VPL2cell      rightVPL2[NUM_VPL2],    leftVPL2[NUM_VPL2];

parameters   beeParam;
target       figure[N_FIGURE];

/******************************************************************************

 $B4X?t%W%m%H%?%$%W$NDj5A(B

 ----------------------------------------------------------------------------

******************************************************************************/

// $BJ#4c%G!<%?$N@_Dj(B: init.c

extern void rmFiles();
extern void readConfig();
extern void initEye();
extern void initEye2();
extern void initEye3();
extern void initVPL1();
extern void initVPL2();

// $BDs<(2hA|$N@_Dj(B: figure.c

extern void initFig( int );
extern void initFigPlus( int );
extern void initFigCross( int );
extern void initFigCircle( int );
extern void initFigPGM( int, char* );
extern void fixFig( int );
extern void printFig( int );

// $B=PNO4XO"4X?t(B: output.c

extern void printEye( int );
extern void plotLeftEyeXZ( char*, int );
extern void plotRightEyeXZ( char*, int );
extern void plotBothEyeYZ( char*, int );
extern void plotBothEyeXY( char*, int );
extern void plotBothEyeXZ( char*, int );

extern void greyPlotLeftEyeXZ( char*, int );
extern void greyPlotRightEyeXZ( char*, int );
extern void greyPlotBothEyeXZ( char*, int );

extern void plotBothVPL1( char* );
extern void plotBothVPL2( char*, int );

extern void outToFile( char* );
extern void outToFileXYZ( char* );
extern void outToFileRslt( char* );
extern int  inFromFile( char* );

// $B$3$N%U%!%$%k$GDj5A$5$l$?4X?t(B

double filter( double );
double dotCheck( double, double, double, double, double );
void   proToEye( int, int, int );
void   applySigmoid( int );

double VPL1rf( int, double, double, double, int ); 
int    VPL1resp(); 

double VPL2rf( int, double, double, double ); 
int    VPL2resp(); 

/*****************************************************************************

  $BJ#4c$X$N2hA|$NEj1F(B

*****************************************************************************/

double filter( double angle ) {
  double limit, eyeAngle;
  double value;

  limit = 0.16;
  
  eyeAngle = beeParam.omDeg/2. * TO_RAD;              // $B8D4c$N;kLn3Q(B
  /*
  if ( angle < eyeAngle ) { 
    value = 1.-1./eyeAngle*angle; 
  } else value = 0.;
  */

  // $B8D4c$N;kLn$K$*$1$k8:?jFC@-$r%,%&%94X?t$G6a;w(B

  if ( angle < eyeAngle ) {
     value = exp( -beeParam.omRFcoef * angle * TO_DEG * angle * TO_DEG );
     //     printf( "value: %lf, %lf\n", angle*TO_DEG, value );
  } else value = 0;

  return value;
}

double dotCheck( double visVecTh, double visVecPh, 
                 double objTh, double objPh, double objR ) {
  double diffTh, diffPh, diffAngle;

  diffTh = fabs( visVecTh - objTh );
  diffPh = fabs( visVecPh - objPh );
  diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );

  //  printf( "diffAngle: %lf\n", diffAngle );

  return filter( diffAngle );

}


// $BJ#4c$K<L$kA|$r5a$a$k(B
//   0: right, 1: left

void proToEye(int RorL, int numOM, int figNum) {
  int    i, j, k;
  double ph, th, eyeAngle;
  double rfArea, dotArea;
  double lightResponse;
  double shiftX, shiftY, shiftZ;
  double over;
  double objX, objY, objZ, objR, objTh, objPh, s;

  double figXangle, figYangle, angleH, angleV;

  double alpha1, objTh1;

  dotArea = M_PI * figure[figNum].dotDiam * figure[figNum].dotDiam;     
                                                      // $B2hA|(B1$B%I%C%H$NLL@Q(B
  eyeAngle = beeParam.omDeg/2. * TO_RAD;              // $B8D4c$N;kLn3Q(B

  for ( k = 0; k < numOM; k++ ) {

    // $B8D4c0LCV$r86E@$K$9$k$?$a$N%7%U%HNL(B

    // X$BJ}8~$NITO"B3@-$r2r>C$9$k$?$a$K1&B&$O:BI87O$r%^%$%J%9$+$i%W%i%9$K(B
    // $BJQ49$7$F7W;;$9$k$h$&$KJQ99$7$?(B

    figXangle = figure[figNum].angleX * TO_RAD;
    figYangle = figure[figNum].angleY * TO_RAD;

    if ( !RorL ) {
      shiftX = rightEye[k].x; 
      shiftY = rightEye[k].y; 
      shiftZ = rightEye[k].z;
    } else {
      shiftX = leftEye[k].x; 
      shiftY = leftEye[k].y; 
      shiftZ = leftEye[k].z;
    }

    lightResponse = 0.;
    for (j = 0; j < figure[figNum].dotY; j++) {
      for (i = 0; i < figure[figNum].dotX; i++) {

        if (figure[figNum].pixel[i][j].br == 0) continue;

	// $B8D4c0LCV$r86E@$K@_Dj(B

        objX = figure[figNum].pixel[i][j].x - shiftX;
        objY = figure[figNum].pixel[i][j].y - shiftY;
        objZ = figure[figNum].pixel[i][j].z - shiftZ;

        // $B8D4c$+$i1GA|E@$^$G$N5wN%!"3QEY$r5a$a$k(B
        objR  = sqrt( objX*objX + objY*objY + objZ*objZ );
        objTh = atan( objX/objY );

        if ( objY < 0. && objX  > 0. ) objTh += M_PI;
        if ( objY < 0. && objX <=  0. ) objTh -= M_PI;

	s = sqrt( objX*objX + objY*objY );
        objPh = atan( objZ/s );

        // $B2hA|$N%I%C%H$,$I$NDxEY;kLn$KF~$C$F$$$k$+$r5a$a$k(B

        if ( !RorL ) {
          over = dotCheck( rightEye[k].alpha, rightEye[k].beta,
                           objTh, objPh, objR ); 
        } else {
          over = dotCheck( leftEye[k].alpha, leftEye[k].beta,
                           objTh, objPh, objR ); 
        }

         if ( over != 0. )  {
            if ( figure[figNum].pixel[i][j].br != 0.) {
 	      rfArea = M_PI * (objR * tan(eyeAngle) * objR * tan(eyeAngle));

              // $B>HEY$O5wN%$NFs>h$KH?HfNc$9$k(B 2001.11.14
              // cos$B$O(BX$B!"(BY$BJ}8~$K$D$$$F2hA|%T%/%;%k$H;k@~%Y%/%H%k$H$NJ}8~(B
              // $B$N$:$l$r9MN8$9$k$?$a$N@.J,(B

              angleH = objTh - figXangle; angleV = objPh - figYangle;
              if ( cos( M_PI/2. - angleH ) >= 0. ) {
// $BJ|<M8w$N>l9g(B
/*
    
            lightResponse += figure[figNum].pixel[i][j].br 
                  * dotArea * over/rfArea / (s*s)
	  	  * cos( M_PI/2. - angleH )
		  * cos( angleV )
                  * 1.e6;
*/

// $BH?<M8w$N>l9g(B

                lightResponse += figure[figNum].pixel[i][j].br 
                  * dotArea * over/rfArea
	  	  * cos( M_PI/2. - angleH )
		  * cos( angleV )
                  * 1.e6;

       }

	      /*
	printf( "k, i, j, objPh, objTh, shadow: %d, %d, %d, %lf, %lf, %lf\n", 
          k, i, j, objPh*TO_DEG, objTh*TO_DEG, shadow );
	      */
            }
	    /*
	printf( "k, alpha, beta, ojbPh, objTh: %d, %lf, %lf, %lf, %lf\n",
	  k,
	  rightEye[k].alpha*TO_DEG, rightEye[k].beta*TO_DEG, 
          objTh*TO_DEG, objPh*TO_DEG );
	    */
	  }
       }
    }

    if ( !RorL ) {
      rightEye[k].br +=  lightResponse;
      //if ( rightEye[k].br != 0. )
      //  printf( "right(%d): %lf\n", k, rightEye[k].br );
    } else {
      leftEye[k].br +=  lightResponse;
      //if ( leftEye[k].br != 0. ) 
      //  printf( "left(%d): %lf\n", k, leftEye[k].br );
    }

  }

}

void applySigmoid( int numOM ) {
  int  i;

  for ( i = 0; i < numOM; i++ ) {
    if ( leftEye[i].br <= 50. && leftEye[i].br >= -50. ) {  
      leftEye[i].br =  2.*(1./(1.+exp( beeParam.sigCoef * leftEye[i].br )) 
                    - 0.5);
    } else if ( leftEye[i].br > 50. ) {
      leftEye[i].br = 1.;
    } else {
      leftEye[i].br = -1.;
    }

    if ( rightEye[i].br <= 50. && rightEye[i].br >= -50. ) {  
      rightEye[i].br =  2.*(1./(1.+exp( beeParam.sigCoef * rightEye[i].br )) 
                     - 0.5);
    } else if ( rightEye[i].br > 50. ) {
      rightEye[i].br = 1.;
    } else {
      rightEye[i].br = -1.;
    }
  }
}

void applySigmoid2( int numOM ) {
  int  i;

  for ( i = 0; i < numOM; i++ ) {
    leftEye[i].br =  2./(1.+exp( beeParam.sigCoef * leftEye[i].br )) - 1.;
    rightEye[i].br = 2./(1.+exp( beeParam.sigCoef * rightEye[i].br )) - 1.;
  }
}

/*****************************************************************************

 $B2hA|>pJs=hM}AX(B(VPL1)$B:YK&$N1~Ez$r5a$a$k(B

 -----------------------------------------------------------------------------
 2002.01.31: $BLVKlAX$+$i$NF~NO$r<u$1!"J#?t$N8D4c$N1~Ez$NJ?6Q$r5a$a$k(B

 [VPL1$B:YK&$NFC@-(B: RFtype$B$G@_Dj(B]
   $B#1!'(B $B0lDj$N(B

 *****************************************************************************/

// $B$3$N4X?t$O;H$C$F$$$J$$(B 2003/4/11

double VPL1rf( int rfType, double rfCoef, double th, double ph, 
               int left_right ) 
{
  double angle2, resp;

  resp = 0.;
  angle2 = th*th + ph*ph;
  switch ( rfType ) {
    case 0: {
        resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        break;
    }
    case 1: {
	if ( ((th > 0) && (left_right == 0)) || 
             ((th < 0) && (left_right == 1)) ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        }
        break;
    }
    case 2: {
	if ( ((th < 0) && (left_right == 0)) || 
             ((th > 0) && (left_right == 1)) ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
	}
        break;
    }
    case 3: {
	if ( ph > 0 ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        }
        break;
    }
    case 4: {
	if ( ph < 0 ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        }
        break;
    }
  }

  return resp;

}

int VPL1resp() {
  int     i, j, k, rfType;
  double  diffTh, diffPh, diffAngle;
  double  resp, rfCoef;

  printf( "start calc of Visual-information Processing Layer 1 response\n" );

  // $B:8B&(B

  for ( i = 0; i < beeParam.numOfVPL1; i++ ) { 
    rfType = leftVPL1[i].RFtype;
    rfCoef = leftVPL1[i].RFcoef;

    resp = 0.;
    for ( j = 0; j < leftVPL1[i].conNumOfOM; j++ ) {
      k = leftVPL1[i].connectOM[j];
//      diffTh = leftEye[k].alpha - leftVPL1[i].alpha; 
//      diffPh = leftEye[k].beta - leftVPL1[i].beta;
//      resp += VPL1rf( rfType, rfCoef, diffTh, diffPh, 0 ) * leftEye[k].br; 
      resp += leftEye[k].br; 
    }
    leftVPL1[i].resp = resp/leftVPL1[i].conNumOfOM;
    //    leftVPL1[i].resp = resp;

    if ( leftVPL1[i].resp != 0. ) {
      printf( "leftVPL1[%d]: %lf\n", i, leftVPL1[i].resp );
    }

  }

  // $B1&B&(B

  for ( i = 0; i < beeParam.numOfVPL1; i++ ) { 
    rfType = rightVPL1[i].RFtype;
    rfCoef = rightVPL1[i].RFcoef;

    resp = 0.;
    for ( j = 0; j < rightVPL1[i].conNumOfOM; j++ ) {
      k = rightVPL1[i].connectOM[j];
//      diffTh = rightEye[k].alpha - rightVPL1[i].alpha;
//      diffPh = rightEye[k].beta - rightVPL1[i].beta;
//      resp += VPL1rf( rfType, rfCoef, diffTh, diffPh, 1 ) * rightEye[k].br; 
      resp += rightEye[k].br; 
    }
    rightVPL1[i].resp = resp/rightVPL1[i].conNumOfOM;
    //    rightVPL1[i].resp = resp;

    if ( rightVPL1[i].resp != 0. ) {
      printf( "rightVPL1[%d]: %lf\n", i, rightVPL1[i].resp );
    }

  }

  return 0;

}

/*****************************************************************************

 $B2hA|>pJs=hM}AX(B(VPL2)$B:YK&$N1~Ez$r5a$a$k(B

 -----------------------------------------------------------------------------

 2002.01.31: VPL1$B:YK&$+$i$NF~NO$r<u$1%*%W%F%#%+%k%U%m!<$r7W;;$9$k(B
 type 0: $BC1=c$K9g7W(B
 type 1: $B?eJ?J}8~$NF0$-(B
 type 2: $B1tD>J}8~$NF0$-(B

 *****************************************************************************/

int VPL2resp() {
  int     i, j, k, rfType, rfTypeVPL1;
  int     count, countP;
  double  diffTh, diffPh, diffAngle;
  double  resp, respP;

  double  resp1[VPL1_RF_NUM], resp1P[VPL1_RF_NUM];
  int     count1[VPL1_RF_NUM], count1P[VPL1_RF_NUM];

  // $B:8B&(B

  for ( i = 0; i < beeParam.numOfVPL2; i++ ) { 
    rfType = leftVPL2[i].RFtype;
    for ( j = 0; j < VPL1_RF_NUM; j++ ) {
      resp1[j] = resp1P[j] = 0.;
      count1[j] = count1P[j] = 0;
    }

    resp = respP = 0.;
    count = countP = 0;
    for ( j = 0; j < leftVPL2[i].conNumOfVPL1; j++ ) {
      k = leftVPL2[i].connectVPL1[j];
      rfTypeVPL1 = leftVPL1[k].RFtype;
      diffTh = leftVPL1[k].alpha - leftVPL2[i].alpha;
      diffPh = leftVPL1[k].beta - leftVPL2[i].beta;

      if ( rfTypeVPL1 == 0 ) { 
        resp1[0] += leftVPL1[k].resp; count1[0]++;
      }

      if ( diffTh >= 0 ) { 
        resp1[1]  += fabs(leftVPL1[k].resp); count1[1]++;
        resp1P[1] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[1]++;
      }
      if ( diffTh < 0 ) { 
        resp1[2]  += fabs(leftVPL1[k].resp); count1[2]++;
        resp1P[2] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[2]++;
      }
      if ( diffPh >= 0 ) { 
        resp1[3]  += fabs(leftVPL1[k].resp); count1[3]++;
        resp1P[3] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[3]++;
      }
      if ( diffPh < 0 ) { 
        resp1[4]  += fabs(leftVPL1[k].resp); count1[4]++;
        resp1P[4] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[4]++;
      }

    }

    if ( rfType == 0 ) {
      if ( count1[0] != 0 ) 
        leftVPL2[i].resp = resp1[0];
    }
    if ( rfType == 1 ) {
      leftVPL2[i].resp =  resp1[1] * resp1P[2] - resp1[2] * resp1P[1];
    }
    if ( rfType == 2 ) {
      leftVPL2[i].resp =  resp1[3] * resp1P[4] - resp1[4] * resp1P[3];
    }

    if ( leftVPL2[i].resp != 0. && rfType != 0 ) {
            printf( "leftVPL2[%d](%d): %lf\n", i, rfType, leftVPL2[i].resp );
    }

  }

  // $B1&B&(B

  for ( i = 0; i < beeParam.numOfVPL2; i++ ) { 
    rfType = rightVPL2[i].RFtype;
    for ( j = 0; j < VPL1_RF_NUM; j++ ) {
      resp1[j] = resp1P[j] = 0.;
      count1[j] = count1P[j] = 0;
    }

    resp = respP = 0.;
    count = countP = 0;
    for ( j = 0; j < rightVPL2[i].conNumOfVPL1; j++ ) {
      k = rightVPL2[i].connectVPL1[j];
      rfTypeVPL1 = rightVPL1[k].RFtype;
      diffTh = rightVPL1[k].alpha - rightVPL2[i].alpha;
      diffPh = rightVPL1[k].beta - rightVPL2[i].beta;

      if ( rfTypeVPL1 == 0 ) { 
        resp1[0] += rightVPL1[k].resp; count1[0]++;
      }

      // $BCm0U!*!*(B diffTh$B$K$D$$$F:81&$GId9f$rH?E>$5$;$k(B

      if ( diffTh <= 0 ) { 
        resp1[1]  += fabs(rightVPL1[k].resp); count1[1]++;
        resp1P[1] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[1]++;
      }
      if ( diffTh > 0 ) { 
        resp1[2]  += fabs(rightVPL1[k].resp); count1[2]++;
        resp1P[2] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[2]++;
      }
      if ( diffPh >= 0 ) { 
        resp1[3]  += fabs(rightVPL1[k].resp); count1[3]++;
        resp1P[3] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[3]++;
      }
      if ( diffPh < 0 ) { 
        resp1[4]  += fabs(rightVPL1[k].resp); count1[4]++;
        resp1P[4] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[4]++;
      }

    }


    if ( rfType == 0 ) {
      if ( count1[0] != 0 ) 
        rightVPL2[i].resp = resp1[0];
    }
    if ( rfType == 1 ) {
      rightVPL2[i].resp = resp1[1] * resp1P[2] - resp1[2] * resp1P[1];
    }
    if ( rfType == 2 ) {
      rightVPL2[i].resp = resp1[3] * resp1P[4] - resp1[4] * resp1P[3];
    }

    if ( rightVPL2[i].resp != 0. && rfType != 0 ) {
            printf( "rightVPL2[%d](%d): %lf\n", i, rfType, rightVPL2[i].resp );
    }

  }

  return 0;

}

/*****************************************************************************

 $B$3$l$^$G$N1~Ez$rJ]B8!"FI$_9~$`$?$a$N4X?t$rDI2C$7$?(B

 *****************************************************************************/

int loadVPLresp( int time ) {
  int    t, i, j ;
  double leftVPL1resp[NUM_VPL1], rightVPL1resp[NUM_VPL1];
  char   filename[256];
  FILE   *fp;
  size_t cnt;

  for ( i = 0, t = time-1; i < VPL1_MEM; i++, t-- ) {
    if ( t >= 0 ) { 
      sprintf( filename, "./Responses/%d", t );

      fp = fopen( filename, "r" );
      cnt = fread( leftVPL1resp, sizeof leftVPL1resp, 1, fp );
      cnt = fread( rightVPL1resp, sizeof rightVPL1resp, 1, fp );
      fclose( fp );
    }

    for ( j = 0; j < NUM_VPL1; j++ ) {
      if ( t >= 0 ) { 
        leftVPL1mem[i][j] = leftVPL1resp[j];      
        rightVPL1mem[i][j] = rightVPL1resp[j];
      } else {
        leftVPL1mem[i][j] = 0.;
        rightVPL1mem[i][j] = 0.;
      }      
    }
  }

  return 0;
}

int saveVPLresp( int time ) {
  int    t, i, j;
  char   filename[256];
  double leftVPL1resp[NUM_VPL1], rightVPL1resp[NUM_VPL1];
  FILE   *fp;
  size_t cnt;

  for ( j = 0; j < NUM_VPL1; j++ ) {
    leftVPL1resp[j] = leftVPL1[j].resp;      
    rightVPL1resp[j] = rightVPL1[j].resp;      
  }

  sprintf( filename, "./Responses/%d", time );
  fp = fopen( filename, "w" );
  cnt = fwrite( leftVPL1resp, sizeof leftVPL1resp, 1, fp );
  cnt = fwrite( rightVPL1resp, sizeof rightVPL1resp, 1, fp );
  fclose( fp );

  return 0;
}

// $BJ#4c!"?@7P:YK&>pJs$NJ]B8!"FI$_9~$_(B

int loadCellInfo() {
  FILE *fp;
  size_t cnt;

  fp = fopen( "./Results/cellInfo.bin", "r" );

  cnt = fread( leftEye, sizeof(compound_eye), NUM_CE, fp );
  cnt = fread( rightEye, sizeof(compound_eye), NUM_CE, fp );

  cnt = fread( leftVPL1, sizeof(VPL1cell), NUM_VPL1, fp );
  cnt = fread( rightVPL1, sizeof(VPL1cell), NUM_VPL1, fp );

  cnt = fread( leftVPL2, sizeof(VPL2cell), NUM_VPL2, fp );
  cnt = fread( rightVPL2, sizeof(VPL2cell), NUM_VPL2, fp );

  cnt = fread( &beeParam, sizeof(parameters), 1, fp );
  
  fclose( fp );

  return 0;
}

int saveCellInfo() {
  char filename[256];
  FILE *fp;
  size_t cnt;

  fp = fopen( "./Results/cellInfo.bin", "w" );

  cnt = fwrite( leftEye, sizeof(compound_eye), NUM_CE, fp );
  cnt = fwrite( rightEye, sizeof(compound_eye), NUM_CE, fp );

  cnt = fwrite( leftVPL1, sizeof(VPL1cell), NUM_VPL1, fp );
  cnt = fwrite( rightVPL1, sizeof(VPL1cell), NUM_VPL1, fp );

  cnt = fwrite( leftVPL2, sizeof(VPL2cell), NUM_VPL2, fp );
  cnt = fwrite( rightVPL2, sizeof(VPL2cell), NUM_VPL2, fp );

  cnt = fwrite( &beeParam, sizeof(parameters), 1, fp );
  
  fclose( fp );

  return 0;
}

/*****************************************************************************

   $B$3$3$+$i$,%a%$%s%W%m%0%i%`(B
 ---------------------------------------------------------------------------
   $B%3%^%s%I%*%W%7%g%s(B: 
   argv[1]
     -v: version $BI=<((B
     -n: $BHV9fIU$-$N%P%C%A=hM}(B
   argv[2]
     $B%7%_%e%l!<%7%g%sHV9f(B
   argv[3]
     TIFF$B%U%!%$%k=PNO$NM-L5!J(B-plot for plotting)
 ****************************************************************************/

int main(int argc, char *argv[]) {
    int   i, numOM, numFig, time;
    char  disDev[8];

    // print version number

    if ( !strcmp(argv[1], "-v") ) {
      printf( VERSION ); printf( "\n" );
      return 0;
    }

    // simulation$B$N<B9T(B

    if ( !strcmp(argv[1], "-n") ) {
      rmFiles();
      readConfig();

      // $BJ]B8$7$F$$$?(BVPL$B1~Ez$r%m!<%I$9$k(B

      time = atoi( argv[2] );
      loadVPLresp( time );
    } else return 0;

      // $B8D4c$NG[CV(B

    if ( !strcmp( argv[1], "-n") && time != 0 ) {
      printf( "---------> load cell information\n" );
      loadCellInfo();
    } else {
//      initEye();   // $B$3$l$r;HMQ$9$k$H$-$O(BbeeVision.conf.base.1$B$r;HMQ(B
//      initEye2();  // $B$3$l$r;HMQ$9$k$H$-$O(BbeeVision.conf.base.2$B$r;HMQ(B
      initEye3();    // $B$3$l$r;HMQ$9$k$H$-$O(BbeeVision.conf.base.3$B$r;HMQ(B
      printf( "---------> END: initialize Eye\n" );
      //      initVPL1();
      //      printf( "---------> END: initialize VPL1\n" );
      //      initVPL2();
      //      printf( "---------> END: initialize VPL2\n" );
      saveCellInfo();
      printf( "---------> END: save cell infromation\n" );
    }

    outToFileXYZ( "./Results/" );
    printf( "---------> END: save ./Results/xyz*.asc\n" );

      // $BL\I8%Q%?!<%s$N@_Dj(B

    printf( "---------> start initialization of Targets\n" );

    printf( "numOfFig: %d\n", beeParam.numOfFig );
    for ( numFig = 0; numFig < beeParam.numOfFig; numFig++ ) {
       switch ( figure[numFig].pattern ) {
   	 case -1: { initFigPGM( numFig, figure[numFig].fileName ); break; }
   	 case  0: { initFigPlus( numFig ); break; }
  	 case  1: { initFigCross( numFig ); break; }
  	 case  2: { initFigCircle( numFig ); break; }
       }
       fixFig( numFig );
	//        printFig( numFig );
    }

    printf( "---------> end initialization of Targets\n" );

    // $BJ#4c$X$NEj1F(B
          
    printf( "---------> start calculation projection image on Eye\n" );

    for ( numFig = 0; numFig < beeParam.numOfFig; numFig++ ) {
      if ( figure[numFig].show ) {
         proToEye( 0, beeParam.numOfOM, numFig );       // $B1&L\$X$NEj1F(B
	 proToEye( 1, beeParam.numOfOM, numFig );       // $B:8L\$X$NEj1F(B
      }
    }
    applySigmoid2( beeParam.numOfOM );

    printf( "---------> end calculation projection image on Eye\n" );

    // $B2hA|=hM}AX$N7W;;(B

    //    printEye();

    //    printf( "---------> start calculation VPL1 response\n" );
    //    VPL1resp();
    //    printf( "---------> end calculation VPL1 response\n" );

    //    printf( "---------> start calculation VPL2 response\n" );
    //    VPL2resp();
    //    printf( "---------> end calculation VPL2 response\n" );

    // $B7W;;7k2L$N=PNO(B

    printf( "---------> start output results to ./Results\n" );
    outToFile( "./Results" );
    printf( "---------> end output results to ./Results\n" );

    // $B%7%_%e%l!<%7%g%s7k2L$N:n@.(B

    if ( !strcmp(argv[3], "-plot") ) {
      strcpy( disDev, "tiff" );

      plotLeftEyeXZ( disDev, beeParam.numOfOM );
         printf( "---------> plot left eye XY\n" );
      plotRightEyeXZ( disDev, beeParam.numOfOM );
      plotBothEyeYZ( disDev, beeParam.numOfOM );
      plotBothEyeXY( disDev, beeParam.numOfOM );
      plotBothEyeXZ( disDev, beeParam.numOfOM );

      greyPlotBothEyeXZ( disDev, beeParam.numOfOM );
      greyPlotLeftEyeXZ( disDev, beeParam.numOfOM );
      greyPlotRightEyeXZ( disDev, beeParam.numOfOM );

      //      plotBothVPL1( disDev );

      //      plotBothVPL2( disDev, 0 );
      //      plotBothVPL2( disDev, 1 );
      //      plotBothVPL2( disDev, 2 );
      //      plotBothVPL2( disDev, 3 );
      //      plotBothVPL2( disDev, 4 );
    }
    saveVPLresp( time );

    return 0;
}
