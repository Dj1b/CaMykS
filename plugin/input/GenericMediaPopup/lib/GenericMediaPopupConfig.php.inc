<?php
/**
 * @brief GenericMediaPopup Input configuration object
 * @details Plugin / Input Library
 * @file plugin/input/GenericMediaPopup/lib/GenericMediaPopupConfig.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Mar 2018
 * @date Modification: Apr 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GenericMediaPopupConfig PluginConfig class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class GenericMediaPopupConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);
        
        $this->add_newItem('insertion', 'int', 0);    // 0 : manual / 1 : automatic
        $this->add_newItem('styleSource', 'string', 'plugin');     // plugin / theme
        
        /* controls */
        $this->add_newItem('clickBkgdToClose', 'int', 1);
        $this->add_newItem('enableCloseButton', 'int', 1);
        $this->add_newItem('enableKeyboard', 'int', 1);
        $this->add_newItem('maxWidth', 'int', 0);
        
        /* diaporama controls */
        $this->add_newItem('enableDiaporama', 'int', 1);
        $this->add_newItem('diaporamaButtonsShift', 'int', 0);
        
        /* flash controls */
        $this->add_newItem('enableFlash', 'int', 0);
        $this->add_newItem('flvControlerColor', 'string', '1F1F1F');
        $this->add_newItem('flvControlerAlpha', 'float', 0.85);
        $this->add_newItem('flvControlerHeight', 'float', 20);
        
        /* generic initialisation */
        parent::init_config();
    }
    
    /* specific tool methods */
    
    /**
     * Return insertion value list.
     * @return array
     */
    public function get_insertionList() {
        return array(
            0 => $this->get_translation('insertion_manual'),
            1 => $this->get_translation('insertion_automatic'),
        );
    }
    
    /**
     * Return insertion value title.
     * @return string
     */
    public function get_insertionTitle() {
        $l = $this->get_insertionList();
        return $l[$this->vars['insertion']];
    }
    
    /**
     * Return style source value list.
     * @return array
     */
    public function get_styleSourceList() {
        return array(
            'plugin'    => $this->get_translation('stylesource_plugin'),
            'theme'     => $this->get_translation('stylesource_theme'),
        );
    }
    
    /**
     * Return style source value title.
     * @return string
     */
    public function get_styleSourceTitle() {
        $l = $this->get_styleSourceList();
        return $l[$this->vars['styleSource']];
    }
}
?>