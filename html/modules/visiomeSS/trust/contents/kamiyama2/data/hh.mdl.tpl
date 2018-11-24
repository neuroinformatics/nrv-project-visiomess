/* $VisiomeSS-Revision: 1.1.1.1 $ $VisiomeSS-Date: 2003/03/04 05:05:31 $
   File:
     hh.mdl
   Title:
     Hodgkin-Huxley Model (from Clay (1998) )
   Author:
     Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
   Reference Paper:
     Hodgkin, A. L. and Huxley, A. F. (1952),
     A quantitative description of membrane current and its
     application to conduction and excitation in nerve,
     Journal of Physiology, Vol.117, pp.500-544 
     Clay, J, R. (1998),
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
exinput:        Iinp;
output:         V;
observable:     m, h, n, gNa, gK, INa, IK, IL;
parameter:      m0=@@@NUMBER:0.053574610501528@@@,
                h0=@@@NUMBER:0.592537641525269@@@,
                n0=@@@NUMBER:0.319246172904968@@@,
                V0=@@@NUMBER:-59.897674560546875@@@,
                gNa_m=@@@NUMBER:120.0@@@, ENa=@@@NUMBER:55.0@@@,
                gK_m=@@@NUMBER:36.0@@@, EK=@@@NUMBER:-72.0@@@,
                gL=@@@NUMBER:0.3@@@, EL=@@@NUMBER:-49.0@@@,
                Cm=@@@NUMBER:1.0@@@, Q=@@@NUMBER:1.0@@@;
function:
        if (V != -35.0){
        alpha_m = -0.1*(V+35.0) / (exp(-0.1*(V+35.0))-1.0);
        }else{
        alpha_m =  0.1/0.1;
        }
        beta_m  = 4.0*exp(-(V+60.0)/18.0);
        dm      = Q*(alpha_m*(1.0-m)-beta_m*m);
        m       = integral( m0, dm );
        alpha_h = 0.07*exp(-(V+60.0)/20.0);
        beta_h  = 1.0 / (exp(-0.1*(V+30.0))+1.0);
        dh      = Q*(alpha_h*(1.0-h)-beta_h*h);
        h       = integral( h0, dh );
        gNa     = gNa_m*m*m*m*h;
        INa     = gNa*(V-ENa);

        if (V!=-50){
        alpha_n = -0.01*(V+50.0) / (exp(-0.1*(V+50.0))-1.0);
        }else{
        alpha_n = 0.01/0.1;
        }
        beta_n  = 0.125*exp(-(V+60.0)/80.0);
        dn      = Q*(alpha_n*(1.0-n)-beta_n*n);
        n       = integral( n0, dn );
        gK      = gK_m*n*n*n*n;
        IK      = gK*(V-EK);

        IL      = gL*(V-EL);

        dV      = (Iinp-INa-IK-IL) / Cm;
        V       = integral( V0, dV );
end;
/* $VisiomeSS-Author: kamiyama $ */
