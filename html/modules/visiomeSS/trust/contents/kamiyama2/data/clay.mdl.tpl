/* $VisiomeSS-Revision: 1.2 $ $VisiomeSS-Date: 2003/03/04 05:24:29 $
   File:
     clay.mdl
   Title:
     Clay modifiedl Hodgkin-Huxley Model
   Author:
     Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
   Reference Paper:
     Clay, J, R. (1998)
     Excitability of the Squid Gian Axon Revisited,
     Journal of Neurophysiology, Vol.80, pp.903-913
*/
type:           NETWORK;
module:         Squid_Giant_Axon;
cell:           HH[1];
connection:
        HH[0] < ();
end;

type:           CELL;
module:         HH;
exinput:        Iext;
output:         V;
observable:     n, IK, Ks, INa,
                C2, C3, C4, C5, I, I4, I5, O,
                IL;
parameter:      n0=@@@NUMBER:0.379878@@@,
                V0=@@@NUMBER:-61.1432647705@@@,
                Ks0=@@@NUMBER:0.2420274466@@@,
                C20=@@@NUMBER:0.1547295153@@@, C30=@@@NUMBER:0.0328097902@@@,
                C40=@@@NUMBER:0.0069571873@@@, C50=@@@NUMBER:0.0027652706@@@,
                I0=@@@NUMBER:0.0008073342@@@, I40=@@@NUMBER:0.0516124554@@@,
                I50=@@@NUMBER:0.205117743@@@, O0=@@@NUMBER:0.0001091067@@@,
                gNamax=@@@NUMBER:215.0e-02@@@, VNa=@@@NUMBER:64.0@@@,
                gKmax=@@@NUMBER:62.5e-02@@@, VK=@@@NUMBER:-72.0@@@,
                Kd=@@@NUMBER:2.0@@@, Ko=@@@NUMBER:10.0@@@, Ki=@@@NUMBER:300.0@@@, theta=@@@NUMBER:20.0@@@,
                tau_1=@@@NUMBER:12.0@@@, tau_2=@@@NUMBER:0.2@@@,
                gL=@@@NUMBER:0.3e-02@@@, VL=@@@NUMBER:-49.0@@@,
                Cm=@@@NUMBER:1.0e-02@@@;
/* unit
   V in mV, G in nS/um^2, C in pF/um^2, I in pA/um^2, t in msec
*/
function:
        a = 7.55*exp(0.017*(V-10.0));
        b = 5.6*exp(-0.00017*(V-10.0));
        c = 21.0*exp(0.06*(V-10.0));
        d = 1.8*exp(-0.02*(V-10.0));
        f = 0.56*exp(0.00004*(V-10));
        g = exp(0.00004*(V-10.0));
        i = 0.0052*exp(-0.038*(V-10.0));
        j = 0.009*exp(-0.038*(V-10.0));
        y = 22.0*exp(0.014*(V-10.0));
        z = 1.26*exp(-0.048*(V-10.0));
        dC2 = y-(2.0*y+z)*C2+(z-y)*C3-y*(C4+C5+I+I4+I5+O);
        C2  = integral( C20, dC2 );
        dC3 = y*C2-(y+z)*C3+z*C4;
        C3  = integral( C30, dC3 );
        dC4 = y*C3-(a+z+g)*C4+b*C5+j*I4;
        C4  = integral( C40, dC4 );
        dC5 = a*C4-(b+c)*C5+d*O;
        C5  = integral( C50, dC5 );
        dI  = -(d+i)*I+c*I5+f*O;
        I   = integral( I0, dI );
        dI4 = g*C4-(j+a)*I4+b*I5;
        I4  = integral( I40, dI4 );
        dI5 = d*I+a*I4-(b+c)*I5;
        I5  = integral( I50, dI5 );
        dO  = c*C5+i*I-(d+f)*O;
        O   = integral( O0, dO );
        C1  = 1.0-(C2+C3+C4+C5+I+I4+I5+O);
        tmp = gNamax*O*V*(exp((V-VNa)/24.0)-1.0);
        ump = ( exp(V/24.0)-1.0 ) * ( 1.0 + 0.4*exp(-0.38*V/24.0) );
        INa = tmp / ump;

        alpha_n = -0.01*(V+50.0) / (exp(-0.1*(V+50.0))-1.0);
        beta_n  = 0.1*exp(-(V+60.0)/25.0);
        dn      = alpha_n*(1.-n)-beta_n*n;
        dKs     = 10.36*IK/theta - (Ks-Ko)/tau_1 
                  - (Ks-Ko) /( tau_2*pow( (1.0+(Ks-Ko)/Kd), 3.0));
        Ks      = integral( Ks0, dKs );
        n       = integral( n0, dn );
        tmp     = gKmax*n*n*n*n*V;
        ump     = (exp(V/24.0)-Ks/Ki) / (exp(V/24.0)-1.0);
        IK      = tmp * ump;

        IL      = gL*(V-VL);

        dV      = (Iext-INa-IK-IL) / Cm;
        V       = integral( V0, dV );
end;
/* Copyright 2003, KAMIYAMA Yoshimi */
/* $VisiomeSS-Author: kamiyama $ */
