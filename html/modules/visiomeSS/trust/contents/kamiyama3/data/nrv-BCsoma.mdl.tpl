/* $VisiomeSS-Revision: 1.3 $ $VisiomeSS-Date: 2003/10/24 07:25:17 $
   File: 
     nrv-BCsoma.mdl
   Title:
     Retinal Bipolar Cell Model 
   Author:
     Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
     Akito   Ishihara (ishihara@bpel.ics.tut.ac.jp)
   Reference Paper:
     Usui, S., Ishihara, A., Kamiyama, Y. and Ishii, H. (1996),
     Ionic current model of bipolar cells in lower vertebrate
     retina, Vision Research, Vol.36, No.24, pp.4096-4076
*/

      type:     NETWORK;
    module:     BC_VC;
      cell:     BC[1];
connection:
                BC[0] < ();
                end;

      type:     CELL;
    module:     BC;
   exinput:     v;
    output:     i_all;
observable:
                mKv, hKv, iKv,
                C1, C2, OP1, OP2, OP3, ih,
                mKca, iKca,
                mCa, iCa,
                Ca_s, Ca_d, bCa_ls, bCa_hs, bCa_ld, bCa_hd,
                iNC, iATP,
                iA, mA, hA,
                il;
  constant:
                /***********   ICa parameter  ***********/
                /*        Chemical parameter         */
                F=@@@NUMBER:9.649E4@@@/*[c/mol]*/;
  parameter:
                Dca=@@@NUMBER:6.0E-8@@@,/*[cm^2/s]*/
                /***********   IKv parameter ************/
                gKv = @@@NUMBER:2.0@@@,
                mKv0 = @@@NUMBER:0.89860713481903076@@@,
                hKv0 = @@@NUMBER:0.06862986832857132@@@,
                Ek = @@@NUMBER:-58.@@@,
                /***********  Ih parameter  *************/
                C10 = @@@NUMBER:0.94730311632156372@@@,
                C20 = @@@NUMBER:0.036538422107696533@@@,
                OP10 = @@@NUMBER:0.00052849622443318367@@@,
                OP20 = @@@NUMBER:0.00000339743769472989@@@,
                OP30 = @@@NUMBER:0.00000000819015966158@@@,
                gh = @@@NUMBER:0.975@@@, Eh = @@@NUMBER:-17.7@@@,
                /***********   ICa parameter  ***********/
                /*      Morphologycal parameter        */
                /*  Soma : diameter 12 micron          */
                PIP = @@@NUMBER:3.14159@@@,
                radius = @@@NUMBER:6.0@@@, radius_d = @@@NUMBER:5.6@@@ /* [um] */,
                Vd = @@@NUMBER:4@@@/@@@NUMBER:3@@@*PIP*(radius_d*radius_d*radius_d)*@@@NUMBER:1e-15@@@ /* [l] */,
                Vs = @@@NUMBER:4@@@/@@@NUMBER:3@@@*PIP*(radius*radius*radius)*@@@NUMBER:1e-15@@@-Vd /* [l] */,
                Ssd = @@@NUMBER:4@@@*PIP*radius_d*radius_d*@@@NUMBER:1e-10@@@ /*[dm^2]*/,
                dsd = ((radius-radius_d)/@@@NUMBER:2@@@ + radius_d)*@@@NUMBER:1e-5@@@ /*[dm]*/,
                /*        Chemical parameter         */
                Ca_o = @@@NUMBER:2500.@@@,
                /*      Ca current parameter         */
                gCa = @@@NUMBER:1.1@@@,
                /*      Ca buffer parameter          */
                LB_to1 = @@@NUMBER:300.@@@, HB_to1 = @@@NUMBER:100.@@@, /*[uM]*/
                LB_to2 = @@@NUMBER:500.@@@, HB_to2 = @@@NUMBER:300.@@@, /*[uM]*/
                Lb1 = @@@NUMBER:0.4@@@, Lb2 = @@@NUMBER:0.2@@@,
                Hb1 = @@@NUMBER:100.@@@, Hb2 = @@@NUMBER:90.@@@,/*[1/s/uM]*/
                /*   Ca exchanger & pump parameter   */
                Jnc = @@@NUMBER:9.@@@*@@@NUMBER:40@@@, Jatp = @@@NUMBER:9.5@@@*@@@NUMBER:40@@@, /*[pA]*/
                Ca_e = @@@NUMBER:0.01@@@, /*[uM]*/
                /*      integral initial value       */
                mCa0 = @@@NUMBER:0.38389194011688232@@@,
                Ca_s0 = @@@NUMBER:0.014662666246294975@@@,
                Ca_d0 = @@@NUMBER:0.014662666246294975@@@,
                bCa_ls0 = @@@NUMBER:8.5469579696655273@@@,
                bCa_hs0 = @@@NUMBER:1.6030682325363159@@@,
                bCa_ld0 = @@@NUMBER:14.244929313659668@@@,
                bCa_hd0 = @@@NUMBER:4.80920457839965820@@@,
                /***********   IKca parameter  ***********/
                mKca0 = @@@NUMBER:0.51732587814331055@@@,
                gKca = @@@NUMBER:8.5@@@,
                /***********   IA parameter  ***********/
                mA0 = @@@NUMBER:0.35099479556083679@@@,
                hA0 = @@@NUMBER:0.011917699128389359@@@,
                gA = @@@NUMBER:50.@@@,
                /******** leakage current parameter *******/
                gl = @@@NUMBER:0.23@@@, El = @@@NUMBER:-21.0@@@;
  function:
                /**************     IK(V)     ******************/
                /*amKv = 280 / ( exp( -(v-35)/36 ) + 1. );*/
                amKv = 400 / ( exp( -(v-15)/36 ) + 1. );
                /*bmKv = 0.7 * exp( -v / 13 );*/
                bmKv = 1.0 * exp( -v / 13 );
                d_mKv = amKv * ( 1. - mKv ) - bmKv * mKv;
                mKv = integral( mKv0, d_mKv );

                ahKv = 0.0003 * exp( -v / 7 );
                bhKv = 80 / ( exp( -(-115-v)/15 ) + 1.0 ) + 0.02;
                d_hKv = ahKv * ( 1. - hKv ) - bhKv * hKv;
                hKv = integral( hKv0, d_hKv );

                iKv = gKv * mKv * mKv * mKv * hKv*( v - Ek );

                /***************     Ih      *****************/
                ah = 3 / ( exp( (v+110)/15 ) + 1. );
                bh = 1.5 / ( exp( -(v+115)/15 ) + 1. );
                dC1 = bh*C2 - 4.*ah*C1;
                C1 = integral( C10, dC1 );
                dC2 = C1*4.*ah + OP1*2.*bh - C2*bh - C2*3.*ah;
                C2 = integral( C20, dC2 );
                dOP1 = C2*3.*ah + OP2*3.*bh - OP1*2.*(bh+ah);
                OP1 = integral( OP10, dOP1 );
                dOP2 = OP1*2.*ah + OP3*4.*bh - OP2*(3.*bh + ah);
                OP2 = integral( OP20, dOP2 );
                dOP3 = ah*OP2 - 4*bh*OP3;
                OP3 = integral( OP30, dOP3 );
                mh = OP1 + OP2 + OP3;
                ih = mh * gh * ( v - Eh );

                /***************     ICa   *******************/
                amCa = 12000*( 120 - v ) / ( exp( (120-v)/25 ) - 1. );
                bmCa = 40000 / ( 1.0 + exp( (68+v)/25 ) );
                d_mCa = amCa * ( 1. - mCa ) - bmCa * mCa;
                mCa = integral( mCa0 ,d_mCa );
                mCa_4 = pow( mCa, 4.0 );

                dCa_s = -(iCa+iNC+iATP)/(2.*F*Vs)*1.0E-6
                        - Dca*Ssd/Vs/dsd*( Ca_s - Ca_d ) 
                        + Lb2*bCa_ls - Lb1*Ca_s*(LB_to1 - bCa_ls)
                        + Hb2*bCa_hs - Hb1*Ca_s*(HB_to1 - bCa_hs);
                Ca_s = integral( Ca_s0 , dCa_s );

                dbCa_ls = Lb1*Ca_s*(LB_to1 - bCa_ls) - Lb2*bCa_ls;
                bCa_ls = integral( bCa_ls0, dbCa_ls );
                dbCa_hs = Hb1*Ca_s*(HB_to1 - bCa_hs) - Hb2*bCa_hs;
                bCa_hs = integral( bCa_hs0, dbCa_hs );

                dCa_d = Dca*Ssd/Vd/dsd*( Ca_s - Ca_d )
                        + Lb2*bCa_ld - Lb1*Ca_d*(LB_to2 - bCa_ld)
                        + Hb2*bCa_hd - Hb1*Ca_d*(HB_to2 - bCa_hd);
                Ca_d = integral( Ca_d0, dCa_d );

                dbCa_ld = Lb1*Ca_d*(LB_to2 - bCa_ld) - Lb2*bCa_ld;
                bCa_ld = integral( bCa_ld0, dbCa_ld );
                dbCa_hd = Hb1*Ca_d*(HB_to2 - bCa_hd) - Hb2*bCa_hd;
                bCa_hd = integral( bCa_hd0, dbCa_hd );

                iNC = Jnc*exp(-(v+14.)/70.)
                        *( Ca_s - Ca_e )/( Ca_s - Ca_e + 2.3 );
                iATP = Jatp*( Ca_s - Ca_e )/( Ca_s - Ca_e + 0.5 );

                hCa = exp( (50-v)/11 )/( 1.0 + exp( (50-v)/11) );

                ECa = 12.9*log(Ca_o/Ca_s);

                iCa = gCa*mCa_4*hCa*(v-ECa);


                /****************   IKca  ***********************/
                mKca_c1 = Ca_s / ( Ca_s + 0.2 );
                amKca = 100 * ( 230 - v )/( exp( (230-v)/52 ) - 1. );
                bmKca = 120 * exp( -v / 95 );
                d_mKca = amKca * ( 1. - mKca ) - bmKca * mKca;
                mKca = integral( mKca0, d_mKca );
                iKca = gKca * mKca_c1*mKca*mKca*(v - Ek);

                /****************     IA    ********************/
                amA = 2400 / ( 1.0 + exp( -(v-50.)/28. ) );
                bmA = 12 * exp( -v/10. );
                d_mA = amA * ( 1. - mA ) - bmA * mA;
                mA = integral( mA0, d_mA );

                ahA = 0.045 * exp( -v / 13 );
                bhA = 75 / ( exp( -(30+v)/15 ) + 1.0 );
                d_hA = ahA * ( 1.0 - hA ) - bhA * hA;
                hA = integral( hA0, d_hA );

                iA = gA * pow( mA, 3.0 ) * hA * ( v - Ek );

                /****************     Il    ********************/
                il = gl * ( v - El );

                /************** whole cell current *************/
                i_all = iKca + iCa + ih + iKv + il + iA;

                end;
