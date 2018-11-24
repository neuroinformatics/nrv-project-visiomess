<?php

include '../include/common.inc.php';

function is_supported_fileinfo() {
  $using_functions = array( 'finfo_file', 'finfo_open', 'finfo_close' );
  if ( ! extension_loaded( 'fileinfo' ) ) {
    return false;
  }
  foreach( $using_functions as $fname ) {
    if ( ! function_exists( $fname ) ) {
      return false;
    }
  }
  return true;
}

// remove ob filters
$handlers = ob_list_handlers();
while( ! empty( $handlers ) ) {
  ob_end_clean();
  $handlers = ob_list_handlers();
}

// check fileinfo extension
if ( ! is_supported_fileinfo() ) {
  die( 'fileinfo not supported' );
}

// get requests
// - 's' - subdir name
if ( is_null( $visiomess_common['subdir'] ) ) {
  die( 'illegal access' );
}
// - 't' - resource type : 'd' (data) or 'r' (result)
$resource_type = visiomess_get_request( 'get', 't', 's', array( 'd', 'r' ), false );
// - 'f' - file name
$file_name = visiomess_get_request( 'get', 'f', 's', null, false );
if ( ! preg_match( '/^[a-zA-Z0-9_-]+\.[a-zA-Z]+$/', $file_name ) ) {
  die( 'invalid image name'.( VSS_DEBUG_MODE ? ' fname('.$file_name.')' : '' ) );
}
// - 'd' - result time 
if ( $resource_type == 'r' ) {
  $result_time = visiomess_get_request( 'get', 'd', 's', null, false );
  if ( ! preg_match( '/^\d+$/', $result_time ) ) {
    die( 'invalid result time'.( VSS_DEBUG_MODE ? ' time('.$result_time.')' : '' ) );
  }
}

// build physical file path from request variables
require_once VSS_CLASS_PATH.'/filebox.class.php';
$filebox =& VisiomeSS_FileBox::getInstance();
if ( $resource_type == 'd' ) {
  $file_path = $filebox->get_path( 'dbox', $file_name );
} else {
  $file_path = $filebox->get_path( 'cbox', array( $result_time, $file_name ) );
}
if ( ! file_exists( $file_path ) || ! is_readable( $file_path ) ) {
  exit( 'file not found'.( VSS_DEBUG_MODE ? ' path('.$file_path.')' : '' ) );
}

// get file status
$finfo = finfo_open( FILEINFO_MIME, VSS_MIMEFILE_PATH );
$mime_type = finfo_file( $finfo, $file_path );
list($mime_type) = explode(';', $mime_type);
finfo_close( $finfo );
$file_size = filesize( $file_path );
$image_mime_types = array( 'image/png', 'image/gif', 'image/jpeg' );
if ( ! in_array( $mime_type, $image_mime_types ) ) {
  die( 'file is not image data'.( VSS_DEBUG_MODE ? ' type('.$mime_type.')' : '') );
}

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
