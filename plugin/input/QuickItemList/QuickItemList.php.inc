<?php
/*
 * CaMykS Engine
 * Developed by	       	: camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   	: 1.0a
 * Object Version       : 1.0
 * Object Type          : Plugin / Input Engine
 * Creation Date       	: Mar 2007
 * Last Modif Date	: Mar 2007
 * History : 
 * * 07-03-xx : Initial Files
 *   
 * QuickItemList input : Dynamic list editor
*/

class QuickItemList extends Input {
  /* variables */
  var $objectName;
  var $fullListName;
  var $fullListItems;
  var $editListName;
  var $editListItems;
  var $form;
  var $formItemName;
  var $formItemSep;

  /*
   * constructor
   * @param string $path_list
   */
  function QuickItemList ( $path_type ) {
    parent::Input('QuickItemList', $path_type);
    /* set plugin version */
    $this->version = '1.0';
    /* set plugin package */
    $this->plugin_package = 'Default';
    /* set plugin author */
    $this->author_name = 'CaMykS Team';
    $this->author_mail = 'camyks.contact@gmail.com';
    $this->author_group = 'camyks.net';
  }
  
  /* overwrite input methods */


  /* 
   * initialise input
   * @param string $n the object name
   * @param string $fln the full list name
   * @param array $fli the full list items
   * @param string $eln the edited list name
   * @param array $eli the edited list items
   * @param string $f the form name
   * @param string $fin the form item
   * @param string $fis the form item separator value
   * @return void
   * @access public
   */
  function initialise ( $n='', $fln='', $fli=array(), $eln='', $eli=array(), &$f=null, $fin=null, $fis=',' ) {
    global $camyks;
    /* set name value */
    $this->objectName = $n;
    /* set full list values */
    $this->fullListName = $fln;
    $this->fullListItems = $fli;
    /* set edit list values */
    $this->editListName = $eln;
    $this->editListItems = $eli;
    /* set form values */
    $this->formName = $f;
    $this->formItemName = $fin;
    $this->formItemSep = $fis;

    /* set javascript file */
    $this->add_JSEngineFile ( 'tool/array.js' );
    $this->add_JSFile ( 'quickitemlist.js' );
    /* set javascript object */
    $this->add_JSScript ( $this->objectName.' = new QuickItemList("'.$this->objectName.'");' );
    /* set javascript object values */
    foreach ( $this->fullListItems as $i ) {
      $this->add_JSScript ( $this->objectName.'.add_fullListItem("'.$i->login.'");' );
    }
    foreach ( $this->editListItems as $i ) {
      $this->add_JSScript ( $this->objectName.'.add_editListItem("'.$i.'");' );
    }
    $this->add_JSScript ( $this->objectName.'.add_formValue("'.$this->formName.'","'.$fin.'");' );
    $this->add_JSScript ( $this->objectName.'.add_separatorValue("'.$fis.'");' );

    /* send icons */
    $this->add_JSScript($this->objectName.'.set_iconURL("plus", "'.$camyks->theme->get_pictURL('plus', 12, 'std').'");');
    $this->add_JSScript($this->objectName.'.set_iconURL("plus_over", "'.$camyks->theme->get_pictURL('plus', 12, 'ovr').'");');

    $this->add_JSScript($this->objectName.'.set_iconURL("minus", "'.$camyks->theme->get_pictURL('minus', 12, 'std').'");');
    $this->add_JSScript($this->objectName.'.set_iconURL("minus_over", "'.$camyks->theme->get_pictURL('minus', 12, 'ovr').'");');


    /* set object initialization on page load */
    $this->add_JSLoadScript ( $this->objectName.'.initialise();' ); 

    /* Input generic initialization */
    parent::initialise();
  }
 
  /*
   * display input
   * @return void
   * @access public
   */
  function display ( ) {
    /* Input generic display */
    parent::display();
  }  
}
?>