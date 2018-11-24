<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

// parameter
$params['template'] = array( 'param.mdl' );

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// command task
$command =& $taskman->create_task( 'command' );
$command->set_copy( 'FigData.csv' );
$command->set_name( 'copy data file' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'plot.sl', true );

// result
$taskman->set_result( 'result.ps', true );

$title = 'Plot Data';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
