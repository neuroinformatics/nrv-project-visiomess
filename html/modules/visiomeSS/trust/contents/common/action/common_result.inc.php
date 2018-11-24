<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

if ( ! isset( $title ) ) {
  die( 'FATAL' );
}

$ctime = visiomess_get_request( 'post', 'ctime', 's', null, false );
if ( ! preg_match( '/^\d+$/', $ctime ) ) {
  die( 'invalid request' );
}

// templates
$tmpl =& visiomess_get_pattemplate( $ctime );

// assign template variables
$tmpl->addVar( 'main', 'TITLE', $title );

// get parsed template
$html = $tmpl->getParsedTemplate();

// page
include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
