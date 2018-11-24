<?php

require_once dirname( __FILE__ ).'/../../../mainfile.php';
require_once dirname( __FILE__ ).'/config.inc.php';

$mydirname = basename( dirname( dirname( __FILE__ ) ) );
$mod_url = XOOPS_URL.'/modules/'.$mydirname;
$mod_path = XOOPS_ROOT_PATH.'/modules/'.$mydirname;

require_once VSS_INCLUDE_PATH.'/common.inc.php';

?>
