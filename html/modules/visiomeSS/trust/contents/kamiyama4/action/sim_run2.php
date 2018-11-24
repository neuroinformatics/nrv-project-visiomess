<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

$data_files = array();
$data_files[] = 'det-DC.out';
$data_files[] = 'det-noise.out';
for ( $i = 0; $i < 2; $i++ ) {
  for ( $j = 0; $j < 10; $j++ ) {
    $data_files[] = 'cc'.$i.$j.'.out';
    $data_files[] = 'dc'.$i.$j.'.out';
  }
}

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// command task
$cmd =& $taskman->create_task( 'command' );
$cmd->set_copy( $data_files );
$cmd->set_name( 'copy data file' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'cc-noise.sl', true );

// result
$taskman->set_result( 'result.ps', true );

$title = 'Run Script';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
