<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

include VSS_INCLUDE_PATH.'/function.inc.php';

global $visiomess_common;

$visiomess_common = array();
$visiomess_common['uname'] = visiomess_get_uname();
$visiomess_common['mydirname'] = $mydirname;
$visiomess_common['mod_url'] = $mod_url;
$visiomess_common['mod_path'] = $mod_path;

// $visiomess_common['subdirs']
include VSS_CONTENTS_PATH.'/subdirs.inc.php';

// $visiomess_common['subdir']
$visiomess_common['subdir'] = visiomess_get_request( 'get', 's', 's', $visiomess_common['subdirs'], true );

// $visiomess_common['pages']
if ( is_null( $visiomess_common['subdir'] ) ) {
  $visiomess_common['pages'] = array();
} else {
  include VSS_CONTENTS_PATH.'/'.$visiomess_common['subdir'].'/pages.inc.php';
}

// $visiomess_common['page']
if ( empty( $visiomess_common['pages'] ) ) {
  $visiomess_common['page'] = null;
} else {
  $visiomess_common['page'] = visiomess_get_request( 'get', 'p', 's', array_keys( $visiomess_common['pages'] ), true );
  if ( is_null( $visiomess_common['page'] ) ) {
    $visiomess_common['page'] = 'main';
  }
}

// $visiomess_common['action']
if ( is_null( $visiomess_common['page'] ) ) {
  $visiomess_common['action'] = null;
} else {
  if ( isset( $_GET['a'] ) ) {
    $visiomess_common['action'] = visiomess_get_request( 'get', 'a', 's', $visiomess_common['pages'][$visiomess_common['page']]['get'], false );
  } else if ( isset( $_POST['a'] ) ) {
    $visiomess_common['action'] = visiomess_get_request( 'post', 'a', 's', $visiomess_common['pages'][$visiomess_common['page']]['post'], false );
  } else {
    $visiomess_common['action'] = 'default';
  }
}

?>
