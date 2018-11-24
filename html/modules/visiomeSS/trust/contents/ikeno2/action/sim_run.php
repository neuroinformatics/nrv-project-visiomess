<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

define( 'DISLIN_CFLAGS', '-I/usr/local/dislin' );
define( 'DISLIN_LIBS', '-ldislin' );

$visiomess_common['filebox']->copy_file_data2work( 'beeVision.conf', false );

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();

// make task
$make =& $taskman->create_task( 'make' );
$make->set_target( 'beeVision' );
$make->add_source( array( 'beeVision.c', 'figure.c', 'init.c', 'output.c' ) );
$make->add_cflag( DISLIN_CFLAGS );
$make->add_lib( DISLIN_LIBS );
$make->set_name( 'make beeVision' );

// command task
$cmd =& $taskman->create_task( 'command' );
$cmd->set_copy( array( '0304324.pgm', '0304325m.pgm', 'r0300165.pgm' ) );
$cmd->set_mkdir( array( 'TIFF', 'Results', 'Responses' ) );
$cmd->set_command( './beeVision -n 0 -plot' );
$cmd->set_name( 'run beeVision' );

// result
$results = array(
 'TIFF/bothEyeXZ.tif', 'TIFF/bothEyeYZ.tif', 'TIFF/greyBothEyeXZ.tif',
 'TIFF/greyLeftEyeXZ.tif', 'TIFF/greyRightEyeXZ.tif', 'TIFF/leftEyeXZ.tif',
 'TIFF/rightEyeXZ.tif',
);
$taskman->set_result( $results, true );
$taskman->set_result( 'beeVision.conf', false );

$title = 'Run Program';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
