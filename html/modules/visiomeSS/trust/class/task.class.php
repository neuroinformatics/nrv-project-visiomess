<?php

class VisiomeSS_Task {
  var $_taskname;
  var $_filebox;
  var $_cbox;
  var $_wbox;
  var $_dbox;
  var $_output;
  var $_error;
  var $_tempfiles;
  var $_time;

  /**
   * constructor, this function will be called from constructor of 
   * extended classes.
   *
   * @access protected
   **/
  function VisiomeSS_Task() {
    $this->_taskname = '';
    $this->_filebox =& VisiomeSS_FileBox::getInstance();
    $this->_cbox = $this->_filebox->get_path( 'cbox', null );
    $this->_wbox = $this->_filebox->get_path( 'wbox', null );
    $this->_dbox = $this->_filebox->get_path( 'dbox', null );
    $this->_output = '';
    $this->_error = '';
    $this->_tempfiles = array();
    $this->_time = array();
  }

  /**
   * set task name
   *
   * @access public
   * @param string $name task name
   **/
  function set_name( $name ) {
    $this->_taskname = $name;
  }

  /**
   * get task name
   *
   * @access public
   * @return string task name
   */
  function get_name() {
    return $this->_taskname;
  }

  /**
   * get calculation time
   * 
   * @access public
   * @param string $type type of time : 'value' or 'label'
   * @param string $name name of time : 'start' or 'end' or 'time'
   * @return string time, return false if calculation is not finished
   **/
  function get_time( $type, $name ) {
    if ( empty( $this->_time ) ) {
      return false;
    }
    return $this->_time[$type][$name];
  }

  /**
   * add temporary file
   *
   * @access protected
   * @param string $file temporary file name of work box
   **/
  function add_tempfile( $file ) {
    $this->_tempfiles[] = $file;
  }

  /**
   * run task
   *
   * @access abstract
   * @return bool results
   **/
  function run() {
    $this->_error = 'SimTask::run() called';
    return false;
  }

  /**
   * clean task
   *
   * @access public
   * @return bool result
   */
  function clean() {
    return $this->_clean_tempfiles();
  }

  /**
   * get ouput message
   *
   * @access public
   * @return string path information hidden ouput message
   */
  function get_output() {
    return $this->_display_message( $this->_output );
  }

  /**
   * get errors
   *
   * @access public
   * @return string path information hidden error message
   */
  function get_error() {
    return $this->_display_message( $this->_error );
  }

  function _display_message( $mes ) {
    $searches = array(
      '/'.preg_quote( $this->_wbox, '/' ).'/', 
      '/'.preg_quote( $this->_dbox, '/' ).'/',
      '/'.preg_quote( $this->_cbox, '/' ).'\/(\d+)/e',
    );
    $replaces = array(
      '$(WORK_PATH)', 
      '$(DATA_PATH)',
      '\'$(RESULT_PATH:\'.date(\'Y-m-d H:i:s\', ${1}).\')\'',
    );
    return preg_replace( $searches, $replaces, $mes );
  }

  /**
   * execute shell command
   *
   * @access private
   * @param string $cmd command
   * @param array $time calculation time
   * @return bool result
   **/
  function _do_command( $cmd, &$time ) {
    $cwd = getcwd();
    list( $tus, $tms ) = explode( ' ', microtime() );
    chdir( $this->_wbox );
    // start of command
    $this->_output .= $this->_output_prompt().$cmd."\n";
    $hdl = @popen( $cmd, 'r' );
    if ( $hdl === false ) {
      $this->_error = 'failed to create process '.$cmd;
      chdir( $cwd );
      return false;
    }
    while ( ! feof( $hdl ) ) {
      $this->_output .= fgets( $hdl, 4096 );
    }
    $retcode = ( pclose( $hdl ) >> 8 ) & 0xff;
    if ( $retcode != 0 ) {
      $this->_error = 'process terminated with unexpected code '.$retcode;
      chdir( $cwd );
      return false;
    }
    // end of command
    chdir( $cwd );
    list( $tue, $tme ) = explode( ' ', microtime() );
    $ct = ( (float)$tue + (float)$tme ) - ( (float)$tus + (float)$tms );
    $tms_s = date( DATE_RFC822, $tms );
    $tme_s = date( DATE_RFC822, $tme );
    $ct_s = trim( sprintf( "%12.5f", $ct) );
    $time = array(
      'value' => array( 'start' => $tms, 'end' => $tme, 'time' => $ct ), 
      'label' => array( 'start' => $tms_s, 'end' => $tme_s, 'time' => $ct_s ),
    );
    return true;
  }

  /**
   * execute class method
   *
   * @access private
   * @param string $method method name of this class
   * @param mixed $arg method argument
   * @param array $time calculation time
   * @return bool result
   **/
  function _do_function( $method, $arg, &$time ) {
    $cwd = getcwd();
    list( $tus, $tms ) = explode( ' ', microtime() );
    chdir( $this->_wbox );
    // start of function
    $ret = $this->$method( $arg );
    if ( $ret == false ) {
      chdir( $cwd );
      return false;
    }
    // end of function
    chdir( $cwd );
    list( $tue, $tme ) = explode( ' ', microtime() );
    $ct = ( (float)$tue + (float)$tme ) - ( (float)$tus + (float)$tms );
    $tms_s = date( DATE_RFC822, $tms );
    $tme_s = date( DATE_RFC822, $tme );
    $ct_s = trim( sprintf( "%12.5f", $ct) );
    $time = array(
      'value' => array( 'start' => $tms, 'end' => $tme, 'time' => $ct ), 
      'label' => array( 'start' => $tms_s, 'end' => $tme_s, 'time' => $ct_s ),
    );
    return true;
  }

  function _clean_tempfiles() {
    foreach ( $this->_tempfiles as $fname ) {
      $file = $this->_wbox.'/'.$fname;
      if ( ! $this->_rm_recurse( $file ) ) {
        return false;
      }
    }
    return true;
  }

  function _output_prompt() {
    $this->_output .= '['.$this->_filebox->uname.'@VSS]$ ';
  }

  function _rm_recurse( $file ) {
    if ( ! file_exists( $file ) ) {
      return true;
    }
    if ( is_dir( $file ) && ! is_link( $file ) ) {
      foreach( glob( $file.'/*' ) as $sf ) {
        if ( ! $this->_rm_recurse( $sf ) ) {
          return false;
        }
      }
      if ( ! @rmdir( $file ) ) {
          $this->_error = 'failed to remove directory '.$file;
        return false;
      }
      return true;
    }
    if ( ! @unlink( $file ) ) {
      $this->_error = 'failed to remove file '.$file;
      return false;
    }
    return true;
  }

  function _merge_time( $time1, $time2 ) {
    if ( empty( $time1 ) ) {
      $time1['value']['start'] = $time2['value']['start'];
      $time1['value']['time'] = 0.0;
    }
    $tms = $time1['value']['start'];
    $tme = $time2['value']['end'];
    $ct = $time1['value']['time'] + $time2['value']['time'];
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
