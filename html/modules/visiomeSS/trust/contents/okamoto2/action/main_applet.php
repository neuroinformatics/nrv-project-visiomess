<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

// remove ob filters
$handlers = ob_list_handlers();
while( ! empty( $handlers ) ) {
  ob_end_clean();
  $handlers = ob_list_handlers();
}

// - 'f' - file name
$file_name = visiomess_get_request( 'get', 'f', 's', null, false );
$jars = array( 'original.jar', 'hough.jar', 'velocity.jar' );
if ( ! in_array( $file_name, $jars ) ) {
  die( 'invalid jar name'.( VSS_DEBUG_MODE ? ' fname('.$file_name.')' : '' ) )
;
}

$file_path = $visiomess_common['filebox']->get_path( 'dbox', $file_name );
if ( ! file_exists( $file_path ) ) {
  die( 'file not found' );
}
$mime_type = 'application/x-zip';
$file_size = filesize( $file_path );

// output header
$cache_limit = 3600 ; // default 3600sec == 1hour
session_cache_limiter( 'public' );
header( 'Expires: '.date( 'r', intval( time() / $cache_limit ) * $cache_limit + $cache_limit ) );
header( 'Cache-Control: public, max-age='.$cache_limit );
header( 'Last-Modified: '.date( 'r', intval( time() / $cache_limit ) * $cache_limit ) );
header( 'Content-type: '.$mime_type );
header( 'Content-size: '.$file_size );

// output file
readfile( $file_path );

?>
