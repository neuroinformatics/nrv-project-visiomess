<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

// parameters
$params['template'] = array( 'param2.mdl' );

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// command task
$command =& $taskman->create_task( 'command' );
$command->set_copy( 'ex_data2.csv' );
$command->set_name( 'copy data file' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'plotData2.sl', true );

// result
$taskman->set_result( 'result.ps', true );

$title = 'Plot Data';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
