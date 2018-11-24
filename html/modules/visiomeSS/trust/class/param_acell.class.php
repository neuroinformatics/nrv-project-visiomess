<?php

/**
 * simulation parameter handling class for A-Cell
 *
 * @package visiomess
 * @copyright copyright &copy; 2008 RIKEN Japan
 */
class VisiomeSS_Parameter_Acell extends VisiomeSS_Parameter {
  /**
   * .RK parameter file name
   * @access private
   * @var string 
   */
  var $rk;

  /**
   * body content of .RK parameter file
   * @access private
   * @var string 
   */
  var $body = array();

  /**
   * .Csim simulation file name
   * @access private
   * @var string 
   */
  var $csim;

  /**
   * output file name
   * @access private
   * @var string
   */
  var $ofile;

  /**
   * number of symbols
   * @access private
   * @var int
   */
  var $num_sym;

  /**
   * name of symbols
   * @access private
   * @var array
   */
  var $symbols = array();

  /**
   * number of stimulus
   * @access private
   * @var int
   */
  var $num_stim;

  /**
   * number of conditions
   * @access private
   * @var int
   */
  var $num_cond;

  /**
   * constractor
   *
   * @access public
   * @param string $rk .RK parameter file name
   */
  function VisiomeSS_Parameter_Acell( $rk ) {
    $this->rk = $rk;
    $filebox =& VisiomeSS_FileBox::getInstance();
    $filebox->copy_file_data2work( $rk, false );
    $fname = trim( $filebox->load_file( $rk, false ) );
    parent::VisiomeSS_Parameter( $fname );
  }

  /**
   * get .Csim file name
   *
   * @access public
   * @return string
   */
  function get_csim() {
    return $this->csim;
  }

  /**
   * get output file name
   *
   * @access public
   * @return string
   */
  function get_outfile() {
    return $this->ofile;
  }

  /**
   * get number of symbols
   *
   * @access public
   * @return int
   */
  function get_num_symbol() {
    return $this->num_sym;
  }

  /**
   * get label of symbols
   *
   * @access public
   * @param int $num index of symbol
   * @return string
   */
  function get_symbol_label( $num ) {
    return $this->symbols[$num]['label'];
  }

  /**
   * initilize parametars
   *
   * @access protected
   */
  function _init_params() {
    $filebox =& VisiomeSS_FileBox::getInstance();
    $this->body = explode( "\r\n", $filebox->load_file( $this->_fname, true ) );
    // simulation file
    if ( ! preg_match( '/^(.*)\.Csim$/', $this->body[0], $matches ) ) {
      die( 'unexpected Csim file name' );
    }
    $this->csim = $matches[1];
    // output file
    $this->ofile = $this->body[1];
    // number of symbols
    $this->num_sym = intval( $this->body[2] );
    // symbols
    for ( $i = 0; $i < $this->num_sym; $i++ ) {
      list( $label, $value, $unit ) = explode( ' ', $this->body[3 + $i] );
      $this->symbols[] = array( 'label' => $label, 'unit' => $unit );
      $this->_init_param( $i, 'n', $value );
    }
    // stimulation parameters
    $line = 3 + $this->num_sym;
    if ( ! preg_match( '/^\/\*stimulation parameters\*\/$/', $this->body[$line] ) ) {
       die( 'condition file error : stimulation parameters not found' );
    }
    $line++;
    for( $i = 0; ! preg_match( '/^\/\*calculation condition\*\/$/', $this->body[$line + $i] ); $i++ ) {
      $value = trim( $this->body[$line + $i] );
      $this->_init_param( $i + $this->num_sym, 'n', $value );
    }
    $this->num_stim = $i;
    // calculation condtions
    $line += $this->num_stim + 1;
    for( $i = 0; ! preg_match( '/^\/\*number of output variables\*\/$/', $this->body[$line + $i ] ); $i++ ) {
      $value = trim( $this->body[$line + $i] );
      $this->_init_param( $i + $this->num_sym + $this->num_stim, 'n', $value );
    }
    $this->num_cond = $i;
  }

  /**
   * apply parametars to parameter file
   *
   * @access protected
   */
  function _apply_params() {
    $filebox =& VisiomeSS_FileBox::getInstance();
    // replace symbols
    $line = 3;
    for ( $i = 0; $i < $this->num_sym; $i++ ) {
      $num = $i;
      $value = $this->_get_param( $num );
      $this->body[$line + $i] = $this->symbols[$i]['label'].' '.$value.' '.$this->symbols[$i]['unit'];
    }
    // replace parameters
    $line += $this->num_sym + 1;
    for ( $i = 0; $i < $this->num_stim; $i++ ) {
      $num = $i + $this->num_sym;
      $value = $this->_get_param( $num );
      $this->body[$line + $i] = ' '.$value;
    }
    // replace calculation conditions
    $line += $this->num_stim + 1;
    for ( $i = 0; $i < $this->num_cond; $i++ ) {
      $num = $i + $this->num_sym + $this->num_stim;
      $value = $this->_get_param( $num );
      $this->body[$line + $i] = ' '.$value;
    }
    $filebox->save_file( $this->_fname, implode( "\r\n", $this->body ) );
  }

  /**
   * get requested parametars
   *
   * @access protected
   * @param array &$errors error list of form requests
   * @param string $type type of requested parameter
   */
  function _get_request_params( &$errors, $type ) {
    switch ( $type ) {
    case 'symbol':
      for ( $i = 0; $i < $this->num_sym; $i++ ) {
        $num = $i;
        $this->_get_request_param( $errors, $num );
      }
      break;
    case 'stim':
      for ( $i = 0; $i < $this->num_stim; $i++ ) {
        $num = $i + $this->num_sym;
        $this->_get_request_param( $errors, $num );
      }
      break;
    case 'cond':
      for ( $i = 0; $i < $this->num_cond; $i++ ) {
        $num = $i + $this->num_sym + $this->num_stim;
        $this->_get_request_param( $errors, $num );
      }
      break;
    default:
      $errors[] = 'unknown request type';
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
    return $this->__render_params_body( $type, false );
  }

  /**
   * render parameters editing form
   *
   * @access protected
   * @param string $type type of requested parameter
   * @return string renderd html
   */
  function _render_form( $type ) {
    return $this->__render_params_body( $type, true );
  }

  /**
   * render parameters and editiong forms
   *
   * @access private
   * @param string $type type of requested parameter
   * @param bool $is_form true if render form
   * @return rendlerd html
   */
  function __render_params_body( $type, $is_form ) {
    $html = '<div class="visiomess_parameter">'."\n";
    switch( $type ) {
    case 'symbol':
      $html .= $this->__render_symbol( $is_form );
      break;
    case 'stim':
      $html .= $this->__render_stim( $is_form );
      break;
    case 'cond':
      $html .= $this->__render_cond( $is_form );
      break;
    default:
      $html .= $this->__render_symbol( $is_form );
      $html .= $this->__render_stim( $is_form );
      $html .= $this->__render_cond( $is_form );
    }
    $html .= '</div>'."\n";
    return $html;
  }

  /**
   * render symbol part of parameters and editiong forms
   *
   * @access private
   * @param bool $is_form true if render form
   * @return rendlerd html
   */
  function __render_symbol( $is_form ) {
    $myts =& MyTextSanitizer::getInstance();
    $html = '<table>'."\n";
    for ( $i = 0; $i < $this->num_sym; $i++ ) {
      $num = $i;
      $label = $myts->htmlSpecialChars( $this->symbols[$i]['label'] );
      $unit = $myts->htmlSpecialChars( $this->symbols[$i]['unit'] );
      $value = $myts->htmlSpecialChars( $this->_get_param( $num ) );
      $name = 'param'.$num;
      $html .= '<tr>'."\n";
      $html .= '<td style="width: 60px;">';
      $html .= $label;
      $html .= '</td>'."\n";
      $html .= '<td>';
      if ( $is_form ) {
        $html .= '<input name="'.$name.'" size="20" value="'.$value.'" type="text"/>';
      } else {
        $html .= $value;
      }
      $html .= '&nbsp;'.$unit.'</td>';
      $html .= '</tr>'."\n";
    }
    $html .= '</table>'."\n";
    return $html;
  }

  /**
   * render stim part of parameters and editiong forms
   *
   * @access private
   * @param bool $is_form true if render form
   * @return rendlerd html
   */
  function __render_stim( $is_form ) {
    $myts =& MyTextSanitizer::getInstance();
    $labels = array(
      'function', 'param1', 'maximum value', 'param3', 'param4',
      'param5', 'param6', 'Tau1', 'Tau2', 'param9', 'param10',
      'param11', 'param12', 'param13', 'param14',
    );
    $pstim0_labels = array(
      'step', 'plus', 'double exponential', 'ramp', 'alpha fuction',
    );
    $html = '<table>'."\n";
    for ( $i = 0; $i < $this->num_stim; $i++ ) {
      $num = $i + $this->num_sym;
      $label = $myts->htmlSpecialChars( $labels[$i] );
      $value = $myts->htmlSpecialChars( $this->_get_param( $num ) );
      $name = 'param'.$num;
      $html .= '<tr>'."\n";
      $html .= '<td style="width:120px;">'.$label.':</td>'."\n";
      $html .= '<td>';
      if ( $is_form ) {
        if ( $i == 0 ) {
          for ( $j = 0; $j < 5; $j++ ) {
            $plabel = $myts->htmlSpecialChars( $pstim0_labels[$j] );
            $html .= '<span class="visiomess_nowrap">';
            $html .= '<input type="radio" name="'.$name.'" value="'.($j + 1).'"'.( $value == $j+1 ? ' checked="checked"' : '' ).'/>';
            $html .= '&nbsp;'.$plabel;
            if ( $j != 4 ) $html .= ' &nbsp;';
            $html .= '</span>';
          }
        } else {
          $html .= '<input type="text" name="'.$name.'" size="30" value="'.$value.'"/>';
        }
      } else {
        if ( $i == 0 ) {
          $html .= $myts->htmlSpecialChars( $pstim0_labels[$value - 1] );
        } else {
          $html .= $value;
        }
      }
      $html .= '</td>'."\n";
      $html .= '</tr>'."\n";
    }
    $html .= '</table>'."\n";
    return $html;
  }

  /**
   * render cond part of parameters and editiong forms
   *
   * @access private
   * @param bool $is_form true if render form
   * @return rendlerd html
   */
  function __render_cond( $is_form ) {
    $myts =& MyTextSanitizer::getInstance();
    $labels = array( 'simulation time', '-', 'calc. interval', 'output interval' );
    $html = '<table>'."\n";
    for ( $i = 0; $i < $this->num_cond; $i++ ) {
      $num = $i + $this->num_sym + $this->num_stim;
      $label = $myts->htmlSpecialChars( $labels[$i] );
      $value = $myts->htmlSpecialChars( $this->_get_param( $num ) );
      $name = 'param'.$num;
      if ( $i != 1 ) {
        $html .= '<tr>'."\n";
        $html .= '<td style="width:120px;">'.$label.':</td>'."\n";
        $html .= '<td>';
      } else {
        $html .= '&nbsp;&nbsp;'.$label.'&nbsp;&nbsp;';
      }
      if ( $is_form ) {
        $html .= '<input type="text" name="'.$name.'" size="20" value="'.$value.'"/>';
      } else {
        $html .= $value;
      }
      if ( $i != 0 ) {
        $html .= '</td>'."\n";
        $html .= '</tr>'."\n";
      }
    }
    $html .= '</table>'."\n";
    return $html;
  }

}

?>
