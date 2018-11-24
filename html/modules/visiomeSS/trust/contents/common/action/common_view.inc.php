<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

if ( ! isset( $title ) ) {
  die( 'FATAL' );
}

if ( ! isset( $tname ) ) {
  $tname = 'view';
}

if ( ! isset( $rtype ) ) {
  $rtype = '';
}

$myts =& MyTextSanitizer::getInstance();

$filebox =& VisiomeSS_FileBox::getInstance();

$rpaths = $filebox->get_result_path( $rtype );
$is_empty = empty( $rpaths );
$results = array();
$is_first = true;
foreach ( $rpaths as $rpath ) {
  $results[] = array(
    'VALUE' => $myts->htmlSpecialChars( $rpath['value'] ),
    'LABEL' => $myts->htmlSpecialChars( $rpath['label'] ),
    'IS_CHECKED' => $is_first
  );
  $is_first = false;
}
 
// templates
$tmpl =& visiomess_get_pattemplate( null, $tname );

// assign template variables
$tmpl->addVar( 'main', 'TITLE', $title );
$tmpl->addVar( 'body', 'IS_EMPTY', $is_empty );
if ( ! $is_empty ) {
  $tmpl->addRows( 'results', $results );
}

// page
include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
