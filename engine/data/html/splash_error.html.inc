<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type		: Engine / Generic Layout
 * Creation Date	: Jan 2008
 * Last Modif Date	: Jan 2008
 * History :
 * * 08-01-17 : Initial file 
 *
 * Splash error XHTML page
*/
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title><?=$error['site_title']?><?=isset($error['title'])?' : '.$error['title']:''?></title> 
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <meta http-equiv="Pragma" content="no-cache" />
    <meta http-equiv="Content-Style-Type" content="text/css" />
    <meta http-equiv="Content-Script-Type" content="text/javascript" />
    <meta name="author" content="CaMykS Engine" />
    <style type="text/css">
      * { font-family : Arial, Verdana, Helvetica; font-size : 11px; font-weight : normal; font-style : normal; color : #333333; padding : 0; margin : 0; }
      body { background: #DEDEEE; }
      p { padding:4px; }
      a { font-weight:bold; color:#666686; }
      #pageMain{ margin: 100px auto; width:500px; border:solid 1px #666686 }
      #pageHeader { background : #666686; padding : 6px 12px; font-weight:bold; font-size:14px; color:white;  }
      #pageContent { background : white; padding: 12px 8px; }
      #pageFooter { background : #666686; padding : 2px 12px; font-weight:bold; font-size:10px; color:white; }
      #description { color:#CC3333; font-weight:bold; font-size:12px; }
    </style>
  </head>
  <body>
    <div id="pageMain">
      <div id="pageHeader">
	<?=$error['site_title']?> <?=isset($error['title'])?' : '.$error['title']:''?>
      </div>
      <div id="pageContent">
	<?php if ( isset( $error['description'] ) and $error['description']!='' ) : ?>
	<p id="description">
	  <?=$error['description']?>
	</p>
	<?php endif; ?>
	
	<?php $cnt=1; ?>
	<?php while ( isset ( $error['content'.$cnt] ) ) : ?>
	<p>
	  <?=$error['content'.$cnt]?>
	</p>
	<?php $cnt++; ?>
	<?php endwhile; ?>
	
	<?php if ( isset( $error['error_title'] ) and $error['error_title']!=''
	and isset( $error['error_link'] ) and $error['error_link']!='' ) : ?>
	<p>
	  <a href="<?=$error['error_link']?>"> &gt; <?=$error['error_title']?> </a>
	</p>
	<?php endif; ?>
	
	
	<?php if ( isset( $error['back_title'] ) and $error['back_title']!=''
	and isset( $error['back_link'] ) and $error['back_link']!='' ) : ?>
	<p>
	  <a href="<?=$error['back_link']?>"> &gt; <?=$error['back_title']?> </a>
	</p>
	<?php endif; ?>
      </div>
      
      <div id="pageFooter">
	&nbsp;
      </div>
    </div>
  </body>
</html>