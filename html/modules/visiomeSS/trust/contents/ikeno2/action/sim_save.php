<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

$visiomess_common['filebox']->copy_file_data2work( 'beeVision.conf', false );

$meta_vals = array(
 'step' => array( '0.7', '1.0', '1.3', '1.6', '1.7' ),
 'figCenter' => array( '20.', '15.', '10.', '5.', '0.', '-5.', '-10.', '-15.', '-20' ),
 'figAngle' => array( '90.', '45.', '0.', '-45.', '-90.' ),
 'figDotD' => array( '0.1', '0.25', '0.5', '1.0' ),
 'figFile' => array( '0304324', '0304325m', 'r0300165' ),
);
$acceptable_vars = array(
  'stepPh' => $meta_vals['step'],
  'stepTh' => $meta_vals['step'],
  'figCenterX' => $meta_vals['figCenter'],
  'figCenterY' => $meta_vals['figCenter'],
  'figCenterZ' => $meta_vals['figCenter'],
  'figAngleV' => $meta_vals['figAngle'],
  'figAngleH' => $meta_vals['figAngle'],
  'figDotD' => $meta_vals['figDotD'],
  'figFile' => $meta_vals['figFile'],
);

// check requested variables
$params = array();
foreach( $acceptable_vars as $key => $vals ) {
  $params[$key] = visiomess_get_request( 'post', $key, 's', $vals, false );
}

// read condition file
$data = $visiomess_common['filebox']->load_file( 'beeVision.conf', false );

$searches = array(
  '/^(\s*stepPh\s*=\s*)[^\s]+(\s*(#.*)?)$/m',
  '/^(\s*stepTh\s*=\s*)[^\s]+(\s*(?:#.*)?)$/m',
  '/^(\s*figCenter\s*=\s*)[^\s]+\s*,\s*[^\s]+\s*,\s*[^\s]+(\s*(?:#.*)?)$/m',
  '/^(\s*figAngle\s*=\s*)[^\s]+\s*,\s*[^\s]+(\s*(?:#.*)?)$/m',
  '/^(\s*figDotD\s*=\s*)[^\s]+(\s*(?:#.*)?)$/m',
  '/^(\s*figFile\s*=\s*)[^\s]+(\s*(?:#.*)?)$/m',
);
$replaces = array(
  '${1}'.$params['stepPh'].'${2}',
  '${1}'.$params['stepTh'].'${2}',
  '${1}'.$params['figCenterX'].', '.$params['figCenterY'].', '.$params['figCenterX'].'${2}',
  '${1}'.$params['figAngleH'].', '.$params['figAngleV'].'${2}',
  '${1}'.$params['figDotD'].'${2}',
  '${1}'.$params['figFile'].'.pgm${2}',
);

$data = preg_replace( $searches, $replaces, $data );

$visiomess_common['filebox']->save_file( 'beeVision.conf', $data );

// templates
$tmpl =& visiomess_get_pattemplate();

// assign template variables
$tmpl->addVar( 'main', 'STEP_TH', $params['stepTh'] );
$tmpl->addVar( 'main', 'STEP_PH', $params['stepPh'] );
$tmpl->addVar( 'main', 'FIG_CENTER_X', $params['figCenterX'] );
$tmpl->addVar( 'main', 'FIG_CENTER_Y', $params['figCenterY'] );
$tmpl->addVar( 'main', 'FIG_CENTER_Z', $params['figCenterZ'] );
$tmpl->addVar( 'main', 'FIG_ANGLE_H', $params['figAngleH'] );
$tmpl->addVar( 'main', 'FIG_ANGLE_V', $params['figAngleV'] );
$tmpl->addVar( 'main', 'FIG_DOT_D', $params['figDotD'] );
$tmpl->addVar( 'main', 'FIG_FILE', $params['figFile'] );

include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
