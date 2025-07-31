<?php
/**
 * @brief Content_GenericLegalMentions module, content library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jan 2020
 * @date Modification: Jul 2025
 * @copyright 2020 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Content_GenericLegalMentionsItem class.
 */
final class Content_GenericLegalMentionsItem extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Admin items */
        $this->add_newItem('name', 'db', 'text', 'varchar', 32, '');
        $this->add_newItem('updateDate', 'db', 'date', 'bigint unsigned', '', 0);

        /* Properties items - owner */
        $this->add_newItem('owner_name', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('owner_type', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('owner_managername', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('owner_manageremail', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('owner_address', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('owner_phone', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('owner_fax', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('owner_email', 'db', 'text', 'varchar', 255, '');

        $this->add_newItem('owner_company_legalform', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('owner_company_capital', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('owner_company_vat', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('owner_company_siret', 'db', 'text', 'varchar', 24, '');
        $this->add_newItem('owner_company_rcsnum', 'db', 'text', 'varchar', 24, '');
        $this->add_newItem('owner_company_rcsloc', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('owner_company_naf', 'db', 'text', 'varchar', 24, '');

        $this->add_newItem('owner_additional', 'db', 'text', 'text', '', '', true);

        /* Properties items - creator */
        $this->add_newItem('creator_name', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('creator_address', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('creator_phone', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('creator_fax', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('creator_email', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('creator_website', 'db', 'text', 'varchar', 255, '');

        /* Properties items - webmaster */
        $this->add_newItem('webmaster_name', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('webmaster_email', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('webmaster_company', 'db', 'text', 'varchar', 255, '');

        /* Properties items - DPO */
        $this->add_newItem('dpo_name', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('dpo_email', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('dpo_company', 'db', 'text', 'varchar', 255, '');

        /* Properties items - host */
        $this->add_newItem('host_name', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('host_address', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('host_phone', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('host_fax', 'db', 'text', 'varchar', 16, '');
        $this->add_newItem('host_email', 'db', 'text', 'varchar', 255, '');
        $this->add_newItem('host_website', 'db', 'text', 'varchar', 255, '');

        /* Properties items - law */
        $this->add_newItem('law_tribunal', 'db', 'text', 'varchar', 64, '');

        /* Properties items - additional content */
        $this->add_newItem('additional_content', 'db', 'text', 'text', '', '', true);

        /* Temporary items */
        $this->add_newItem('defaultPage', 'temp', 'int', '', '', 0);

        /* generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Load object from database.
     * @param string $language
     * @return boolean success
     */
    public function get($language=true) {
        global $camyks;

        if (!parent::get($language))
            return false;

        if (isset($this->_libParent->page_id))
            $this->_libItems['defaultPage']->value = (int)($camyks->modules['Admin_ContentPage']->get_keyPage('LegalMentions') === $this->_libParent->page_id);

        return true;
    }

    /**
     * Save object to database.
     * @return boolean success
     */
    public function save() {
        global $camyks;

        /* Save object */
        if (!parent::save())
            return false;

        /* Define page as default legal mentions page */
        if ($this->_libItems['defaultPage']->value === 1) {
            $camyks->modules['Admin_ContentPage']->set_keyPage('LegalMentions', $this->_libParent->page_id);
        }

        /* Return success */
        return true;
    }

    /**
     * Check object data.
     * @return boolean result
     */
    public function check_data() {
        /* Check symbolic name value */
        $this->_libItems['name']->check_value('symbolic_name', 'legalmentions');

        /* Update last update date */
        $this->_libItems['updateDate']->value = time();

        /* Return success */
        return true;
    }

    /* Mark: Specific data methods */

    /**
     * Return owner type list.
     * @return array
     */
    public function get_ownerTypeList() {
        return array(
            0 => $this->get_translation('ownertype_company'),
            1 => $this->get_translation('ownertype_association'),
            2 => $this->get_translation('ownertype_publicestablishment'),
            11 => $this->get_translation('ownertype_individual'),
        );
    }

    /**
     * Return owner full type list.
     * @return array
     */
    public function get_ownerFullTypeList() {
        return array(
            0 => $this->get_translation('ownertype_thecompany'),
            1 => $this->get_translation('ownertype_theassociation'),
            2 => $this->get_translation('ownertype_thepublicestablishment'),
        );
    }

    /**
     * Return owner full type title.
     * @return string
     */
    public function get_ownerFullTypeTitle() {
        $l = $this->get_ownerFullTypeList();
        if (isset($l[$this->vars['owner_type']]))
            return $l[$this->vars['owner_type']];
        return '';
    }

    /**
     * Return website url display.
     * @return string
     */
    public function get_websiteURL() {
        global $camyks;
        return url_getAsSmart($camyks->get_confValue('url'));
    }

    /**
     * Return editor full name.
     * @return string
     */
    public function get_editorFullName() {
        $s = '';
        switch ($this->vars['owner_type']) {
            case 0: $s .= $this->get_translation('ownertype_thecompany'); break;
            case 1: $s .= $this->get_translation('ownertype_theassociation'); break;
            case 2: $s .= $this->get_translation('ownertype_thepublicestablishment'); break;
            default:
        }
        return $s.' '.$this->vars['owner_name'];
    }

    /* Mark: Specific check methods */

    /**
     * Check if given value is defined.
     * @return boolean
     */
    public function has_content($value) {
        if (!isset($this->vars[$value]))
            return false;
        if (trim($this->vars[$value]) == '')
            return false;
        return true;
    }

    /**
     * Check if type is individual.
     * @return boolean
     */
    public function is_individual() {
        return ($this->vars['owner_type'] == 11);
    }

}
?>
