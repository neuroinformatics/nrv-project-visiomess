<?php

class VisiomeSS_Task_Command extends VisiomeSS_Task {

  var $_commands = array();

  function VisiomeSS_Task_Command() {
    parent::VisiomeSS_Task();
    $this->set_name( 'run simulator' );
  }

  function set_remove( $fname ) {
    if ( is_array( $fname ) ) {
      foreach( $fname as $f ) {
        $this->_commands[] = array( 'type' => 'remove', 'file' => $f );
      }
    } else {
      $this->_commands[] = array( 'type' => 'remove', 'file' => $fname );
    }
  }

  function set_remove_r( $dname ) {
    if ( is_array( $dname ) ) {
      foreach( $dname as $d ) {
        $this->_commands[] = array( 'type' => 'remove_r', 'file' => $d );
      }
    } else {
      $this->_commands[] = array( 'type' => 'remove_r', 'file' => $dname );
    }
  }

  function set_copy( $fname ) {
    if ( is_array( $fname ) ) {
      foreach( $fname as $f ) {
        $this->_commands[] = array( 'type' => 'copy', 'file' => $f );
        $this->add_tempfile( $f );
      }
    } else {
      $this->_commands[] = array( 'type' => 'copy', 'file' => $fname );
      $this->add_tempfile( $fname );
    }
  }

  function set_copy_r( $dname ) {
    if ( is_array( $dname ) ) {
      foreach( $dname as $d ) {
        $this->_commands[] = array( 'type' => 'copy_r', 'file' => $d );
        $this->add_tempfile( $d );
      }
    } else {
      $this->_commands[] = array( 'type' => 'copy_r', 'file' => $dname );
      $this->add_tempfile( $dname );
    }
  }

  function set_mkdir( $dname ) {
    if ( is_array( $dname ) ) {
      foreach( $dname as $d ) {
        $this->_commands[] = array( 'type' => 'mkdir', 'file' => $d );
        $this->add_tempfile( $d );
      }
    } else {
      $this->_commands[] = array( 'type' => 'mkdir', 'file' => $dname );
      $this->add_tempfile( $dname );
    }
  }

  function set_command( $cmd ) {
    if ( is_array( $cmd ) ) {
      foreach( $cmd as $c ) {
        $this->_commands[] = array( 'type' => 'command', 'file' => $c );
      }
    } else {
      $this->_commands[] = array( 'type' => 'command', 'file' => $cmd );
    }
  }

  function run() {
    $this->_error = '';
    $this->_output = '';
    $mytime_total = array();
    $mytime = array();
    foreach ( $this->_commands as $cmd ) {
      switch( $cmd['type'] ) {
      case 'command':
        $ret = $this->_do_command( $cmd['file'], $mytime );
        break;
      case 'remove':
        $wpath = $this->_wbox.'/'.$cmd['file'];
        $c = 'rm -f '.$wpath;
        $ret = $this->_do_command( $c, $mytime );
        break;
      case 'remove_r':
        $wpath = $this->_wbox.'/'.$cmd['file'];
        $c = 'rm -rf '.$wpath;
        $ret = $this->_do_command( $c, $mytime );
        break;
      case 'copy':
        $dpath = $this->_dbox.'/'.$cmd['file'];
        $wpath = $this->_wbox.'/'.$cmd['file'];
        $c = 'cp '.$dpath.' '.$wpath;
        $ret = $this->_do_command( $c, $mytime );
        break;
      case 'copy_r':
        $dpath = $this->_dbox.'/'.$cmd['file'];
        $wpath = $this->_wbox.'/'.$cmd['file'];
        $c = 'cp -R '.$dpath.' '.$wpath;
        $ret = $this->_do_command( $c, $mytime );
        break;
      case 'mkdir':
        $wpath = $this->_wbox.'/'.$cmd['file'];
        $c = 'mkdir '.$wpath;
        $ret = $this->_do_command( $c, $mytime );
        break;
      }
      if ( ! $ret ) {
        return false;
      }
      $mytime_total = $this->_merge_time( $mytime_total, $mytime );
    }
    $this->_time = $mytime_total;
    return true;
  }

  function clean() {
    $this->_error = '';
    $this->_output = '';
    return parent::clean();
  }

}
