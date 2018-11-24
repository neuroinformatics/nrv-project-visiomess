<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// make task
$make =& $taskman->create_task( 'make' );
$make->set_target( 'NeoOccl' );
$make->add_source( 'NeoOccl.c' );
$make->set_name( 'compile Neocognitron' );

// command task
$cmd =& $taskman->create_task( 'command' );
$cmd->set_copy( array( 'Header.dat', 'PatLearn.dat', 'PatMask.dat', 'PatTest.dat' ) );
$cmd->set_command( './NeoOccl' );
$cmd->add_tempfile( 'connect.dat' );
$cmd->set_name( 'run Neocognitron' );

// result
for ( $i = 0; $i < 4; $i++ ) {
  for ( $j = 0; $j < 10; $j++ ) {
    $taskman->set_result( sprintf( 'out0%d%d.eps', $j, $i ), true );
  }
}

$title = 'Run Program';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
