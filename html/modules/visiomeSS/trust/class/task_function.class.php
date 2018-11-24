<?php


class VisiomeSS_Task_Function extends VisiomeSS_Task {

  var $funcs = array();

  function VisiomeSS_Task_Function() {
    parent::VisiomeSS_Task();
    $this->set_name( 'local function' );
  }

  function set_function( $func, $args ) {
    if ( is_array( $func ) ) {
      list( $c, $m ) = $func;
      $this->funcs[] = array( 'class' => $c, 'method' => $m, 'args' => $args );
    } else {
      $this->funcs[] = array( 'class' => '', 'method' => $func, 'args' => $args );
    }
  }

  function _run_funcs() {
    foreach ( $this->funcs as $func ) {
      $c =& $func['class'];
      $m = $func['method'];
      $a = $func['args'];
      if ( is_object( $c ) ) {
        $ret = $c->$m( $a );
      } else {
        $ret = $m( $a );
      }
      if ( $ret == false ) {
        return $ret;
      }
    }
    return true;
  }

  function run() {
    $this->_time = array();
    $this->_error = '';
    $this->_output = '';
    if ( ! $this->_do_function( '_run_funcs', null, $this->_time ) ) {
      return false;
    }
    return true;
  }

  function clean() {
    $this->_error = '';
    $this->_output = '';
    return parent::clean();
  }
}

?>
