/* $VisiomeSS-Revision: 1.1.1.1 $ $VisiomeSS-Date: 2002/07/18 08:15:03 $
   File:
     fishHC.mdl
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
exinput:        Glu;
output:         V;
observable:
        mKv,mA,hA,mCa,Ca,mNa,hNa,
        IA,IKa,ICa,IKv,INa,V,Iall,Il,SB,Glu,El,Iglu;
parameter:
        Ko = @@@NUMBER:2.6@@@,
/*      Ko = 10.,*/
        Ki = @@@NUMBER:118@@@,

/* ---- IA parameters ---- */
        gA_bar=@@@NUMBER:2.2@@@, 
        mA0 = @@@NUMBER:0.016276876@@@, 
        hA0 = @@@NUMBER:0.81380528@@@, 

/* ---- IKa parameters ---- */
        gKa_bar = @@@NUMBER:24.@@@,

/* ---- IKv parameters ---- */
        gKv_bar = @@@NUMBER:0.4@@@,
        mKv0 = @@@NUMBER:0.069557428@@@, 

/* ---- ICa parameters ---- */
        gCa_bar = @@@NUMBER:0.2@@@,
        mCa0 = @@@NUMBER:0.@@@, 
        K_Ca = @@@NUMBER:0.5@@@, 
        n_hCa = @@@NUMBER:1.0@@@,

/* ---- INa parameters ---- */
        gNa_bar = @@@NUMBER:200.@@@,
        mNa0 = @@@NUMBER:0.0@@@,
        hNa0 = @@@NUMBER:1.@@@,
        Na_o = @@@NUMBER:125.@@@, 
        Na_i = @@@NUMBER:5.@@@,

/* ---- Il parameters ---- */
        gl = @@@NUMBER:0.2@@@,
        El = @@@NUMBER:-70.@@@,

/* ---- Iglu parameters ---- */ 
        Iglu_bar = @@@NUMBER:800.@@@, 
        K_Iglu = @@@NUMBER:0.02@@@,
        Hill_Iglu = @@@NUMBER:3.@@@,

/* ---- Calcium pump parameters ---- */
        Ipump_bar = @@@NUMBER:5.@@@, 
        Hil_pump = @@@NUMBER:0.1@@@, 
        Ca_e = @@@NUMBER:0.05@@@,

/* ---- Na-Ca exchanger parameters ---- */
        Iex_bar = @@@NUMBER:5.@@@, 
        Hil_ex = @@@NUMBER:3.@@@,

/* ---- cell parameters ---- */
        Cm = @@@NUMBER:0.0125@@@, 
        V0 = @@@NUMBER:-60.@@@, 
        r=@@@NUMBER:25.@@@,

/* ---- Calcium System paremeters ---- */
        DCa = @@@NUMBER:600.@@@, 
        Ca_init = @@@NUMBER:0.04563446@@@, 
        Ca_o = @@@NUMBER:2500.@@@, 

/* ---- Calcium buffer parameters ---- */
        FB0_t = @@@NUMBER:10.@@@, bFB0 = @@@NUMBER:2.@@@, fFB0 = @@@NUMBER:4.@@@,
        FB1_t = @@@NUMBER:20.@@@, bFB1 = @@@NUMBER:100.@@@, fFB1 = @@@NUMBER:100.@@@,

/* ---- Calcium store parameters ---- */
        ns = @@@NUMBER:3.@@@, Kb = @@@NUMBER:1.5@@@, Kf = @@@NUMBER:0.1@@@, fSB = @@@NUMBER:0.2@@@, bSB = @@@NUMBER:0.8@@@,
        SB_t = @@@NUMBER:20.@@@, SB_init = @@@NUMBER:2.4936218@@@,
/*      SB_t = @@@NUMBER:0.@@@, SB_init = @@@NUMBER:0.@@@,*/

/* ---- physiological parameters ---- */
        F = @@@NUMBER:9.648e+4@@@, 
        R = @@@NUMBER:8.31@@@,
        T = @@@NUMBER:293.@@@;
function:
        EK = 58.*log10(Ko/Ki);

/* ----IKa (anomalous rectifying potassium current)  ---- */
        mKa = 1./(1.+exp((V-EK)/10.));
        IKa = gKa_bar*(1.-(Glu/(Glu+1.0)))*pow(mKa,4.)*(V-EK);

/* ---- IA (Transient outward potassium current) ---- */
if (V!=75.){
        amA = 80.*(75.-V)/(exp((75.-V)/14.)-1.);
}else{
        amA = 80.*14.;
}
        bmA = 8.*exp(-(V-40)/60.);
        dmA = amA*(1.-mA)-bmA*mA;
        mA = integral(mA0,dmA);
        ahA = 0.02*exp(-V/20.);
        bhA = 4./(exp(-(V+30.)/8.)+1.);
        dhA = ahA*(1.-hA)-bhA*hA;
        hA = integral(hA0,dhA);
        IA = gA_bar*pow(mA,3.)*hA*(V-EK);

/* ---- IKv (Sustained outward potassium current) ---- */
if (V!=70.){
        amKv = 10.*(70.-V)/(exp((70.-V)/25.)-1.);
}else{
        amKv = 10.*25.;
}
        bmKv = 2.5*exp(-V/20.);
        dmKv = amKv*(1.-mKv)-bmKv*mKv;
        mKv = integral(mKv0,dmKv);
        gKv = gKv_bar*pow(mKv,4.);
        IKv = gKv*(V-EK);

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

/* --- INa (fast inward sodium current) ---- */
if (V!=35){
        amNa = 15.*(35.-V)/(exp((35.-V)/32.)-1.);
}else{
        amNa = 15.*32.;
}
        bmNa = 150.*exp(-(30.+V)/10.);
        dmNa = amNa*(1.-mNa)-bmNa*mNa;
        mNa = integral(mNa0,dmNa);
        ahNa = 60480.*exp(-(V+100.)/5.); 
        bhNa = 2304./(exp((100.-V)/75.)+1.);
        dhNa = ahNa*(1.-hNa)-bhNa*hNa;
        hNa = integral(hNa0,dhNa);
        gNa = gNa_bar*pow(mNa,3.)*hNa;
        ENa = 58.*log10(Na_o/Na_i);
        INa = gNa*(V-ENa);

/* ---- Il (Leakage current) ---- */
        Il = gl*(V-El);

/* ---- Na-Ca exchanger ---- */
        Iex = Iex_bar*exp(-(V+14.)/70.)*Ca/(Ca+Hil_ex);

/* ---- Calcium pump ---- */
        Ipump = Ipump_bar * (Ca-Ca_e)/(Ca + Hil_pump );

/* ---- Iglu ( L-glutamate sensitive current ) ---- */
        mglu = (exp((V+3.)/125.)-1.)/(exp((3.-V)/125.)+1.);
        Iglu=Iglu_bar*mglu*(pow(Glu,Hill_Iglu)
                /(pow(Glu,Hill_Iglu)+pow(K_Iglu,Hill_Iglu)));

        V_s=4*PI*pow(r,3)/3.;

        influx = -(ICa)/(2.*F*V_s)*1.e9;
        efflux = -(Iex + Ipump)/(2*F*V_s)*1.e9;

        KFB0 = fFB0/bFB0; 
        kappaFB0 = (KFB0*FB0_t)/pow(1.+Ca*KFB0,2);
        KFB1 = fFB1/bFB1; 
        kappaFB1 = (KFB1*FB1_t)/pow(1.+Ca*KFB1,2);

        dSB = pow(Ca,ns)/(pow(Ca,ns)+pow(Kb,ns))*bSB*(SB_t-SB)
        -(pow(Ca,ns)/(pow(Ca,ns)+pow(Kf,ns)))*fSB*Ca*SB;
        SB = integral(SB_init,dSB);

        dCa = (dSB + influx + efflux)/(1+kappaFB0+kappaFB1);
        Ca = integral(Ca_init,dCa);

/* --- membrane potential ---- */
        Iall = - (IKv + IKa + IA + ICa + INa + Il + Iglu);
        dV = Iall/Cm;
        V = integral(V0, dV);
end;
