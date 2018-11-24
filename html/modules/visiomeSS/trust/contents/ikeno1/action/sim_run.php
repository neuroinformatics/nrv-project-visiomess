<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

// parameter
$params['template'] = array( 'sim.sl', 'hh.mdl' );

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'sim.sl', false );

// result
$taskman->set_result( 'result.ps', true );

$title = 'Run Script';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
