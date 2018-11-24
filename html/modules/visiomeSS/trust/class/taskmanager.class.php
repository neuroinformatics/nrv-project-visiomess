<?php

require_once VSS_CLASS_PATH.'/task.class.php';

class VisiomeSS_TaskManager {
  var $results = array();
  var $result_type = '';
  var $tasks = array();
  var $time = array();
  var $errors = array();

  function VisiomeSS_TaskManager() {
  }

  function &create_task( $name ) {
    $cfile = VSS_CLASS_PATH.'/task_'.$name.'.class.php';
    require_once $cfile;
    $cname = 'VisiomeSS_Task_'.ucfirst( $name );
    $tinst = new $cname();
    $this->tasks[] =& $tinst;
    return $tinst;
  }

  function display() {
    $num_task = count( $this->tasks );
    if ( $num_task == 0 ) {
      die( 'empty task' );
    }
    $total = 0.0;
    $start = $this->tasks[0]->get_time( 'label', 'start' );
    $end = $this->tasks[$num_task - 1]->get_time( 'label', 'end' );
    if ( $start === false ) {
      $start = 'error';
    }
    if ( $end === false ) {
      $end = 'error';
    }
    $header = '<p>Simulation start : '.$start.'</p>';
    $footer = '<p>Simulation end : '.$end.'</p>';
    $has_error = false;
    $html = '';
    foreach( $this->tasks as $num => $task ) {
      $prefix = '&raquo; '.( ( $num_task == 1 ) ? '' : 'step'.( $num + 1 ).' - ' );
      $name = $task->get_name();
      $time = $task->get_time( 'label', 'time' );
      if ( $time === false ) {
        $has_error = true;
        $time = 'error';
        break;
      } else {
        $time .= ' sec.';
        $total += $task->get_time( 'value', 'time' );
      }
      $html .=  '<p>'.$prefix.$name.' : '.$time.'</p>';
    }
    if ( $has_error ) {
      $html = '<p>an error occured</p>';
    }
    $post = '<p>total time : '.sprintf( '%12.5f', $total ).' sec.</p>';
    $html = $header.'<br />'.$html.'<br />'.$footer.'<br />'.$post;
    return $html;
  }

  function display_error() {
    foreach( $this->errors as $err ) {
      echo $err;
    }
  }

  function run() {
    $outputs = array();
    $filebox =& VisiomeSS_FileBox::getInstance();
    if ( empty( $this->tasks ) ) {
      die( 'no tasks' );
    }
    // run tasks
    foreach( $this->tasks as $task ) {
      $tmpt = array();
      if ( ! $task->run() ) {
        return false;
      }
      $outputs[] = $task->get_output();
      $this->time = $task->_merge_time( $this->time, $task->_time );
    }
    // pickup results
    $ctime = $this->time['value']['start'];
    $rbox = $filebox->make_result_path( $ctime );
    foreach( $this->results as $result ) {
      if ( $result['do_convert'] ) {
        $fpath = $filebox->get_path( 'wbox', $result['file'] );
        $tpath = $rbox.'/'.preg_replace( '/\.(tif|eps|ps)$/', '.png', basename( $result['file'] ) );
        $cmd = 'convert '.escapeshellarg( $fpath ).' '.escapeshellarg( $tpath );
        system( $cmd );
        unlink( $fpath );
      } else {
        $filebox->move_file_work2result( $result['file'], $ctime );
      }
    }
    $filebox->write_result( $ctime, 'result.log', implode( "\n", $outputs ) );
    if ( $this->result_type != '' ) {
      $filebox->write_result( $ctime, 'result.type', $this->result_type );
    }

    // clean tasks
    foreach( array_reverse( $this->tasks ) as $task ) {
      if ( ! $task->clean() ) {
        $this->errors[] = $task->get_error();
        return false;
      }
    }
    return $ctime;
  }

  function set_result_type( $rtype ) {
    $this->result_type = $rtype;
  }

  function set_result( $file, $do_convert ) {
    if ( is_array( $file ) ) {
      foreach( $file as $f ) {
        $this->results[] = array( 'file' => $f, 'do_convert' => $do_convert );
      }
    } else {
      $this->results[] = array( 'file' => $file, 'do_convert' => $do_convert );
    }
  }
}

?>
