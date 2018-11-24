<?php

if ( ! defined( 'XOOPS_ROOT_PATH' ) ) exit();

$modversion['name'] = _MI_VISIOMESS_NAME;
$modversion['version'] = 1.01;
$modversion['description'] = _MI_VISIOMESS_DESC;
$modversion['credits'] = 'RIKEN, Japan (http://www.riken.jp/)';
$modversion['author'] = 'Hidetoshi IKENO';
$modversion['help'] = 'help.html';
$modversion['license'] = 'GPL see LICENSE';
$modversion['official'] = 0;
$modversion['image'] = 'images/icon_slogo.png';
$modversion['dirname'] = 'visiomeSS';

// Admin
$modversion['hasAdmin'] = 0;
$modversion['adminindex'] = '';
$modversion['adminmenu'] = '';

// Blocks
$modversion['blocks'][1]['file'] = 'visiomess_block_menu.php';
$modversion['blocks'][1]['name'] = _MI_VISIOMESS_BNAME1;
$modversion['blocks'][1]['description'] = 'Menu Block';
$modversion['blocks'][1]['show_func'] = 'b_visiomess_menu_show';
$modversion['blocks'][1]['template'] = 'visiomess_block_menu.html';

// Menu
$modversion['hasMain'] = 1;

// Templates
$modversion['templates'][1]['file'] = 'visiomess_main.html';
$modversion['templates'][1]['description'] = 'Main page';
$modversion['templates'][2]['file'] = 'visiomess_readme.html';
$modversion['templates'][2]['description'] = 'Readme page';

?>
