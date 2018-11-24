<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

require_once dirname( __FILE__ ).'/task_satellite.class.php';

class VisiomeSS_Task_Satellite4 extends VisiomeSS_Task_Satellite {

  function VisiomeSS_Task_Satellite4() {
    parent::VisiomeSS_Task_Satellite();
  }

  function run() {
    $this->_make_satellite_setup();
    $this->_make_satellite_output();
    $scripts = '';
    foreach ( $this->srcs as $src ) {
      $scripts .= ' '.$this->_filebox->get_path( $src['path'], $src['file'] );
    }
    $cmd = VSS_SATELLITE4_PATH.'/bin/sl4 -setup -clean cgisetup.sl '.$scripts.' output.sl';
    return $this->_do_command( $cmd, $this->_time );
  }

  function _make_satellite_setup() {
    // create cgisetup.sl
    $script = '';
    $sl_modules = array(
      'BUILTIN' => array(
        'ini' => 'builtin.ini',
      ),
      'SYSTEM' => array(
        'dll' => 'mod_system.so',
        'ini' => 'system.ini',
      ),
      'ISPP' => array(
        'dll' => 'mod_ispp.so',
        'ini' => 'ispp.ini',
      ),
      'BPS' => array(
        'dll' => 'mod_bps.so',
        'ini' => 'bps.ini',
      ),
      'NCS' => array(
        'dll' => 'mod_ncs.so',
        'ini' => 'ncs.ini',
      ),
      'NPE' => array(
        'dll' => 'mod_npe.so',
        'ini' => 'npe.ini',
      ),
      'GPM' => array(
        'dll' => 'mod_gpm.so',
        'ini' => 'gpm.ini',
      ),
      'DCM' => array(
        'dll' => 'mod_dcm.so',
        'ini' => 'dcm.ini',
      ),
      'UTILITY' => array(
        'dll' => 'mod_slutil.so',
        'ini' => 'slutil.ini',
        'sl' => 'slutil/slutil.sl',
      ),
      'STATISTICS' => array(
        'ini' => 'statistics.ini',
        'sl' => 'statistics/statistics.sl',
      )
    );
    foreach ( $sl_modules as $name => $sl_module ) {
      $script .= sprintf( '# %s', $name )."\n";
      $script .= sprintf( 'define %s {', $name )."\n";
      if ( isset( $sl_module['dll'] ) ) {
        $script .= sprintf( 'set Module_Dll sl4vars("moduledir") + "/%s";', $sl_module['dll'] )."\n";
      }
      if ( isset( $sl_module['ini'] ) ) {
        $script .= sprintf( 'set Module_Ini sl4vars("systemrcdir") + "/%s";', $sl_module['ini'] )."\n";
      }
      if ( isset( $sl_module['sl'] ) ) {
        $script .= sprintf( 'set Module_Scr sl4vars("sharedir") + "/%s";', $sl_module['sl'] )."\n";
      }
      $script .= sprintf( '}' )."\n";
      $script .= sprintf( 'module(%s);', $name )."\n";
    }
    $this->_filebox->save_file( 'cgisetup.sl', $script );
  }

  function _make_satellite_output() {
    // create output.sl
    $script = 'system( "/bin/sh -c \\"'.VSS_SATELLITE_PATH.'/bin/gpm2ps -cps > result.ps; \\"");'."\n";
    $this->_filebox->save_file( 'output.sl', $script );
  }

}


?>
