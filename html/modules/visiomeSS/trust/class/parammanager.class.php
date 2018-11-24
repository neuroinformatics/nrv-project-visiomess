<?php

/**
 * simulation parameter factory class
 *
 * @package visiomess
 * @copyright copyright &copy; 2008 RIKEN Japan
 */
class VisiomeSS_ParameterManager {

  /**
   * place holder for parameter handling classes
   * @access private
   * @var array
   */
  var $_class_loaded;

  /**
   * constractor, this function will called from getInstance() method
   *
   * @access public
   */
  function VisiomeSS_ParameterManager() {
    $this->_class_loaded = array();
  }

  /**
   * get class instance
   *
   * @access public
   * @return object
   */
  function &getInstance(){
    static $instance = null;
    if ( is_null( $instance ) ) {
      $instance = new VisiomeSS_ParameterManager();
    }
    return $instance;
  }

  /**
   * load object of parameter handling class
   *
   * @access public
   * @param string $type type of parameter handling class
   * @param string $file parameter file name
   * @return object of parameter handling class
   */
  function &load( $type, $file ) {
    if ( empty( $this->_cloaded ) ) {
      require_once VSS_CLASS_PATH.'/param.class.php';
    }
    if ( ! isset( $this->class_loaded[$type] ) ) {
      require_once VSS_CLASS_PATH.'/param_'.$type.'.class.php';
      $this->_cloaded[$type] = true;
    }
    $cname = 'VisiomeSS_Parameter_'.ucfirst( $type );
    $param = new $cname( $file );
    return $param;
  }
}

?>
