<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

$visiomess_common['filebox']->copy_file_data2work( 'beeVision.conf', true );

$tmpl =& visiomess_get_pattemplate();

include VSS_CONTENTS_PATH.'/common/action/common.inc.php';

?>
