<?php

global $visiomess_common;

$visiomess_common['pages'] = array(
  'main' => array(
     'get' => array( 'default' ),
     'post' => array(),
  ),
  'sim' => array(
     'get' => array( 'default' ),
     'post' => array( 'run', 'view', 'reset', 'result', 'emclay', 'emhh', 'esclay', 'eshh', 'eshhclay', 'smclay', 'smhh', 'ssclay', 'sshh', 'sshhclay' ),
  ),
);

$visiomess_common['breadcrumbs'] = array(
  'main' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme' ),
  ),
  'sim' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme', 'url' => $visiomess_common['mod_url'].'/?s='.$visiomess_common['subdir'] ),
    array( 'name' => 'Simulation' ),
  )
);
 
$visiomess_common['navi'] = array(
  'main' => array(
    array( 'title' => '', 'page' => 'sim', 'icon' => 'vss' ),
  ),
  'sim' => array()
);

?>
