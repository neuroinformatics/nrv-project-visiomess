NRV Project Model Distribution
==============================

Title:
 Hodgkin-Huxley Model
Author:
 Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Reference Paper:
  Hodgkin, A. L. and Huxley, A. F. (1952),
  A quantitative description of membrane current and its
  application to conduction and excitation in nerve,
  Journal of Physiology, Vol.117, pp.500-544 
-------------------------------------------------------------

This package contains the following files:

 README
   This file.	
 nrv-hh.mdl
   Hodgkin-Huxley model descriptions written in NCS language.
 nrv-hh.sl
   SATELLITE shell script file for running the model.

HOW TO RUN
----------

0) This package is running with SATELLITE system developed at
   Biological & Physiological Engineering Laboratory, Toyohashi
   University of Technology. SATELLITE will be found in the 
   followings: 
       http://www.nrv.neuroinformatics.jp/
       ftp://ftp.nrv.neuroinformatics.jp/

1) Put "nrv-hh.mdl" and "nrv-hh.sl" in the same working directory.

2) In the working directory, run SATELLITE by "sl" command. 

3) Execute the script by "inline("nrv-hh.sl")".

   The simulation results as in Figure 19 of the reference paper will
   be displayed.

For further information, please contact:

Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Faculty of Information System and Technology
Aichi Prefectural University
Nagakute, Aichi, 480-1198
Japan
$Revision: 1.1 $ Last updated $Date: 2008/05/07 16:57:34 $