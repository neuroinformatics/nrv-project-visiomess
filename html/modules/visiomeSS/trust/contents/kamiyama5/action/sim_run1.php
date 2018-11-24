<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

require_once VSS_CLASS_PATH.'/taskmanager.class.php';
$taskman = new VisiomeSS_TaskManager();


// parameters
$params['template'] = array( 'fishHC.mdl', 'Glu_resp_compute.sl', 'Glu_resp.sl' );

// satellite task
$satellite =& $taskman->create_task( 'satellite' );
$satellite->add_script( 'Glu_resp_compute.sl', false );
$satellite->add_tempfile( 'control_Ca.dat' );
$satellite->add_tempfile( 'control_V.dat' );
$satellite->add_tempfile( 'withoutSB_Ca.dat' );
$satellite->add_tempfile( 'withoutSB_V.dat' );

// result
$taskman->set_result_type( 'Glu_resp' );
$taskman->set_result( 'result.ps', true );

$title = 'Run Script';
include VSS_CONTENTS_PATH.'/common/action/common_run.inc.php';

?>
