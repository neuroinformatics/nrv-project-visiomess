=====  Recognition of Partly Occluded Patterns: A Neural Network Model  =====

-----  Simulation program in C language  -----


##### How to Use #####

[1] Files to be downloaded:
    Readme.txt    Explanation: How to run the program
    NeoOccl.c     Main program for the simulation
    Header.dat    Header for PS or EPS files (to be read during the simulation)
    PatLearn.dat  Learning pattern set
    PatTest.dat   Test pattern set (target patterns to be occluded)
    PatMask.dat   Occluding pattern set



[2] How to run the program

1) Put the following files in the same directory:
    NeoOccl.c
    Header.dat
    PatLearn.dat
    PatTest.dat
    PatMask.dat

2) Compile and link  NeoOccl.c  using a C compiler.

3) If you run the program, you will get the following files depending on the
   control parameters.  See 4) below for the control parameters.
    connect.dat   Data file containing the values of the connections 
                  between cell-planes.
    outall.ps     PostScript file displaying the response of the network.
                  All pages of the display are included in this single file.
    out???.eps    Encapsulated PostScript file displaying the response of
                  the network.  Each page of the display is written in a
                  separate file.  ??? is the sequence number of the files.
    res.dat       ASCII file of the response of the network

4) You can choose the type of output files or change the parameters for the
   simulation by editing the program  NeoOccl.c.
   All important parameters are gathered in the top of the main program main().

 a) Mode of the simulation and output files can be changed by the following
    parameters.

   learn (lines 374-375 of file NeoOccl.c)
     learn = 1:  The network learns patterns using the learning set PatLearn.dat
                 and the connections are written in Connect.dat.
                 After that, the response of the network to the test patterns
                 will be calculated.
     learn = 0:  The network skip the learning phase and read the values of
                 connections from Connect.dat.
                 Then, the response of the network to the test patterns is
                 calculated.
                 For the initial run of the program, learn=1 must be assigned.

   ifpN (lines 376-377)
     ifpN = 0:   No output to PS nor EPS files.
     ifpN = 1:   Generate separate EPS (Encapsulated PostScript) files.
                 Each file has an image of a response of the network in a
                 particular condidion.
                 The names of the output files are out???.dat, where ??? is
                 a sequence number of the output files.
     ifpN = 2:   Generate a single PS (PostScript) file (outall.ps), in which
                 all pages of the display are included.
     Since the response of each cell is represented by a hexadecimal character
     in these PS and EPS files, you can also observe the response using an
     editor that can display ASCII characters.

   iprl[] and iprl[] (lines 379-383)
     Each digit in arrays iprl[] and iprl[] controls the output of the response
     of a layer in the learning and the recognition phases, respectively.
     The responses are written in res.dat with an ASCII format.
       = 0:  No display.
       = 1:  The response of the assigned layer is displayed.
       = 2:  Sum of the responses of all cell-planes of the layer are displayed.
     If all digits in iprl[] and iprl[] are zero, res.dat will not be generated.

   tpm[][2] (lines 385-390)
     Specify test patterns in the recognition phase.
     Combination of maskee (target pattern to be masked) and masker (masking
     pattern) can be assigned by the sequence number (starting from 0) in 
     pattern sets PatTest.dat and PatMask.dat, respectively.
     (-1) indicates the end of the test.

 b) All parameters specifying the network are written in the top of the 
    main program.
    For example, you can change the scale of the network by modifying the values
    of N0, Nc[], Ns[] (lines 336-338), and so on.  In this case, however, you
    also need to modify files PatLearn.dat, PatTest.dat and PatMask.dat,
    depending on the size of the input layer.
    Thresholds for the learning and recognition phases are given in thetal[] and
    thetar[] (lines 359-360).




##### Licence Terms #####

        Title of work:   Computer program recognizing occluded patterns
        Creator
