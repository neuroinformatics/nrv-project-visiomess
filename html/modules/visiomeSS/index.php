<?php

require_once 'include/common.inc.php';

if ( ! is_null( $visiomess_common['subdir'] ) ) {
  if ( is_null( $visiomess_common['page'] ) || is_null( $visiomess_common['action'] ) ) {
    die( 'illegal request' );
  }
  $page_path = VSS_CONTENTS_PATH.'/'.$visiomess_common['subdir'].'/action/'.$visiomess_common['page'].'_'.$visiomess_common['action'].'.php';
  if ( ! file_exists( $page_path ) || ! is_readable( $page_path ) ) {
    die( 'page not found'.( VSS_DEBUG_MODE ? ' path('.$page_path.')' : '' ) );
  }
  // load filebox class file
  require_once VSS_CLASS_PATH.'/filebox.class.php';
  $visiomess_common['filebox'] =& VisiomeSS_FileBox::getInstance();
  // load action file
  include $page_path;
  exit();
}

// default page
$xoopsOption['template_main'] = 'visiomess_main.html';
include XOOPS_ROOT_PATH.'/header.php';

visiomess_init_template( $xoopsTpl, $visiomess_common );

include XOOPS_ROOT_PATH.'/footer.php';

?>
