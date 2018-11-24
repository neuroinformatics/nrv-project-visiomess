<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

$ctime = visiomess_get_request( 'post', 'ctime', 's', null, false );
if ( ! preg_match( '/^\d+$/', $ctime ) ) {
  die( 'invalid request' );
}

// read condition file
$params = array();
$lines = explode( "\n", $visiomess_common['filebox']->read_result( $ctime, 'beeVision.conf' ) );
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

// preprocess for template variable
$figSize = array(
  '0304324.pgm' => array( 196, 124 ),
  '0304325m.pgm' => array( 119, 96 ),
  'r0300165.pgm' => array( 208, 153 ),
);
$figFile = $params['figFile'];
$figCenter = $params['figCenter'];
$figAngle = $params['figAngle'];
$figDotD = $params['figDotD'];
list( $figX, $figY ) = $figSize[$figFile];
$figX *= $figDotD;
$figY *= $figDotD;
$imgFile = preg_replace( '/\.pgm$/', '.png', $figFile );

// templates
$tmpl =& visiomess_get_pattemplate( $ctime );

// assign template variables
$tmpl->addVar( 'main', 'FIG_FILE', $figFile );
$tmpl->addVar( 'main', 'FIG_CENTER', $figCenter );
$tmpl->addVar( 'main', 'FIG_ANGLE', $figAngle );
$tmpl->addVar( 'main', 'FIG_DOTD', $figDotD );
$tmpl->addVar( 'main', 'FIG_X', $figX );
$tmpl->addVar( 'main', 'FIG_Y', $figY );
$tmpl->addVar( 'main', 'IMG_FILE', $imgFile );

// page
include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
