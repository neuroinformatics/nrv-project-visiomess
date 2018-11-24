<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// command task
$command =& $taskman->create_task( 'command' );
$command->set_copy( array( 'Fig3C1.csv', 'Fig3C2.csv', 'Fig9A1.csv', 'Fig9A2.csv' ) );
$command->set_name( 'copy data file' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'plot.sl', true );

// result
$taskman->set_result( 'result.ps', true );

$title = 'Plot Data';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
