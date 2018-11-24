<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

if ( ! isset( $title ) || ! isset( $file ) || ! isset( $action ) ) {
  die( 'FATAL' );
}

// using action template name
if ( ! isset( $tname ) ) {
  $tname = 'edit';
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
$param = $paramman->load( $ptype, $file );

// templates
$tmpl =& visiomess_get_pattemplate( null, $tname );

// assign template variables
$tmpl->addVar( 'main', 'TITLE', $title );
$tmpl->addVar( 'main', 'FORM', $param->form( $rtype ) );
$tmpl->addVar( 'main', 'ACTION', $action );

// page
include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
