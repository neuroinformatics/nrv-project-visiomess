<?php


class VisiomeSS_Task_Make extends VisiomeSS_Task {
  var $target;
  var $cc = 'gcc';
  var $cxx = 'g++';
  var $ld = '';
  var $srcs = array();
  var $cflags = array();
  var $libs = array();

  function VisiomeSS_Task_Make() {
    parent::VisiomeSS_Task();
    $this->set_name( 'compile simulator' );
    $this->target = '';
    $this->cflags[] = '-O2';
    $this->cflags[] = '-I$(WORKDIR)';
    $this->cflags[] = '-I$(DATADIR)';
    $this->libs[] = '-L$(WORKDIR)';
    $this->libs[] = '-L$(DATADIR)';
    $this->add_tempfile( 'Makefile' );
  }

  function set_target( $target ) {
    $this->target = $target;
  }

  function set_cc( $cc ) {
    $this->cc = $cc;
  }

  function set_cxx( $cxx ) {
    $this->cxx = $cxx;
  }

  function set_ld( $ld ) {
    $this->ld = $ld;
  }

  function add_source( $src, $is_databox=true ) {
    $path = $is_databox ? 'd' : 'w';
    if ( is_array( $src ) ) {
      foreach ( $src as $s ) {
        $this->srcs[] = array( 'file' => $s, 'path' => $path );
      }
    } else {
      $this->srcs[] = array( 'file' => $src, 'path' => $path );
    }
  }

  function add_cflag( $cflag ) {
    if ( is_array( $cflag ) ) {
      $this->cflags = array_merge( $this->cflags, $cflag );
    } else {
      $this->cflags[] = $cflag;
    }
  }

  function add_lib( $lib ) {
    if ( is_array( $lib ) ) {
      $this->libs = array_merge( $this->libs, $lib );
    } else {
      $this->libs[] = $lib;
    }
  }

  function run() {
    $this->_time = array();
    $this->_error = '';
    $this->_output = '';
    $mytime1 = array();
    $mytime2 = array();
    if ( ! $this->_do_function( '_create_makefile', null, $mytime1 ) ) {
      return false;
    }
    if ( ! $this->_do_command( 'make', $mytime2 ) ) {
      return false;
    }
    $this->_time = $this->_merge_time( $mytime1, $mytime2 );
    return true;
  }

  function clean() {
    $this->_error = '';
    $this->_output = '';
    $mytime1 = array();
    if ( ! $this->_do_command( 'make clean', $mytime1 ) ) {
      return false;
    }
    return parent::clean();
  }

  function _create_makefile( $arg ) {
    $this->libs[] = '-lm';
    if ( empty( $this->srcs ) ) {
      $this->_error = 'no input files';
      return false;
    }
    $ext_srcs = array();
    $ext_objs = array();
    $objs = array();
    $has_cxx_src = false;
    foreach ( $this->srcs as $src ) {
      $src_dpath = $src['path'] == 'd' ? '$(DATADIR)' : '$(WORKDIR)';
      $src_fpath = $src_dpath.'/'.$src['file'];
      if ( preg_match( '/^(.+\.)(c|cpp|cxx)$/', $src['file'], $matches ) ) {
        $objs['$(WORKDIR)/'.$matches[1].'o'] = array( 
          'path' => $src_fpath,
          'compiler' => $matches[2] == 'c' ? 'c' : 'cxx',
        );
        if ( $matches[2] != 'c' ) {
          $has_cxx_src = true;
        }
      } else if ( preg_match( '/^(.+\.)(o)$/', $src['file'], $matches ) ) {
        $ext_objs[] = $src_fpath;
      } else {
        $ext_srcs[] = $src_fpath;
      }
    }
    if ( empty( $this->ld ) ) {
      $this->ld = $has_cxx_src ? $this->cxx : $this->cc;
    }
    if ( empty( $this->target ) ) {
      $this->target = 'simulator';
    }
    $makefile = '#'."\n";
    $makefile .= '# makefile for '.$this->target."\n";
    $makefile .= '#'."\n";
    $makefile .= 'CC='.$this->cc."\n";
    $makefile .= 'CXX='.$this->cxx."\n";
    $makefile .= 'LD='.$this->ld."\n";
    $makefile .= 'RM=rm -f'."\n";
    $makefile .= "\n";
    $makefile .= 'WORKDIR='.$this->_wbox."\n";
    $makefile .= 'DATADIR='.$this->_dbox."\n";
    $makefile .= "\n";
    $makefile .= 'CFLAGS='.implode( ' ', $this->cflags )."\n";
    $makefile .= 'CXXFLAGS='.implode( ' ', $this->cflags )."\n";
    $makefile .= 'LIBS='.implode( ' ', $this->libs )."\n";
    $makefile .= "\n";
    $makefile .= 'TARGET='.$this->target."\n";
    $makefile .= 'EXTRA_SRCS='.implode( ' ', $ext_srcs )."\n";
    $makefile .= 'EXTRA_OBJS='.implode( ' ', $ext_objs )."\n";
    $makefile .= 'OBJS='.implode( ' ', array_keys( $objs ) )."\n";
    $makefile .= "\n";
    $makefile .= 'all: $(TARGET)'."\n";
    $makefile .= '$(TARGET): $(OBJS)'."\n";
    $makefile .= "\t".'$(LD) -o $@ $(OBJS) $(EXTRA_SRCS) $(EXTRA_OBJS) $(LIBS)'."\n";
    $makefile .= "\n";
    foreach ( $objs as $obj => $src ) {
      $makefile .= $obj.': '.$src['path']."\n";
      if ( $src['compiler'] == 'c' ) {
        $makefile .= "\t".'$(CC) $(CFLAGS) -c $< -o $@'."\n";
      } else {
        $makefile .= "\t".'$(CXX) $(CXXFLAGS) -c $< -o $@'."\n";
      }
      $makefile .= "\n";
    }
    $makefile .= 'clean:'."\n";
    $makefile .= "\t".'$(RM) $(TARGET) $(OBJS)'."\n";
    return $this->_filebox->save_file( 'Makefile', $makefile );
  }
}

?>
