<?php

global $visiomess_common;

$visiomess_common['pages'] = array(
  'main' => array(
     'get' => array( 'default' ),
     'post' => array(),
  ),
  'sim' => array(
     'get' => array( 'default' ),
     'post' => array( 'run1', 'view1', 'emodel1', 'esl1', 'esl1c', 'smodel1', 'ssl1', 'ssl1c', 'reset1', 'run2', 'view2', 'emodel2', 'esl2', 'esl2c', 'smodel2', 'ssl2', 'ssl2c', 'reset2', 'result' )
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
