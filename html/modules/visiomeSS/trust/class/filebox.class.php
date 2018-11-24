<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

/**
 * temporary data directories handling class
 *
 * @package visiomess
 * @copyright copyright &copy; 2008 RIKEN Japan
 */
class VisiomeSS_FileBox {

  /**
   * user name
   * @access private
   * @var string
   */
  var $uname = '';

  /**
   * sub directory name of each contents
   * @access private
   * @var string
   */
  var $subdir = '';

  /**
   * place holder of each working directory name
   * @access private
   * @var array(string)
   */
  var $file_box = array();

  /**
   * constructor
   *
   * @access public
   */
  function VisiomeSS_FileBox() {
    global $visiomess_common;
    $this->uname = $visiomess_common['uname'];
    $this->subdir = $visiomess_common['subdir'];
    $this->_initialize();
    $this->_gc_results();
  }

  /**
   * get object instance
   *
   * @access public
   * @return object
   */
  function &getInstance() {
    static $instance = null;
    if ( is_null( $instance ) ) {
      $instance = new VisiomeSS_FileBox();
    }
    return $instance;
  }

  /**
   * move working file to result directory
   *
   * @access public
   * @param string $fname file name of working and result directory
   * @param int $time start time of simulation
   */
  function move_file_work2result( $fname, $time ) {
    $from_path = $this->file_box['wbox'].'/'.$fname;
    $to_path = $this->file_box['cbox'].'/'.$time.'/'.basename( $fname );
    if ( ! @rename(  $from_path, $to_path ) ) {
      die( 'failed to move file'.( VSS_DEBUG_MODE ? ' path('.$to_path.','.$from_path.')' : '') );
    }
  }

  /**
   * copy file from data to working directory
   *
   * @access public
   * @param string $fname file name of data and working directory
   * @param bool $is_override true if override existing file
   */
  function copy_file_data2work( $fname, $is_override ) {
    $from_path = $this->file_box['dbox'].'/'.$fname;
    $to_path = $this->file_box['wbox'].'/'.$fname;
    if ( ! file_exists( $to_path ) || $is_override ) {
      if ( ! @copy(  $from_path, $to_path ) ) {
        die( 'failed to copy file'.( VSS_DEBUG_MODE ? ' path('.$to_path.','.$from_path.')' : '') );
      }
    }
  }

  /**
   * write simulation results to result file
   *
   * @access public
   * @param int $ctime start time of simulation
   * @param string $fname file name of result directory
   * @param string $body file body of result file
   * @return bool false if failure
   */
  function write_result( $ctime, $fname, $body ) {
    $fpath = $this->file_box['cbox'].'/'.$ctime.'/'.$fname;
    $fp = fopen( $fpath, 'w' );
    if ( $fp === false ) {
      die( 'failed to open file'.( VSS_DEBUG_MODE ? ' path('.$fpath.')' : '' ) );
    }
    fwrite( $fp, $body );
    fclose( $fp );
    return true;
  }

  /**
   * save working file
   *
   * @access public
   * @param string $fname file name of working directory
   * @param string $body file contents of working file
   * @return bool false if failure
   */
  function save_file( $fname, $body ) {
    $fpath = $this->file_box['wbox'].'/'.$fname;
    $fp = fopen( $fpath, 'w' );
    if ( $fp === false ) {
      die( 'failed to open file'.( VSS_DEBUG_MODE ? ' path('.$fpath.')' : '' ) );
    }
    fwrite( $fp, $body );
    fclose( $fp );
    return true;
  }

  /**
   * read result file contents
   *
   * @access public
   * @param string $ctime start time of simulation
   * @param string $fname file name of $box directory
   * @return string file contents
   */
  function read_result( $ctime, $fname ) {
    $fpath = $this->file_box['cbox'].'/'.$ctime.'/'.$fname;
    if ( ! is_file( $fpath ) || ! is_readable( $fpath ) ) {
      die( 'file not found'.( VSS_DEBUG_MODE ? ' path('.$fpath.')' : '' ) );
    }
    return file_get_contents( $fpath );
  }

  /**
   * load file contents of data or working directory
   *
   * @access public
   * @param string $fname file name of data or working directory
   * @param bool $is_databox true load file from data direcotry
   * @return string file contents
   */
  function load_file( $fname, $is_databox ) {
    $box = $is_databox ? 'dbox' : 'wbox';
    $fpath = $this->file_box[$box].'/'.$fname;
    if ( ! is_file( $fpath ) || ! is_readable( $fpath ) ) {
      die( 'file not found'.( VSS_DEBUG_MODE ? ' path('.$fpath.')' : '' ) );
    }
    return file_get_contents( $fpath );
  }

  /**
   * run native program
   *
   * @access public
   * @param string $cmd command
   * @param bool $is_databox true if $cmd exists in data directory
   * @return array running time
   */
  function run_program( $cmd, $is_databox ) {
    if ( is_null( $is_databox ) ) {
      $cmd = $cmd.' > /dev/null';
    } else {
      $box = $is_databox ? 'dbox' : 'wbox';
      $cmd = $this->file_box[$box].'/'.$cmd.' > /dev/null';
    }
    return $this->_run( $cmd, true );
  }

  /**
   * run user defined function
   *
   * @access public
   * @param string $func name of function
   * @return array running time
   */
  function run_function( $func ) {
    return $this->_run( $func, false );
  }

  /**
   * get physical file path
   *
   * @access public
   * @param string $box type of directory
   *   'dbox' : data directory
   *   'wbox' : working directory
   *   'cbox' : prefix of results directory, usally to use result dirctoy as
   *            $cbox.'/'.$ctime.
   * @param string $fname file name
   * @return string file path
   */
  function get_path( $box, $fname ) {
    if ( empty( $fname ) ) {
      return $this->file_box[$box];
    }
    $fpath = is_array( $fname ) ? implode( '/', $fname ) : $fname;
    return $this->file_box[$box].'/'.$fpath;
  }

  /**
   * create result directory, this method will called from task manager class
   *
   * @access public
   * @param int $ctime start time of simulation
   * @return string created directory path
   */
  function make_result_path( $ctime ) {
    $res = $this->file_box['cbox'].'/'.$ctime;
    $this->_make_filebox( $res );
    return $res;
  }

  /**
   * get list of simulation result directories
   *
   * @access public
   * @param string $rtype type of result
   * @return array list of simulation result directories
   */
  function get_result_path( $rtype = '' ) {
    $results = array();
    $cbox = $this->file_box['cbox'];
    $hdl = opendir( $cbox );
    if ( $hdl === false ) {
      die( 'failed to open directory handle' );
    }
    while ( ( $dname = readdir( $hdl ) ) !== false ) {
      if ( preg_match( '/^\d+$/', $dname ) ) {
        $list_ok = false;
        if ( $rtype == '' ) {
          $list_ok = true;
        } else if ( file_exists( $cbox.'/'.$dname.'/result.type' ) ) {
          $rtype_tmp = trim( file_get_contents( $cbox.'/'.$dname.'/result.type' ) );
          if ( $rtype == $rtype_tmp ) {
            $list_ok = true;
          }
        }
        if ( $list_ok ) {
          $results[intval($dname)] = array(
            'label' => date( DATE_RFC822, intval( $dname ) ),
            'value' => $dname,
            'path' => $this->file_box['cbox'].'/'.$dname,
          );
        }
      }
    }
    closedir( $hdl );
    if ( ! empty( $results ) ) {
      krsort( $results );
    }
    return $results;
  }

  /**
   * initialize file box
   *
   * @access private
   */
  function _initialize() {
    $bbox = VSS_FILEBOX_PATH;
    $ubox = $bbox.'/'.$this->uname;
    $cbox = $ubox.'/'.$this->subdir;
    $wbox = $cbox.'/'.VSS_FILEBOX_WORKNAME;
    $dbox = VSS_CONTENTS_PATH.'/'.$this->subdir.'/data';
    foreach ( array( $bbox, $ubox, $cbox, $wbox ) as $fbox ) {
      $this->_make_filebox( $fbox );
    }
    $this->file_box = array(
      'bbox' => $bbox,
      'ubox' => $ubox,
      'cbox' => $cbox,
      'wbox' => $wbox,
      'dbox' => $dbox,
    );
  }

  /**
   * garbage collect simulation results
   *
   * @access private
   */
  function _gc_results() {
    $hdl = opendir( $this->file_box['cbox'] );
    if ( $hdl === false ) {
      die( 'failed to open directory handle' );
    }
    while ( ( $dname = readdir( $hdl ) ) !== false ) {
      if ( preg_match( '/^\d+$/', $dname ) ) {
        $old = intval( $dname );
        $now = time();
        if ( $now > $old + VSS_GC_MAXLIFETIME ) {
          system( 'rm -rf '.$this->file_box['cbox'].'/'.$dname );
        }
      }
    }
    closedir( $hdl );
  }

  /**
   * create woking directory
   *
   * @access private
   * @param string $path creating directory path
   */
  function _make_filebox( $path ) {
    if ( file_exists( $path ) ) {
      if ( ! is_dir( $path ) || ! is_writable( $path ) ) {
        die( 'invalid attribute of filebox'.( VSS_DEBUG_MODE ? ' path('.$path.')' : '' ) );
      }
    } else {
      // try to create content file box
      if ( ! @mkdir( $path, 0755 ) ) {
        die( 'failed to create filebox'.( VSS_DEBUG_MODE ? ' path('.$path.')' : '' ) );
      }
    }
  }

  /**
   * run simulation and count simulation time
   *
   * @access private
   * @return array simulation time
   */
  function _run( $cmd, $is_command ) {
    $cwd = getcwd();
    chdir( $this->file_box['wbox'] );
    list( $tus, $tms ) = explode( ' ', microtime() );
    if ( $is_command ) {
      system( $cmd );
    } else {
      if ( is_array( $cmd ) ) {
        list( $instance, $method ) = $cmd;
        $instance->$method();
      } else {
        $cmd();
      }
    }
    list( $tue, $tme ) = explode( ' ', microtime() );
    chdir( $cwd );
    $ct = ( (float)$tue + (float)$tme ) - ( (float)$tus + (float)$tms );
    $tms_s = date( DATE_RFC822, $tms );
    $tme_s = date( DATE_RFC822, $tme );
    $ct_s = trim( sprintf( "%12.5f", $ct) );
    return array(
     'value' => array( 'start' => $tms, 'end' => $tme, 'time' => $ct ), 
     'label' => array( 'start' => $tms_s, 'end' => $tme_s, 'time' => $ct_s ),
    );
  }
}

?>
