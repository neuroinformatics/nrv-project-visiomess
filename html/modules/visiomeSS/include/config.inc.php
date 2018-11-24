<?php

// configs - this file will be called from common.inc.php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

define( 'VSS_DEBUG_MODE', false );

define( 'VSS_USE_XOOPS_TRUST_PATH', false );
define( 'VSS_SATELLITE_PATH', '/usr' );
define( 'VSS_SATELLITE4_PATH', '/usr/local/satellite4' );
define( 'VSS_GC_MAXLIFETIME', 60*60*24 );

if ( VSS_USE_XOOPS_TRUST_PATH ) {
  if ( ! defined( 'XOOPS_TRUST_PATH' ) ) exit();
  define( 'VSS_TRUST_PATH', XOOPS_TRUST_PATH.'/modules/visiomeSS' );
  define( 'VSS_FILEBOX_PATH', XOOPS_TRUST_PATH.'/data/visiomeSS' );
} else {
  define( 'VSS_TRUST_PATH', XOOPS_ROOT_PATH.'/modules/visiomeSS/trust' );
  define( 'VSS_FILEBOX_PATH', XOOPS_ROOT_PATH.'/modules/visiomeSS/000FileBox' );
}

define( 'VSS_CSS_URL', XOOPS_URL.'/modules/visiomeSS/style.css' );
define( 'VSS_FILEBOX_WORKNAME', 'work' );
define( 'VSS_MENUBLOCK_COOKIE', 'visiomess_menu_block' );

define( 'VSS_INCLUDE_PATH', VSS_TRUST_PATH.'/include' );
define( 'VSS_CLASS_PATH', VSS_TRUST_PATH.'/class' );
define( 'VSS_CONTENTS_PATH', VSS_TRUST_PATH.'/contents' );
// define( 'VSS_MIMEFILE_PATH', VSS_TRUST_PATH.'/etc/magic/magic' );
define( 'VSS_MIMEFILE_PATH', null );

?>
