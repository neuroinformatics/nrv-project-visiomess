<?php

global $visiomess_common;

$visiomess_common['pages'] = array(
  'main' => array(
     'get' => array( 'default' ),
     'post' => array(),
  ),
  'plot' => array(
     'get' => array( 'default' ),
     'post' => array( 'run', 'result' ),
  ),
);

$visiomess_common['breadcrumbs'] = array(
  'main' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme' )
  ),
  'plot' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme', 'url' => $visiomess_common['mod_url'].'/?s='.$visiomess_common['subdir'] ),
    array( 'name' => 'Plot' )
  )
);
 
$visiomess_common['navi'] = array(
  'main' => array(
    array( 'title' => '', 'page' => 'plot', 'icon' => 'vss' )
  ),
  'plot' => array()
);


?>
