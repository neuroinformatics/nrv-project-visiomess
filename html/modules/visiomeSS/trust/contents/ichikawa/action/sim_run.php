<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

// get request
$plot_syms = array();
for ( $i = 1; $i <= 24; $i++ ) {
  $var = visiomess_get_request( 'post', 'plotVar'.$i, 'i', array( 1 ), true );
  if ( ! is_null( $var ) ) {
   $plot_syms[] = $i - 1;
  }
}

function acell_convert_result( $args ) {
  list( $ofile, $rfile, $sfile, $num_sym ) = $args;
  $filebox =& VisiomeSS_FileBox::getInstance();
  $outfile = $filebox->get_path( 'wbox', $ofile );
  $resfile = $filebox->get_path( 'wbox', $rfile );
  $slfile = $filebox->get_path( 'wbox', $sfile );
  $fout = fopen( $ofile, 'r' );
  if ( $fout === false ) {
    die( 'simulation result not found' );
    return false;
  }
  // skip version & csim name & symbols
  $line = fgets( $fout, 4096 );
  $line = fgets( $fout, 4096 );
  for ( $i = 0; $i < $num_sym; $i++ ) {
    $line = fgets( $fout, 4096 );
  }
  // seek to result
  while ( !feof( $fout ) ) {
    $line = fgets( $fout, 4096 );
    $sep = trim( $line );
    if ( $sep == '*' ) {
      break;
    }
  }
  // write result
  $fres = fopen( $resfile, "w" );
  if ( $fres === false ) {
    die( 'simulation result not found' );
  }
  while ( !feof( $fout ) ) {
    $line = fgets( $fout, 4096 );
    if ( strstr( $line, "/*symbol" ) ) break;
    fwrite( $fres, $line );
  }
  fclose( $fout );
  fclose( $fres );
  return true;
}

function acell_make_satellite( $args ) {
  list( $sfile, $rfile, $csim, $syms ) = $args;
  $filebox =& VisiomeSS_FileBox::getInstance();
  $slfile = $filebox->get_path( 'wbox', $sfile );
  $fsl = fopen( $slfile, 'w' );
  if ( $fsl === false ) {
    die( 'failed to open satellite script' );
    return false;
  }
  fwrite( $fsl, 'proc plotGraph( x, y, xSize, ySize, var ) {'."\n" );
  fwrite( $fsl, '  origin( x, y );'."\n" );
  fwrite( $fsl, '  size( xSize, ySize );'."\n" );
  fwrite( $fsl, '  graph( var, "T", 0, 0, 0, 1, 3.5 );'."\n" );
  fwrite( $fsl, '  axis( 1, 1, "XY", "XY", 5.5, 0, 0, 0, 0,0 );'."\n" );
  fwrite( $fsl, '  frame();'."\n" );
  fwrite( $fsl, '}'."\n" );
  fwrite( $fsl, 'x = text2buffer( "'.$rfile.'" );'."\n" );
  fwrite( $fsl, 'wopen( 1, "A4", 0, 2 );'."\n" );
  fwrite( $fsl, 'scale( "N", "A", "N", "A" );'."\n" );
  for ( $i = 0; $i < 6; $i++ ) {
    if ( ! isset( $syms[$i] ) ) {
      break;
    }
    list( $label, $idx ) = $syms[$i];
    $xorg = 30 + ( $i % 2 ) * 90;
    if ( $i % 2 ) {
      $yorg = 190 - ( $i - 1 ) / 2 * 80;
    } else {
      $yorg = 190 - $i / 2 * 80;
    }
    fwrite( $fsl, 'plotGraph('.$xorg.', '.$yorg.', 60, 60, x['.$idx.'] );'."\n" );
    fwrite( $fsl, 'label( "I", 60, 62, 5.0, 0, "'.$label.'", 1 );'."\n" );
  }
  fwrite( $fsl, 'origin( 20, 20 );'."\n" );
  fwrite( $fsl, 'label("I", 180, 250, 5.0, 0, "'.$csim.'.Csim",1);'."\n" );
  fclose( $fsl );
  return true;
}

// load parameter
require_once VSS_CLASS_PATH.'/parammanager.class.php';
$paramman =& VisiomeSS_ParameterManager::getInstance();
$param = $paramman->load( 'acell', 'RK.TMP' );
$csim = $param->get_csim();
$ofile = $param->get_outfile();
$rfile = 'simResult.txt';
$sfile = 'plot.sl';
$num_sym = $param->get_num_symbol();
$syms = array();
foreach( $plot_syms as $ps ) {
  $label = $param->get_symbol_label( $ps );
  $syms[] = array( $label, $ps );
}

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// make task
$make =& $taskman->create_task( 'make' );
$make->set_target( $csim );
$make->add_source( $csim.'.c' );
$make->set_name( 'compile A-CELL generated C program' );

// command task
$cmd =& $taskman->create_task( 'command' );
$cmd->set_command( './'.$csim );
$cmd->add_tempfile( $ofile );
$cmd->set_name( 'execution of A-CELL generated C program' );

// function task 1
$func1 =& $taskman->create_task( 'function' );
$args = array( $ofile, $rfile, $sfile, $num_sym );
$func1->set_function( 'acell_convert_result', $args );
$func1->add_tempfile( $rfile );
$func1->set_name( 'make result file' );

// function task 2
$func2 =& $taskman->create_task( 'function' );
$args = array( $sfile, $rfile, $csim, $syms );
$func2->set_function( 'acell_make_satellite', $args );
$func2->add_tempfile( $sfile );
$func2->set_name( 'make SATELLITE script' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( $sfile, false );

// result
$taskman->set_result( 'result.ps', true );

if ( empty( $plot_syms ) ) {
  $errors = array( 'Not Selected Plot Symbols' );
}

$title = 'Run Simulation';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
