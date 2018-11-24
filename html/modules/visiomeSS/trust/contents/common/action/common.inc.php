<?php

// get parsed template
$html = $tmpl->getParsedTemplate( 'header' );
$html .= $tmpl->getParsedTemplate( 'main' );
$html .= $tmpl->getParsedTemplate( 'footer' );

$page = $visiomess_common['page'];

$breadcrumbs = $visiomess_common['breadcrumbs'][$page];
$navi = $visiomess_common['navi'][$page];

// page
$xoopsOption['template_main'] = 'visiomess_readme.html';
include XOOPS_ROOT_PATH.'/header.php';

visiomess_init_template( $xoopsTpl );

$xoopsTpl->assign( 'breadcrumbs', $breadcrumbs );
$xoopsTpl->assign( 'navi', $navi );
$xoopsTpl->assign( 'body', visiomess_convert_link( $html ) );

include XOOPS_ROOT_PATH.'/footer.php';

?>
