<?php
// include the page header

require( 'header.php' );
include( XOOPS_ROOT_PATH.'/header.php' );

$uname = !empty($xoopsUser) ? $xoopsUser->getVar( 'uname', 'E' ) : 
                              $uname = "anonymous";

// program depend

$VSS_TITLE = "A Stochastic Model of Retinal Ganglion Cell";
$VSS_COMMENT = 'You can plot voltage clamp or current clamp simulation results. Click "plot voltage clamp result" or "plot current clamp result" button, then "plot result" button for plotting graph. <br>';
$VSS_DIR = "nrv-rgc";
$VSS_FILES = array( "" ); 

// make file box

$fileBox = "../000FileBox/$uname/$VSS_DIR";

// copy script & config file for each user's filebox

if ( file_exists( $fileBox ) ) {
} else {
  mkdir( "$fileBox", 0755 );

  foreach( $VSS_FILES as $copy_file ) {
    copy( "./org/$copy_file", "$fileBox/$copy_file" );
  }
}

?>

<?php
if ( $uname != "anonymous" ) {
  echo '<div align=right><a href="../index.php">back to the index</a></div>';
}
echo '<div align=right><a href="readme.php">back to readme</a></div>';
echo "<div align=right><b>user: $uname </b></div>";
?>

<font size=4><b><?php echo $VSS_TITLE; ?></b></font>
<p>
<?php echo $VSS_COMMENT; ?>
</p>

<p>
<form method="POST" action="#">
<input type="submit" name="run1" value="plot voltage clamp result">
<input type="submit" name="run2" value="plot current clamp result">
<!--
&nbsp;
<input type="submit" name="edit" value="edit plot parameters">
<input type="submit" name="reset" value="reset plot parameters">
-->
</form>
</p>

<hr>

<?php
$save  = @$_POST["save"];
$endSim  = @$_POST["endSim"];
$edit  = @$_POST["edit"];
$reset  = @$_POST["reset"];

$run   = @$_POST["run"];
$run1   = @$_POST["run1"];
$run2   = @$_POST["run2"];

$param  = @$_POST["param"];
$imgDir  = @$_POST["imgDir"];

// save parameter file

if ($save) {
  echo '<pre>';
  echo "$param";
  echo '</pre>';
  echo "<p> save paramter file </p>";
  
  $fp = fopen( "$fileBox/param.mdl", "w" );
  fwrite( $fp, $param );
  fclose( $fp );
}

// plot results

if ($endSim) {
  echo '<img src="'."$imgDir/image1.w0.png".'" alt="results" />';
}

// reset parameter file

if ($reset) { 
  echo '<p> reset parameter file </p>';
  copy( "./org/param.mdl", "$fileBox/param.mdl" );
}

// edit parameter file

if ($edit) { 
  echo '<h4> edit Parameter file </h4>';

  echo '<form method="POST" action="#">';
  echo '<p>';
  echo '<input type=submit name=save value=save>';
  echo '<br>';

  $fp = fopen( "$fileBox/param.mdl", "r" );
  echo '<textarea name=param rows=10 cols=80>';
  while ( !feof($fp) ) {
    echo fgets( $fp, 4096 );
  }
  echo '</textarea>';
  fclose( $fp );
  echo '</form>';
}

// run SATELLIET script

if ($run1 || $run2) { 
  echo '<h4> SATELLITE status </h4>';

  echo '<br>';

  // prepare output directory

  $hdl = opendir( "$fileBox" );
  while ( ($dname = readdir($hdl)) != false ) {
    if ( $dname != "." && $dname != ".." && filetype($dname) != 'file' ) {
            system( "rm -rf $fileBox/$dname" );
    }
  }

  $now_t = gettimeofday();
  $sec = $now_t["sec"];
  mkdir( "$fileBox/$sec" );

  $fp = fopen( "output.sl", "w" );
  fwrite( $fp, "/usr/local/satellite/bin/gpm2ps -cps > w0.ps;\n" );
  fwrite( $fp, "convert w0.ps w0.png;\n" );
  fwrite( $fp, "cp w0.png $fileBox/$sec/image1.w0.png\n" );
  fclose( $fp );

  // start SATELLITE

  echo "<p> SATELLITE start </p>";

  echo  getcwd()."<br>";

  echo "execution of SATELLITE script<br>";

  foreach( $VSS_FILES as $copy_file ) {
    copy( "$fileBox/$copy_file", "$copy_file" );
  }
  if ($run1) {
    system( "/usr/local/satellite/bin/sl".
          " -setup -clean ../cgisetup.sl vclamp-area.sl output.sl >".
          " /dev/null" );
  } else if ($run2) {
    system( "/usr/local/satellite/bin/sl".
          " -setup -clean ../cgisetup.sl cc-noise.sl output.sl >".
          " /dev/null" );
  }

  echo  getcwd()."<br>";

  echo "<p> SATELLITE end </P>";

  $dir = getcwd();

  echo '<form method="POST" action="#">';
  echo '<input type="submit" name="endSim" value="plot results">';
  echo '<input type="hidden" value="'."$fileBox/$sec".'" name="imgDir">';
  echo '</form>';
}

?>

<?php
// include the page footer

include( XOOPS_ROOT_PATH.'/footer.php' );
?>
