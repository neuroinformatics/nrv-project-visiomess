<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

require_once  dirname( __FILE__ ).'/../include/common.inc.php';

function b_visiomess_menu_show( $new_flag ) {
  global $visiomess_common;
  $block = array();
  for ( $i = 1; $i <= 6; $i++ ) {
    $_disp = 1;
    if ( isset( $_COOKIE[VSS_MENUBLOCK_COOKIE.$i] ) ) {
      $_disp = $_COOKIE[VSS_MENUBLOCK_COOKIE.$i];
    }
    $block['disp'.$i] = ( $_disp ) ? 'block' : 'none';
  }
  if ( preg_match( '/^https?:\/\/([^\/]+)(\S*)$/', XOOPS_URL, $matches ) ) {
    $block['cookie_domain'] = $matches[1];
    $block['cookie_path'] = $matches[2].'/';
  }
  $common_vars = array( 'mydirname', 'mod_url', 'mod_path' );
  foreach ( $common_vars as $var ) {
    $block[$var] = $visiomess_common[$var];
  }
  return $block;
}

?>
