/* $VisiomeSS-Revision: 1.1.1.1 $ $VisiomeSS-Date: 2002/07/18 08:15:03 $
   File:
     ICa.mdl
   Title:
     Ionic Current Model of Fish Retinal Horizontal Cell
   Author:
     KAMIYAMA Yoshimi (kamiyama@ist.aichi-pu.ac.jp)
     AOYAMA Toshihiro (aoyama@brain.riken.go.jp)
   Reference Paper:
     Aoyama, T., Kamiyama, Y. and Usui. S. (2002)
     Simulation analysis of current-voltage relationship 
     of retinal horizontal cells
     The Transactions of the Institute of Electronics, Information
     and Communication Engineers, Vol.J85-D-II, 918-930
*/

type:           NETWORK;
module:         fishHC;
cell:           HC[1];
connection:
                HC[0] < ();
end;

/* horizontal cell model */
type:           CELL;
module:         HC;
exinput:        V;
output:         I;
observable:
        mCa,Ca,ICa,hCa;
parameter:
/* ---- ICa parameters ---- */
        mCa0 = @@@NUMBER:0.@@@,
        K_Ca = @@@NUMBER:0.5@@@,
        n_hCa = @@@NUMBER:1.@@@,
        gCa_bar = @@@NUMBER:0.2@@@,

/* ---- Calcium pump parameters ---- */
        Ipump_bar=@@@NUMBER:5.@@@, Hil_pump = @@@NUMBER:0.1@@@, Ca_e=@@@NUMBER:0.05@@@,

/* ---- Na-Ca exchanger parameters ---- */
        Iex_bar=@@@NUMBER:5.@@@, Hil_ex = @@@NUMBER:3.@@@,

/* ---- cell parameter ---- */
        Cm = @@@NUMBER:0.0125@@@, V0 = @@@NUMBER:-60.@@@, r=@@@NUMBER:25.@@@, dr=@@@NUMBER:2.5@@@,

/* ---- Calcium System parameters ---- */
        DCa=@@@NUMBER:600.@@@,
        Ca_init=@@@NUMBER:0.0488@@@,
        Ca_o=@@@NUMBER:2500.@@@,

/* ---- Calcium buffer parameters ---- */
        FB0_t=@@@NUMBER:10.@@@, bFB0=@@@NUMBER:12@@@, fFB0=@@@NUMBER:4.@@@,
        FB1_t=@@@NUMBER:20.@@@, bFB1=@@@NUMBER:100.@@@, fFB1=@@@NUMBER:100.@@@,
/*      EGTA_t=10000., */
        EGTA_t=@@@NUMBER:0.@@@, 
        BAPTA_t=@@@NUMBER:0.@@@,

/* ---- Calcium store parameters ---- */
        ns=@@@NUMBER:3.@@@, Kb=@@@NUMBER:1.0@@@, Kf=@@@NUMBER:0.1@@@, fSB=@@@NUMBER:0.5@@@, bSB=@@@NUMBER:0.7@@@,
        SB_t=@@@NUMBER:20.@@@, SB_init=@@@NUMBER:2.83@@@,

/* ---- physiological parameters ---- */
        F=@@@NUMBER:9.648e+4@@@, R=@@@NUMBER:8.31@@@, T=@@@NUMBER:293.@@@;
function:
/* ---- ICa (Voltage-dependent calcium current) ---- */
if(V!=40.){
        amCa = 10.*( 40.- V)/(exp((40.- V)/20.)-1.);
}else{
        amCa = 10.*20.;
}
        bmCa = 13.2*exp(-V/15.);
        dmCa = amCa * ( 1. - mCa ) - bmCa * mCa;
        mCa = integral( mCa0 ,dmCa );
        hCa = pow(K_Ca,n_hCa)/(pow(K_Ca,n_hCa)+pow(Ca,n_hCa));

        eps = 2.*V*F/(R*T)*1.e-3;
if (V!=0){
        ICa = gCa_bar*pow(mCa,2.)*pow(hCa,2.)*
                2.*F*eps*1.e-6*(Ca-Ca_o*exp(-eps))/(1.-exp(-eps));
}else{
        ICa = gCa_bar*pow(mCa,2.)*pow(hCa,2.)*
                (2.*F*1.e-6*(Ca-Ca_o*exp(-eps)*(1.-eps)))/exp(-eps);
}

/* ---- Na-Ca exchanger ---- */
        Iex = Iex_bar*exp(-(V+14.)/70.)*Ca/(Ca+Hil_ex);

/* ---- Calcium pump ---- */
        Ipump = Ipump_bar * (Ca-Ca_e)/(Ca + Hil_pump );

/* --- intracellular calcium system --- */
        V_s=4*PI*pow(r,3)/3.;

        influx=(-ICa)/(2.*F*V_s)*1.e9;
        efflux=-(Iex + Ipump)/(2*F*V_s)*1.e9;

        KFB0 = fFB0/bFB0;
        kappaFB0 = (KFB0*FB0_t)/pow(1.+Ca*KFB0,2);
        KFB1 = fFB1/bFB1;
        kappaFB1 = (KFB1*FB1_t)/pow(1.+Ca*KFB1,2);

        KEGTA = 1./(0.18e3);
        kappaEGTA = (KEGTA*EGTA_t)/pow(1.+Ca*KEGTA,2);
        KBAPTA = 1./(0.22e3);
        kappaBAPTA = (KBAPTA*BAPTA_t)/pow(1.+Ca*KBAPTA,2);

        dSB= pow(Ca,ns)/(pow(Ca,ns)+pow(Kb,ns))*bSB*(SB_t-SB)
        -(pow(Ca,ns)/(pow(Ca,ns)+pow(Kf,ns)))*fSB*Ca*SB;
        SB = integral(SB_init,dSB);

        dCa = (dSB + influx + efflux)/(1+kappaFB0+kappaFB1+kappaEGTA+kappaBAPTA);
        Ca = integral(Ca_init,dCa);

        I = ICa;
end;
