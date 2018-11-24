<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

class VisiomeSS_Task_Satellite extends VisiomeSS_Task {

  var $srcs = array();

  function VisiomeSS_Task_Satellite() {
    parent::VisiomeSS_Task();
    $this->set_name( 'execution of SATELLITE script' );
    $this->add_tempfile( 'cgisetup.sl' );
    $this->add_tempfile( 'output.sl' );
    $this->add_tempfile( 'result.ps' );
    $this->add_tempfile( 'GPMDVIFILE1' );
  }

  function add_script( $src, $is_databox=true ) {
    $path = $is_databox ? 'dbox' : 'wbox';
    if ( is_array( $src ) ) {
      foreach ( $src as $s ) {
        $this->srcs[] = array( 'file' => $s, 'path' => $path );
      }
    } else {
      $this->srcs[] = array( 'file' => $src, 'path' => $path );
    }
  }

  function run() {
    $this->_make_satellite_setup();
    $this->_make_satellite_output();
    $scripts = '';
    foreach ( $this->srcs as $src ) {
      $scripts .= ' '.$this->_filebox->get_path( $src['path'], $src['file'] );
    }
    $cmd = VSS_SATELLITE_PATH.'/bin/sl -setup -clean cgisetup.sl '.$scripts.' output.sl';
    return $this->_do_command( $cmd, $this->_time );
  }

  function clean() {
    $this->_error = '';
    $this->_output = '';
    return parent::clean();
  }

  function _make_satellite_setup() {
    // create cgisetup.sl
    $sl_modules = array( 'SYSTEM', 'GPM', 'ISPP', 'BPS', 'NCS', 'NPE', 'DCM' );
    $sl_scripts = array( 'builtin.sl', 'slutil.sl' );
    $script = '';
    foreach ( $sl_modules as $sl_module ) {
      $script .= 'module('.$sl_module.');'."\n";
    }
    foreach ( $sl_scripts as $sl_script ) {
      $script .= 'inline("'.VSS_SATELLITE_PATH.'/libexec/satellite/util/'.$sl_script.'");'."\n";
    }
    $this->_filebox->save_file( 'cgisetup.sl', $script );
  }

  function _make_satellite_output() {
    // create output.sl
    $script = VSS_SATELLITE_PATH.'/bin/gpm2ps -cps > result.ps;'."\n";
    $this->_filebox->save_file( 'output.sl', $script );
  }

}


?>
