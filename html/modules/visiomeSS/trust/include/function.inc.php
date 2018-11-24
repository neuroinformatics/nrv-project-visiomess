<?php

// functions - this file will called from common.inc.php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

/**
 * get http request
 *
 * @param string $method method : 'post' or 'get'
 * @param string $variable variable
 * @param string $type data type : 's' => string, 'i' => integer, 'f' =>float
 * @param array $wlist white list
 * @param bool $nullok flag for acceptable null vaule
 */
function visiomess_get_request( $method, $variable, $type, $wlist, $nullok ) {
  // error message
  $errmes = 'invalid request'.(VSS_DEBUG_MODE ? ' $_'.strtoupper( $method ).'[\''.$variable.'\']' : '' );
  // get parameter
  $value = null;
  if ( $method == 'post' ) {
    if ( isset( $_POST[$variable] ) ) {
      $value = $_POST[$variable];
    }
  } else if ( $method == 'get' ) {
    if ( isset( $_GET[$variable] ) ) {
      $value = $_GET[$variable];
    }
  } else if ( $method == 'both' ) {
    if ( isset( $_GET[$variable] ) ) {
      $value = $_GET[$variable];
    } else if ( isset( $_POST[$variable] ) ) {
      $value = $_POST[$variable];
    }
  }
  if ( is_null( $value ) ) {
    if ( ! $nullok ) {
      die( $errmes.( VSS_DEBUG_MODE ? ' is null' : '' ) );
    }
  } else {
    switch ( $type ) {
    case 's':
      $myts =& MyTextSanitizer::getInstance();
      $value = $myts->stripSlashesGPC( $value );
      break;
    case 'i':
      $value = intval( $value );
      break;
    case 'f':
      $value = floatval( $value );
      break;
    }
    if ( ! is_null( $wlist ) && ! in_array( $value, $wlist ) ) {
      die( $errmes.( VSS_DEBUG_MODE ? '=\''.$value.'\' is not included in white list ('.implode(',',$wlist).').' : '' ) );
    }
  }
  return $value;
}

function visiomess_get_uname() {
  // get user name
  global $xoopsUser;
  $uname = !empty( $xoopsUser ) ? $xoopsUser->getVar( 'uname', 's' ) : 'anonymous';
  return $uname;
}

function visiomess_is_number( $text ) {
  $re_num = '[-+]?(?:\d+(\.\d*)?|(\.\d+))([eE][-+]?\d+)?';
  $re = '/^'.$re_num.'$/';
  return ( preg_match ( $re, $text ) ? true : false ); 
}

function visiomess_init_template( &$tpl ) {
  global $visiomess_common;
  $myts =& MyTextSanitizer::getInstance();

  // common variables
  $common_vars = array( 'mydirname', 'mod_url', 'mod_path', 'subdir', 'page', 'uname' );
  foreach ( $common_vars as $var ) {
    $tpl->assign( $var, $visiomess_common[$var] );
  }
  // visiome platform link
  $url_file = VSS_CONTENTS_PATH.'/'.$visiomess_common['subdir'].'/Visiome.URL';
  if ( file_exists( $url_file ) ) {
    $_url = file_get_contents( $url_file );
    if ( preg_match( '/^URL=(.+)$/m', $_url, $matches ) ) {
      $url = trim( $matches[1] );
      $tpl->assign( 'pf_url', $myts->htmlSpecialChars( $url ) );
    }
  }
  // css
  $xoonips_module_header = '<link rel="stylesheet" type="text/css" href="'.VSS_CSS_URL.'"/>';
  $xoonips_module_header .= $tpl->get_template_vars('xoops_module_header');
  $tpl->assign( 'xoops_module_header', $xoonips_module_header );
}

function visiomess_convert_link( $text ) {
  // patterns
  $_numalpha = '[a-zA-Z0-9]';
  $_hex = '[a-fA-F0-9]';
  $_escape = '%'.$_hex.'{2}';
  $_safe = '[\$\-_\.+]';
  $_extra = '[!\*\'\(\),]';
  // $_unreserved = '('.$_numalpha.'|'.$_safe.'|'.$_extra.')';
  $_unreserved = '('.$_numalpha.'|'.$_safe.')';
  $_uchar = '('.$_unreserved.'|'.$_escape.')';
  $_hsegment = '('.$_uchar.'|[;:@&=])*';
  $_search = '('.$_uchar.'|[;:@&=])*';
  $_hpath = '~?'.$_hsegment.'(\/'.$_hsegment.')*';
  $_domain = '('.$_numalpha.'+([\.\-]'.$_numalpha.'+)*)+\\.[a-zA-Z]{2,}';
  $_hostport = $_domain.'(:[0-9]+)?';

  $patterns = array();
  // email
  $patterns[] = '/[a-zA-Z0-9]+([_\\.\-][a-zA-Z0-9]+)*@'.$_domain.'/e';
  $replaces[] = '_visiomess_make_javascript( \'<a href="mailto:\0">\0</a>\' )';
  // url
  $patterns[] = '/(http|https|ftp):\/\/'.$_hostport.'(\/'.$_hpath.'(\?'.$_search.')?)?/';
  $replaces[] = '<a href="\0" target="_blank">\0</a>';
  // 
  $text = preg_replace( $patterns, $replaces, $text );
  return $text;
}

function _visiomess_make_javascript( $text ) {
  $chars = unpack( 'C*', $text );
  $code  = '<script type="text/javascript"><!--'."\n";
  $code .= 'document.write(String.fromCharCode(';
  $first = true;
  foreach( $chars as $k ) {
    if ( $first ) {
      $first = false;
    } else {
      $code .= ',';
    }
    $code .= $k;
  }
  $code .= '));'."\n";
  $code .= '//--></script>';
  return $code;
}

function &visiomess_get_pattemplate( $ctime=null, $action=null ) {
  global $visiomess_common;
  if ( is_null( $visiomess_common['action'] ) ) {
    $ret = false;
    return $ret;
  }
  require_once VSS_CLASS_PATH.'/pattemplate.class.php';
  $template_basedir = VSS_CONTENTS_PATH;
  $common_basedir = 'common/templates';
  $contents_basedir = $visiomess_common['subdir'].'/templates';

  if ( is_null( $action ) ) {
    $action = $visiomess_common['action'];
  }
  // header
  $hfname = $visiomess_common['page'].'.header.tmpl.html';
  if ( file_exists( $template_basedir.'/'.$contents_basedir.'/'.$hfname ) ) {
    $template_hfname = $contents_basedir.'/'.$hfname;
  } else {
    $template_hfname = $common_basedir.'/common.header.tmpl.html';
  }
  // main
  $fname = $visiomess_common['page'].'_'.$action.'.tmpl.html';
  if ( file_exists( $template_basedir.'/'.$contents_basedir.'/'.$fname ) ) {
    $template_fname = $contents_basedir.'/'.$fname;
  } else {
    $template_fname = $common_basedir.'/common_'.$action.'.tmpl.html';
  }
  // footer
  $ffname = $visiomess_common['page'].'.footer.tmpl.html';
  if ( file_exists( $template_basedir.'/'.$contents_basedir.'/'.$ffname ) ) {
    $template_ffname = $contents_basedir.'/'.$ffname;
  } else {
    $template_ffname = $common_basedir.'/common.footer.tmpl.html';
  }

  $tmpl = new PatTemplate();
  $tmpl->setBaseDir( $template_basedir );
  $tmpl->readTemplatesFromFile( $template_hfname );
  $tmpl->readTemplatesFromFile( $template_fname );
  $tmpl->readTemplatesFromFile( $template_ffname );
  // $tmpl->addTemplate( 'header', $template_hfname );
  // $tmpl->addTemplate( 'main', $template_fname );
  // $tmpl->addTemplate( 'footer', $template_ffname );

  // assign global template variables
  $vars = array( 'uname', 'mydirname', 'mod_url', 'mod_path', 'subdir', 'page', 'action' );
  $img = 'images/image.php?s='.$visiomess_common['subdir'];
  foreach( $vars as $var ) {
    $name = 'VSS_COMMON_'.strtoupper( $var );
    $tmpl->addGlobalVar( $name, $visiomess_common[$var] );
  }
  if ( ! is_null( $ctime ) ) {
    $tmpl->addGlobalVar( 'VSS_IMAGE_RESULT', $img.'&amp;t=r&amp;d='.$ctime.'&amp;f=' );
    $tmpl->addGlobalVar( 'VSS_IMAGE_RESULT_JS', $img.'&t=r&d='.$ctime.'&f=' );
  }
  $tmpl->addGlobalVar( 'VSS_IMAGE_DATA', $img.'&amp;t=d&amp;f=' );
  $tmpl->addGlobalVar( 'VSS_IMAGE_DATA_JS', $img.'&t=d&f=' );

  return $tmpl;
}


?>
