<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

if ( ! isset( $title ) || ! isset( $file ) ) {
  die( 'FATAL' );
}

// using action template name
if ( ! isset( $tname ) ) {
  $tname = 'save';
}

// parameter type
if ( ! isset( $ptype ) ) {
  $ptype = 'template';
}

// request form type
if ( ! isset( $rtype ) ) {
  $rtype = '';
}

require_once VSS_CLASS_PATH.'/parammanager.class.php';
$paramman =& VisiomeSS_ParameterManager::getInstance();
$param =& $paramman->load( $ptype, $file );

$save_ok = true;

$myts =& MyTextSanitizer::getInstance();

$errors = array();
$save_ok = $param->get_request( $errors, $rtype );

if ( $save_ok ) {
  $param->save();
} else {
  foreach( $errors as $err ) {
    $errmes[] = array( 'error' => $myts->htmlSpecialChars( $err ) );
  }
}

// templates
$tmpl =& visiomess_get_pattemplate( null, $tname );

// assign template variables
$tmpl->addVar( 'main', 'TITLE', $title );
$tmpl->addVar( 'body', 'IS_ERROR', ! $save_ok );
if ( $save_ok ) {
  $tmpl->addVar( 'body', 'PARAM', $param->display( $rtype ) );
} else {
  $tmpl->addRows( 'errors', $errmes );
}

// page
include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
