NRV Project Model Distribution
==============================

Title:
 Revised Hodgkin-Huxley Model by Clay
Author:
 KAMIYAMA Yoshimi
e-mail:
 kamiyama@ist.aichi-pu.ac.jp
Reference Paper:
 Clay, J, R. (1998),
 Excitability of the Squid Gian Axon Revisited,
 Journal of Neurophysiology, Vol.80, pp.903-913
 PubMed: 9705477
-------------------------------------------------------------

This package contains the following files:

 Readme.txt
   This file.	
 hh.mdl
   Classical HH Model written in NCS language. 
 hh.sl
   SATELLITE shell script file for the Classical HH.
 clay.mdl
   Revised HH Model written in NCS language. 
 clay.sl 
   SATELLITE shell script file for the Revised HH.
 hh-clay.sl
   SATELLITE shell script file for running the models.

HOW TO RUN
----------

0) This package is running with SATELLITE system developed at
   Biological & Physiological Engineering Laboratory, Toyohashi
   University of Technology. SATELLITE will be found in the 
   followings: 
       http://www.nrv.neuroinformatics.jp/
       ftp://ftp.nrv.neuroinformatics.jp/

1) Put all files in the same working directory.

2) In the working directory, run SATELLITE by "sl" command. 

3) Execute the script by "inline("hh-clay.sl")".

   The simulation results as in Figure 3 of the reference
   paper will be displayed on the screen.

For further information, please contact:

Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Faculty of Information Science and Technology
Aichi Prefectural University
Nagakute, Aichi, 480-1198
Japan
// Copyright 2003, KAMIYAMA Yoshimi
// $Revision: 1.1 $ Last updated $Date: 2008/05/14 05:20:20 $
// $Author: okumura $