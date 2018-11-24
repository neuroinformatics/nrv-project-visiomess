<?php

global $visiomess_common;

$visiomess_common['pages'] = array(
  'main' => array(
     'get' => array( 'default' ),
     'post' => array(),
  ),
  'plot1' => array(
     'get' => array( 'default' ),
     'post' => array( 'edit', 'save', 'reset', 'run', 'result' ),
  ),
  'plot2' => array(
     'get' => array( 'default' ),
     'post' => array( 'edit', 'save', 'reset', 'run', 'result' ),
  ),
);

$visiomess_common['breadcrumbs'] = array(
  'main' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme' )
  ),
  'plot1' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme', 'url' => $visiomess_common['mod_url'].'/?s='.$visiomess_common['subdir'] ),
    array( 'name' => 'I-V plot' )
  ),
  'plot2' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme', 'url' => $visiomess_common['mod_url'].'/?s='.$visiomess_common['subdir'] ),
    array( 'name' => 'Current' )
  )
);
 
$visiomess_common['navi'] = array(
  'main' => array(
    array( 'title' => 'I-V plot', 'page' => 'plot1', 'icon' => 'vss' ),
    array( 'title' => 'Current', 'page' => 'plot2', 'icon' => 'vss' )
  ),
  'plot1' => array(),
  'plot2' => array()
);

?>
