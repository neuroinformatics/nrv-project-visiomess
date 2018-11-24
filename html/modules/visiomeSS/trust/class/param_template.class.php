<?php

/**
 * simulation parameter handling class for generic template
 *
 * @package visiomess
 * @copyright copyright &copy; 2008 RIKEN Japan
 */
class VisiomeSS_Parameter_Template extends VisiomeSS_Parameter {
  /**
   * regex patter for parameter part
   * @access private
   * @var string 
   */
  var $re;

  /**
   * template file name
   * @access private
   * @var string 
   */
  var $tpl_file;

  /**
   * variable counter in temporary file
   * @access private
   * @var string 
   */
  var $temp_counter;

  /**
   * constractor
   *
   * @access public
   * @param string $fname template file name
   */
  function VisiomeSS_Parameter_Template( $fname ) {
    $re_num = '[-+]?(?:\d+(?:\.\d*)?|(?:\.\d+))(?:[eE][-+]?\d+)?';
    $re_str = '".*"';
    $this->re = '/@@@(?:(NUMBER):('.$re_num.')|(STRING):('.$re_str.'))@@@/';
    $this->tpl_file = $fname.'.tpl';
    parent::VisiomeSS_Parameter( $fname );
  }

  /**
   * initilize parameters
   *
   * @access protected
   */
  function _init_params() {
    // parse template
    $filebox =& VisiomeSS_FileBox::getInstance();
    $body = $filebox->load_file( $this->tpl_file, true );
    if ( preg_match_all( $this->re, $body, $matches, PREG_SET_ORDER ) ) {
      $total = count( $matches );
      for( $i = 0; $i < $total; $i++ ) {
        if ( $matches[$i][1] == 'NUMBER' ) {
          $this->_init_param( $i, 'n', $matches[$i][2] );
        } else if ( $matches[$i][3] == 'STRING' ) {
          $this->_init_param( $i, 's', $matches[$i][4] );
        }
      }
    }
  }

  /**
   * apply parametars to parameter file
   *
   * @access protected
   */
  function _apply_params() {
    $filebox =& VisiomeSS_FileBox::getInstance();
    // work file
    $tpl = $filebox->load_file( $this->tpl_file, true );
    $this->temp_counter = 0;
    $body = preg_replace_callback( $this->re, array( &$this, '__replace_value' ), $tpl );
    $filebox->save_file( $this->_fname, $body );
  }

  /**
   * get requested parametars
   *
   * @access protected
   * @param array &$errors error list of form requests
   * @param string $type type of requested parameter
   */
  function _get_request_params( &$errors, $type ) {
    for ( $i = 0; $i < $this->_num_params; $i++ ) {
      $this->_get_request_param( $errors, $i );
    }
  }

  /**
   * render parameters
   *
   * @access protected
   * @param string $type type of requested parameter
   * @return rendlerd html
   */
  function _render_params( $type ) {
    $filebox =& VisiomeSS_FileBox::getInstance();
    $myts =& MyTextSanitizer::getInstance();
    $body = $myts->htmlSpecialChars( $filebox->load_file( $this->_fname, false ) );
    return '<pre>'.$body.'</pre>';
  }

  /**
   * render parameters editing form
   *
   * @access protected
   * @param string $type type of requested parameter
   * @return string renderd html
   */
  function _render_form( $type ) {
    $filebox =& VisiomeSS_FileBox::getInstance();
    $myts =& MyTextSanitizer::getInstance();

    $tpl = $myts->htmlSpecialChars( $filebox->load_file( $this->tpl_file, true ) );
    $search = array( '/ /', '/\n/' );
    $replace = array( '&nbsp;', '<br />' );
    $body = preg_replace( $search, $replace, $tpl );
    $this->temp_counter = 0;
    $body = preg_replace_callback( $this->re, array( &$this, '__replace_form_input' ), $body );
    $body = '<div class="visiomess_parameter">'.$body.'</div>';
    return $body;
  }

  /**
   * call back handler to replace parameter values
   *
   * @access private
   * @param array $matches matched regex patterns
   * @return string replaced value
   */
  function __replace_value( $matches ) {
    $value = $this->_get_param( $this->temp_counter );
    $is_string = false;
    if ( $this->_get_param_type( $this->temp_counter ) == 's' ) {
      $is_string = true;
    }
    $this->temp_counter++;
    if ( $is_string ) {
      return '"'.$value.'"';
    }
    return $value;
  }

  /**
   * call back handler to replace parameter values for form input
   *
   * @access private
   * @param array $matches matched regex patterns
   * @return string replaced value
   */
  function __replace_form_input( $matches ) {
    $name = 'param'.$this->temp_counter;
    $value = $this->_get_param( $this->temp_counter );
    $ret = '<input type="text" size="5" name="'.$name.'" value="'.$value.'"/>';
    $is_string = false;
    if (  $this->_get_param_type( $this->temp_counter ) == 's' ) {
      $is_string = true;
    }
    $this->temp_counter++;
    if ( $is_string ) {
      return '"'.$ret.'"';
    }
    return $ret;
  }
}

?>
