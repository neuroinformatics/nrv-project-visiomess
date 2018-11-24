<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// command task
$cmd =& $taskman->create_task( 'command' );
$cmd->set_copy( array( 'vc01.out', 'vc02.out', 'vc03.out' ) );
$cmd->set_name( 'copy data file' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'vclamp-area.sl', true );

// result
$taskman->set_result( 'result.ps', true );

$title = 'Run Script';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
