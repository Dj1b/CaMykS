<?php
/**
 * @brief Splash error full HTML5 page
 * @details Engine / Generic Layout
 * @file engine/data/html/spash_error.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jan 2008
 * @date Modification: Apr 2018
 * @copyright 2008 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @cond Exclude
 */
global $camyks;
?>
<!DOCTYPE html>
    <html<?=isset($camyks->current_language)?' lang="'.$camyks->current_language.'"':'';?>>
    <head>
        <title><?=$error['site_title']?><?=isset($error['title'])?' : '.$error['title']:''?></title> 
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
        <meta name="author" content="CaMykS Engine" />
        <style type="text/css">
            * { font-family : Arial, Verdana, Helvetica; font-size : 11px; font-weight : normal; font-style : normal; color : #333333; padding : 0; margin : 0; }
            body { background: #DEDEEE; }
            p { padding:4px; }
            a { font-weight:bold; color:#666686; }
            #pageMain{ margin: 100px auto; width:500px; max-width:100%; }
            #pageHeader { background : #666686; padding : 6px 12px; font-weight:bold; font-size:14px; color:white;  }
            #pageContent { background : white; padding: 12px 8px; }
            #pageFooter { background : #666686; padding : 6px 12px; font-size:10px; color:white; text-align:right; }
            #description { color:#CC3333; font-weight:bold; font-size:12px; }
        </style>
    </head>
    <body>
        <div id="pageMain">
            <div id="pageHeader">
                <?=isset($error['title'])?$error['title']:$error['site_title'];?>
            </div>
            <div id="pageContent">
                <?php if (isset($error['description']) and $error['description']!='') : ?>
                    <p id="description">
                        <?=$error['description']?>
                    </p>
                <?php endif; ?>

                <?php $cnt=1; ?>
                <?php while (isset($error['content'.$cnt])) : ?>
                    <p>
                        <?=$error['content'.$cnt]?>
                    </p>
                    <?php $cnt++; ?>
                <?php endwhile; ?>

                <?php if (isset($error['error_title']) and $error['error_title']!='' and isset($error['error_link']) and $error['error_link']!='') : ?>
                    <p>
                        <a href="<?=$error['error_link']?>"> &gt; <?=$error['error_title']?> </a>
                    </p>
                <?php endif; ?>

                <?php if (isset($error['back_title']) and $error['back_title']!='' and isset($error['back_link']) and $error['back_link']!='') : ?>
                    <p>
                        <a href="<?=$error['back_link']?>"> &gt; <?=$error['back_title']?> </a>
                    </p>
                <?php endif; ?>
            </div>

            <div id="pageFooter">
                <?=$camyks->name.' '.$camyks->version; ?>
            </div>
        </div>
    </body>
</html>