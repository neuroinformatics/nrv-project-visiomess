/* $VisiomeSS-Revision: 1.2 $ $VisiomeSS-Date: 2003/03/04 05:24:29 $
   File:
     hh-clay.sl
   Title:
     Revised Hodgkin-Huxley Model by Clay
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

wopen(1, "A4", 0, 2);
size(@@@NUMBER:150@@@,@@@NUMBER:100@@@);
origin(@@@NUMBER:30@@@,@@@NUMBER:150@@@);
inline("hh.sl");
label("I",@@@NUMBER:145@@@,@@@NUMBER:90@@@,8,0,"Classical HH",1);

origin(@@@NUMBER:30@@@,@@@NUMBER:30@@@);
inline("clay.sl");
label("I",@@@NUMBER:145@@@,@@@NUMBER:90@@@,8,0,"Revised HH",1);

/* Copyright 2003, KAMIYAMA Yoshimi */
/* $VisiomeSS-Author: kamiyama $*/
