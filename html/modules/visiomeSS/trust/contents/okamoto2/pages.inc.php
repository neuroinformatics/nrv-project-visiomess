<?php

global $visiomess_common;

$visiomess_common['pages'] = array(
  'main' => array(
     'get' => array( 'default', 'applet' ),
     'post' => array(),
  ),
  'original' => array(
     'get' => array( 'default' ),
     'post' => array(),
  ),
  'hough' => array(
     'get' => array( 'default' ),
     'post' => array(),
  ),
  'velocity' => array(
     'get' => array( 'default' ),
     'post' => array(),
  ),
);

$visiomess_common['breadcrumbs'] = array(
  'main' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme' )
  ),
  'original' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme', 'url' => $visiomess_common['mod_url'].'/?s='.$visiomess_common['subdir'] ),
    array( 'name' => 'Origial Hough Transform' )
  ),
  'hough' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme', 'url' => $visiomess_common['mod_url'].'/?s='.$visiomess_common['subdir'] ),
    array( 'name' => 'Hough Transform' )
  ),
  'velocity' => array(
    array( 'name' => 'Index', 'url' => $visiomess_common['mod_url'].'/' ),
    array( 'name' => 'Readme', 'url' => $visiomess_common['mod_url'].'/?s='.$visiomess_common['subdir'] ),
    array( 'name' => 'Local Velocity Detection' )
  )
);

$visiomess_common['navi'] = array(
  'main' => array(),
  'original' => array(),
  'hough' => array(),
  'velocity' => array()
);

?>
