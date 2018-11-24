<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

/**
 * simulation parameter handling abstract class
 * this class will be extended sub classes
 *
 * @package visiomess
 * @copyright copyright &copy; 2008 RIKEN Japan
 */
class VisiomeSS_Parameter {

  /**
   * parameter file name
   * @access private
   * @var string
   */
  var $_fname = '';

  /**
   * parameters in parameter file
   * @access private
   * @var array
   */
  var $_params = array();

  /**
   * number of parameters
   * @access private
   * @var int
   */
  var $_num_params = 0;

  /**
   * file name of temporary parameter file
   * @access private
   * @var string
   */
  var $_prm_fname = '';

  /**
   * constructor
   *
   * @access public
   * @param string $fname parameter file name
   */
  function VisiomeSS_Parameter( $fname ) {
    $this->_fname = $fname;
    $this->_prm_fname = $fname.'.prm';
    $this->_init_params();
    $this->_num_params = count( $this->_params );
    $this->__init_workspace();
  }

  /**
   * get parameter file name
   *
   * @access public
   * @return string file name
   */
  function get_fname() {
    return $this->_fname;
  }

  /**
   * save parameter file
   *
   * @access public
   */
  function save() {
    $filebox =& VisiomeSS_FileBox::getInstance();
    // update prm file
    $prms = array();
    for( $i = 0; $i < $this->_num_params; $i++ ) {
      $prms[] = $this->_get_param( $i );
    }
    $filebox->save_file( $this->_prm_fname, implode( "\n", $prms ) );
    // save body
    $this->_apply_params();
  }

  /**
   * display parameter file
   *
   * @access public
   * @param string $type type of parameter
   * @return string contents of parameter file
   */
  function display( $type = '' ) {
    return $this->_render_params( $type );
  }

  /**
   * display parameter editing form
   *
   * @access public
   * @param string $type type of parameter
   * @return string editing form html of parameter file
   */
  function form( $type = '' ) {
    $this->__load_prm_file();
    return $this->_render_form( $type );
  }

  /**
   * get form request parameters
   *
   * @access public
   * @param array &$errors error list of form requests
   * @param string $type type of parameter
   * @return bool false if error occured
   */
  function get_request( &$errors, $type = '' ) {
    $errors = array();
    $this->_get_request_params( $errors, $type );
    return empty( $errors );
  }

  /**
   * initizlize parameter
   *
   * @access protected
   * @param int $num number of parameters
   * @param string $type type of parameter
   * @param mixed $value value of parameter
   */
  function _init_param( $num, $type, $value ) {
    $this->_params[$num] = array(
      'type' => $type,
      'init' => $value,
      'value' => $value
    );
  }

  /**
   * get value of parameter
   *
   * @access protected
   * @param int $num number of parameter
   * @return mixed value of parameter
   */
  function _get_param( $num ) {
    return $this->_params[$num]['value'];
  }

  /**
   * set value of parameter
   *
   * @access protected
   * @param int $num number of parameters
   * @param mixed $valie value of parameter
   */
  function _set_param( $num, $value ) {
    if ( ! isset( $this->_params[$num] ) ) {
      die( 'parameter not defined' );
    }
    if ( $this->_params[$num]['type'] == 'n'  && ! visiomess_is_number( $value ) ) {
      die( 'parameter type mismatch' );
    }
    $this->_params[$num]['value'] = $value;
  }

  /**
   * get parameter type
   *
   * @access protected
   * @param int $num number of paraemters
   * @return string type of parameter
   */
  function _get_param_type( $num ) {
    return $this->_params[$num]['type'];
  }

  /**
   * get form requested parameter
   *
   * @access protected
   * @param array &$errors error list of form requests
   * @param int $num number of parameters
   * @return bool false if failure
   */
  function _get_request_param( &$errors, $num ) {
    $key = 'param'.$num;
    $val = visiomess_get_request( 'post', $key, 's', null, false );
    $ptype = $this->_get_param_type( $num );
    $set_ok = true;
    if ( $ptype == 'n' ) {
      if ( ! visiomess_is_number( $val ) ) {
        $errors[] = 'parameter no.'.$num.' is not number format';
        $set_ok = false;
      }
    } else if ( $ptype == 's' ) {
      if( preg_match( '/(?!\\)"/', $val ) ) {
        $errors[] = 'parameter no.'.$num.' is not escaped string';
        $set_ok = false;
      }
    } else {
      $set_ok = false;
    }
    if ( $set_ok ) {
      $this->_set_param( $num, $val );
    }
    return $set_ok;
  }

  /**
   * initilize parametars, this is virtual method.
   * extended sub class have to implemented this method.
   *
   * @access protected
   */
  function _init_params() {
  }

  /**
   * apply parametars to parameter file, this is virtual method.
   * extended sub class have to implemented this method.
   *
   * @access protected
   */
  function _apply_params() {
  }

  /**
   * get requested parametars, this is virtual method.
   * extended sub class have to implemented this method.
   *
   * @access protected
   * @param array &$errors error list of form requests
   * @param string $type type of requested parameter
   */
  function _get_request_params( &$errors, $type ) {
  }

  /**
   * render parameters, this is virtual method.
   * extended sub class have to implemented this method.
   *
   * @access protected
   * @param string $type type of requested parameter
   * @return string renderd html
   */
  function _render_params( $type ) {
    return '';
  }

  /**
   * render parameters editing form, this is virtual method.
   * extended sub class have to implemented this method.
   *
   * @access protected
   * @param string $type type of requested parameter
   * @return string renderd html
   */
  function _render_form( $type ) {
    return '';
  }

  /**
   * initialize work space
   *
   * @access private
   */
  function __init_workspace() {
    $filebox =& VisiomeSS_FileBox::getInstance();
    $prm_fpath = $filebox->get_path( 'wbox', $this->_prm_fname );
    if ( ! file_exists( $prm_fpath ) ) {
      $this->save();
    }
  }

  /**
   * load parameter file
   *
   * @access private
   */
  function __load_prm_file() {
    $filebox =& VisiomeSS_FileBox::getInstance();
    $lines = explode( "\n", $filebox->load_file( $this->_prm_fname, false ) );
    if ( count( $lines ) != $this->_num_params ) {
      die( 'error number of parameters mismatch.');
    }
    for( $i = 0; $i < $this->_num_params; $i++ ) {
      $this->_set_param( $i, $lines[$i] );
    }
  }

}

?>
