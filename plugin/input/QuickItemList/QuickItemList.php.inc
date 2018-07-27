<?php
/**
 * @brief QuickItemList Input
 * <br /> Allows multi selection in a list.
 * @details Plugin / Input Engine
 * @file plugin/input/QuickItemList/QuickItemList.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2007
 * @date Modification: Jul 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * QuickItemList Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class QuickItemList extends Input {

    /**
     * var string $objectName
     * @brief HTML object main name.
     */
    protected $objectName;

    /**
     * var string $fullListName
     * @brief HTML object full list name.
     */
    protected $fullListName;

    /**
     * var array $fullListItems
     * @brief HTML object full list items.
     */
    protected $fullListItems;

    /**
     * var string $editListName
     * @brief HTML object edit list name.
     */
    protected $editListName;

    /**
     * var string $editListItems
     * @brief HTML object edit list items.
     */
    protected $editListItems;

    /**
     * var string $form
     * @brief HTML form name.
     */
    protected $form;

    /**
     * var string $formItemName
     * @brief HTML form item name.
     */
    protected $formItemName;

    /**
     * var string $formItemSep
     * @brief HTML form item separator.
     */
    protected $formItemSep;

    /**
     * Class constructor.
     * @param string $path_type
     * @return void
     */
    public function __construct($path_type) {
        parent::__construct('QuickItemList', $path_type);

        /* overwrite Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite Input methods */

    /**
     * Initialise input.
     * @param string $n the object name
     * @param string $fln the full list name
     * @param array $fli the full list items
     * @param string $eln the edited list name
     * @param array $eli the edited list items
     * @param string $f the form name
     * @param string $fin the form item
     * @param string $fis the form item separator value
     * @return void
     */
    public function initialise ($n='', $fln='', $fli=array(), $eln='', $eli=array(), &$f=null, $fin=null, $fis=',') {
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
        $this->add_JSEngineFile ('tool/array.js');
        $this->add_JSFile ('quickitemlist.js');
        /* set javascript object */
        $this->add_JSScript ($this->objectName.' = new QuickItemList("'.$this->objectName.'");');
        /* set javascript object values */
        foreach ($this->fullListItems as $i) {
            $this->add_JSScript($this->objectName.'.add_fullListItem("'.$i->login.'");');
        }
        foreach ($this->editListItems as $i) {
            $this->add_JSScript($this->objectName.'.add_editListItem("'.$i.'");');
        }
        $this->add_JSScript($this->objectName.'.add_formValue("'.$this->formName.'","'.$fin.'");');
        $this->add_JSScript($this->objectName.'.add_separatorValue("'.$fis.'");');

        /* send icons */
        $this->add_JSScript($this->objectName.'.set_iconURL("plus", "'.$camyks->theme->get_pictURL('plus', 12, 'std').'");');
        $this->add_JSScript($this->objectName.'.set_iconURL("plus_over", "'.$camyks->theme->get_pictURL('plus', 12, 'ovr').'");');

        $this->add_JSScript($this->objectName.'.set_iconURL("minus", "'.$camyks->theme->get_pictURL('minus', 12, 'std').'");');
        $this->add_JSScript($this->objectName.'.set_iconURL("minus_over", "'.$camyks->theme->get_pictURL('minus', 12, 'ovr').'");');

        /* set object initialization on page load */
        $this->add_JSLoadScript($this->objectName.'.initialise();');

        /* Input generic initialization */
        parent::initialise();
    }
}
?>
