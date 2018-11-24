<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

if ( ! isset( $title ) || ! isset( $params ) || ! isset( $do_output ) ) {
  die( 'FATAL' );
}

if ( ! isset( $tname ) ) {
  $tname = 'reset';
}

$myts =& MyTextSanitizer::getInstance();

require_once VSS_CLASS_PATH.'/parammanager.class.php';
$paramman =& VisiomeSS_ParameterManager::getInstance();

$tparams = array();
foreach ( $params as $ptype => $pfiles ) {
  foreach( $pfiles as $pfile ) {
    $param =& $paramman->load( $ptype, $pfile );
    $param->save();
    $html = ( $do_output ? $param->display() : '' );
    $tparams[] = array(
      'name' => $myts->htmlSpecialChars( $param->get_fname() ),
      'html' => $html,
      'do_output' => $do_output
    );
  }
}

// templates
$tmpl =& visiomess_get_pattemplate( null, $tname );

// assign template variables
$tmpl->addVar( 'main', 'TITLE', $title );
$tmpl->addRows( 'params', $tparams );

// page
include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
