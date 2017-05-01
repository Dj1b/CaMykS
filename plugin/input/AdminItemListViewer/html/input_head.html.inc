<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Creation Date	: Oct 2008
 * Last Modif Date	: Apr 2017
 * 
 * AdminItemListViewer input head layout
*/
if ( $this->selectorForm !== false ) {
  echo $this->selectorForm->display_header();
  echo $this->selectorForm->display_hiddens();
  echo '<div class="AdminItemListViewer">';

  foreach ( $this->params['headselectors'] as $name => $selector ) {

    /* start item box */
    echo '<div class="selector">';
    echo '<div class="label eTableLine0 eContent2">';
    echo $selector['title'];
    echo '</div>' . "\n";
    echo '<div class="input eTableLine0 eContent2">';
    
    /* display selector item */
    switch ( $selector['itemtype'] ) {
    case 'page' :
      /* selector type is a page */
      echo '<div class="pageSelector" style="width:160px; text-align:center;">';
      echo '<a href="javascript:'.$this->params['name'].'.update_pageMinus(\''.$name.'\');void(0);" style="float:left">';
      echo '<img src="'.$this->get_icon('left', 'std').'" alt="" border="0" onmouseover="this.src=\''.$this->get_icon('left', 'ovr').'\';" onmouseout="this.src=\''.$this->get_icon('left', 'std').'\';" style="margin-top:6px;" />';
      echo '</a>';
      echo '<a href="javascript:'.$this->params['name'].'.update_pagePlus(\''.$name.'\');void(0);" style="float:right">';
      echo '<img src="'.$this->get_icon('right', 'std').'" alt="" border="0" onmouseover="this.src=\''.$this->get_icon('right', 'ovr').'\';" onmouseout="this.src=\''.$this->get_icon('right', 'std').'\';" style="margin-top:6px;" />';
      echo '</a>';
      //echo '<input type="text" name="'.$this->params['name'].'_form'.$name.'" value="'.($this->selectionValues[$name]+1).'" size="4" style="text-align:right" onchange="'.$this->params['name'].'.update();" />';
      echo $this->selectorForm->display_textInput(array('name'=>$this->params['name'].'_form'.$name, 'default'=>$this->selectionValues[$name]+1, 'maxlength'=>16, 'size'=>4, 
        'class'=>'vsinputs', 'style'=>'text-align:right', 'onchange'=>$this->params['name'].'.update();'));
      echo '/ '.$selector['maxpages'] . "\n";
      echo '</div>';
      break;
    case 'select' :
      /* selector type is a select dropbox */
      echo $this->selectorForm->display_selectInput(array('name'=>$this->params['name'].'_form'.$name, 'default'=>$this->selectionValues[$name], 'values'=>$selector['values'], 'onchange'=>$this->params['name'].'.update();'));
      break;
    case 'boolean' :
      /* selector type is a select dropbox */
      echo $this->selectorForm->display_booleanSelectInput(array('name'=>$this->params['name'].'_form'.$name, 'default'=>$this->selectionValues[$name], 'onchange'=>$this->params['name'].'.update();'));
      break;
    case 'select' :
      /* selector type is a select dropbox */
      echo $this->selectorForm->display_selectInput(array('name'=>$this->params['name'].'_form'.$name, 'default'=>$this->selectionValues[$name], 'values'=>$selector['values'], 'onchange'=>$this->params['name'].'.update();'));
      break;
    case 'text' :
      /* selector type is a text field */
      echo $this->selectorForm->display_textInput(array('name'=>$this->params['name'].'_form'.$name, 'maxlength'=>128, 'default'=>$this->selectionValues[$name], 'onblur'=>$this->params['name'].'.update();'));
      break;
    }
    
    /* end item box */
    echo '</div>';
    echo '</div>';
  }

  echo '</div>';
  echo '<input type="submit" style="display:none" />';
  echo $this->selectorForm->display_footer();
}
?>