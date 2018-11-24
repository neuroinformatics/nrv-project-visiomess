<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

$visiomess_common['filebox']->copy_file_data2work( 'beeVision.conf', false );

// read condition file
$params = array();
$lines = explode( "\n", $visiomess_common['filebox']->load_file( 'beeVision.conf', false ) );
foreach( $lines as $num => $line ) {
  // strip bol and eol spaces
  $line = trim( $line );
  // strip comment line
  $line = preg_replace( '/\s*#.*$/', '', $line );
  // skip empty line
  if ( empty( $line ) ) {
    continue;
  }
  if ( preg_match( '/^([a-zA-Z0-9_]+)\s*=\s*(.+)$/', $line, $matches ) ) {
    $params[$matches[1]] = $matches[2];
  } else {
    die( 'unkown line found in condition file in beeVision.conf at '.$num );
  }
}

// preprocess for template values

// step['Ph'], step['Th']
$step = array();
$names = array( 'Ph', 'Th' );
$vals = array( '0.7', '1.0', '1.3', '1.6', '1.7' );
foreach ( $names as $name ) {
  $step[$name] = array();
  foreach ( $vals as $val ) {
    $step[$name][] = array(
      'value' => $val,
      'is_selected' => ( $val == $params['step'.$name] )
    );
  }
}

// figCenter['X'], figCenter['Y'], figCenter['Z']
$figCenter = array();
$names = array( 'X', 'Y', 'Z' );
$vals = array( '20.', '15.', '10.', '5.', '0.', '-5.', '-10.', '-15.', '-20.' );
$cvals = array_map( 'trim', explode( ',', $params['figCenter'] ) );
foreach ( $names as $num => $name ) {
  $figCenter[$name] = array(); 
  foreach ( $vals as $val ) {
    $figCenter[$name][] = array(
      'value' => $val,
      'is_selected' => ( $val == $cvals[$num] )
    );
  }
}

// figAngle['H'], figAngle['V']
$figAngle = array();
$vals = array( '90.', '45.', '0.', '-45.', '-90.' );
$names = array( 'H', 'V' );
$cvals = array_map( 'trim', explode( ',', $params['figAngle'] ) );
foreach ( $names as $num => $name ) {
  $figAngle[$name] = array();
  foreach ( $vals as $val ) {
    $figAngle[$name][] = array(
      'value' => $val,
      'is_selected' => ( $val == $cvals[$num] )
    );
  }
}

// figDotD
$figDotD = array();
$vals = array( '0.1', '0.25', '0.5', '1.0' );
foreach ( $vals as $val ) {
  $figDotD[] = array(
    'value' => $val,
    'is_selected' => ( $val == $params['figDotD'] )
  );
}

// figFile
$figFile = array();
$vals = array( '0304324', '0304325m', 'r0300165' );
foreach ( $vals as $num => $val ) {
  $figFile[] = array(
    'value' => $val,
    'is_checked' => ( $val.'.pgm' == $params['figFile'] ),
    'padding' => ( ( $num != 0 ) ? '&nbsp;&nbsp;&nbsp;&nbsp;' : '' )
  );
}

// templates
$tmpl =& visiomess_get_pattemplate();

// assign template variables
$tmpl->addRows( 'stepTh', $step['Th'] );
$tmpl->addRows( 'stepPh', $step['Ph'] );
$tmpl->addRows( 'figCenterX', $figCenter['X'] );
$tmpl->addRows( 'figCenterY', $figCenter['Y'] );
$tmpl->addRows( 'figCenterZ', $figCenter['Z'] );
$tmpl->addRows( 'figAngleH', $figAngle['H'] );
$tmpl->addRows( 'figAngleV', $figAngle['V'] );
$tmpl->addRows( 'figDotD', $figDotD );
$tmpl->addRows( 'figFile', $figFile );

include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
