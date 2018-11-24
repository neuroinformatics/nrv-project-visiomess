<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

if ( ! isset( $title ) || ! isset( $taskman ) ) {
  die( 'FATAL' );
}

if ( ! isset( $tname ) ) {
  $tname = 'run';
}

// load parameters
if ( isset( $params ) ) {
  require_once VSS_CLASS_PATH.'/parammanager.class.php';
  $paramman =& VisiomeSS_ParameterManager::getInstance();
  $pinst = array();
  foreach( $params as $ptype => $pfiles ) {
    foreach( $pfiles as $pfile ) {
      $pinst[] =& $paramman->load( $ptype, $pfile );
    }
  }
}

if ( ! isset( $errors ) ) {
  // run
  $ctime = $taskman->run();
  // get results
  $results = $taskman->display();
} else {
  // error
  $ctime = 0;
  $ul_st = '<p>&raquo;&nbsp;Error</p><ul>';
  $ul_en = '</ul>';
  $li_st = '<li>';
  $li_en = '</li>';
  $results = $ul_st.$li_st.implode( $li_en.$li_st, $errors ).$li_en.$ul_en;
}

// templates
$tmpl =& visiomess_get_pattemplate( null, $tname );

// assign template variables
$tmpl->addVar( 'main', 'TITLE', $title );
$tmpl->addVar( 'main', 'RESULTS', $results );
if ( empty( $ctime ) ) {
  $tmpl->setAttribute( 'form', 'Visibility', 'hidden' );
} else {
  $tmpl->addVar( 'form', 'CTIME', $ctime );
}
// get parsed template
$html = $tmpl->getParsedTemplate();

// page
include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
