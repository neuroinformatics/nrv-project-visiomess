This package contains the following files:

 Readme.txt
   This file.   
 ICa.mdl
   Ca Model descriptions written in NCS language. 
 ICa_double_compute.sl
   SATELLITE shell script file for running the Ca model.
   The script writes the results in three data files, 
   ICa_double.dat, Ca_double.dat, ICa_double_stim.dat. 
 ICa_double.sl
   SATELLITE shell script file for the Ca model. The script
   reads the data files and displays the results.
 fishHC.mdl
   Horizontal Cell Model descriptions written in NCS language. 
 Glu_resp_compute.sl
   SATELLITE shell script file for simulating the responses to
   Glutamate application. The script produces four files,
   control_V.dat, control_Ca.dat, withoutSB_V.dat, withoutSB_Ca.dat.
 Glu_resp.sl
   SATELLITE shell script file for displaying the responses to
   Glutamate application.

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

3) Execute the script by inline command, e.g., "inline("ICa_double.sl")".

   The simulation results as in Figures 3 and 5 of the reference
   paper will be displayed on the screen.

For further information, please contact:

Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Information Science and Technology
Aichi Prefectural University
Nagakute, Aichi, 480-1198
Japan