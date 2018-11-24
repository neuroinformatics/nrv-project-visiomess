<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// parameters
$params['template'] = array( 'ICa.mdl', 'ICa_double_compute.sl', 'ICa_double.sl' );

// command task
$cmd =& $taskman->create_task( 'command' );
$cmd->set_remove( array( 'Ca_doulbe.dat', 'ICa_double.dat', 'ICa_double_stim.dat' ) );
$cmd->set_name( 'clean working directory' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'ICa_double_compute.sl', false );
$satellite->add_tempfile( 'Ca_doulbe.dat' );
$satellite->add_tempfile( 'ICa_double.dat' );
$satellite->add_tempfile( 'ICa_double_stim.dat' );

// result
$taskman->set_result_type( 'ICa' );
$taskman->set_result( 'result.ps', true );

$title = 'Run Script';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
