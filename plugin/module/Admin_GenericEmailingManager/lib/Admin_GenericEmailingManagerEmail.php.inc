<?php
/**
 * @brief Admin_GenericEmailingManager module, email library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Dec 2012
 * @date Modification: Jul 2025
 * @copyright 2012 - 2015 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManagerEmail class.
 */
final class Admin_GenericEmailingManagerEmail extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* content */
        $this->add_newItem('emailing', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('source', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('contact', 'db', 'int', 'bigint unsigned', '', 0);

        $this->add_newItem('sent_status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('sent_date', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('opened_status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('opened_date', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('click_count', 'db', 'int', 'smallint unsigned', '', 0);
        $this->add_newItem('firstclick_date', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('unsubscribe_status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('invalid_status', 'db', 'int', 'tinyint unsigned', '', 0);

        $this->add_newItem('title', 'temp', 'string', '', '', '');
        $this->add_newItem('email', 'temp', 'string', '', '', '');

        /* generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Build SQL condition
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();
        $search[] = 'emailing='.$this->_libParent->emailingItem->id;
        if (isset($params['search']) and $params['search'] != '') {
            $contactIds = $this->_libParent->get_contactIdList(array('search' => $params['search']));
            if (count($contactIds) == 0)
                $search[] = 'false';
            elseif (count($contactIds) == 1)
                $search[] = 'contact = '.$contactIds[0];
            else
                $search[] = 'contact in ('.implode(', ', $contactIds).')';
        }

        /* Return fixed params */
        return implode(' and ', $search);
    }

    /* Mark: Specific methods */

    /**
     * Return emailing statistics summary.
     * @param integer $emailing
     * @return array
     */
    public function get_statisticsSummary($emailing) {
        /* Build sql query */
        $sql = 'select count(id) as total_built, sum(sent_status) as total_sent, sum(opened_status) as total_opened, sum(click_count) as total_clicks, sum(unsubscribe_status) as total_unsubscribed, sum(invalid_status) as total_invalid';
        $sql .= ' from '.$this->_libSQLTable;
        $sql .= ' where emailing='.$emailing;

        if ($this->execute_DBQuery($sql, __LINE__))
            /* Get result of sql query */
            if ($data = $this->get_DBQueryDataLine())
                return $data;
        return array();
    }

    /**
     * Return status icon.
     * @return string
     */
    public function get_statusIcon() {
        if ($this->vars['invalid_status'] == 1)
            return '<img src="'.$this->_libParent->theme->get_pictURL('minus', 12, 'std').'" alt="" border="0" />';
        if ($this->vars['unsubscribe_status'] == 1)
            return '<img src="'.$this->_libParent->theme->get_pictURL('cross', 12, 'std').'" alt="" border="0" />';
        if ($this->vars['opened_status'] == 0)
            return '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />';
        if ($this->vars['sent_status'] == 0)
            return '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />';
        return '<img src="'.$this->_libParent->theme->get_pictURL('valid', 12, 'std').'" alt="" border="0" />';
    }

    /**
     * Return sent date value.
     * @return string
     */
    public function get_sentDateValue() {
        global $camyks;
        if ($this->vars['sent_status'] == 0)
            return $camyks->get_translation('no');
        return date_displayNumericDateHour($this->vars['sent_date']);
    }

    /**
     * Return opened date value.
     * @return string
     */
    public function get_openedDateValue() {
        global $camyks;
        if ($this->vars['opened_status'] == 0)
                return $camyks->get_translation('no');
        return date_displayNumericDateHour($this->vars['opened_date']);
    }

    /**
     * Return first click date value
     * @return string
     */
    public function get_firstClickDateValue() {
        if ($this->vars['click_count'] == 0)
                return '--';
        return date_displayNumericDateHour($this->vars['firstclick_date']);
    }

    /**
     * Update email as unsubscribed.
     * @param integer $emailingId
     * @return boolean result
     */
    public function update_asUnsubscribed($emailingId) {
        if (!$this->get())
            return false;
        $this->get_fromItems();

        /* Check emailing value */
        if ($this->vars['emailing'] != $emailingId)
            return false;

        /* Update email value */
        $this->_libItems['unsubscribe_status']->value = 1;
        return $this->update_databaseSpecificItems(array('unsubscribe_status'));
    }

    /**
     * Mark email as invalid.
     * @return boolean result
     */
    public function mark_asInvalid() {
        /* update invalid status */
        $this->_libItems['invalid_status']->value = 1;

        /* update open status (may be opened by server) */
        $this->_libItems['opened_status']->value = 0;
        $this->_libItems['opened_date']->value = 0;

        return $this->update_databaseSpecificItems(array('invalid_status', 'opened_status', 'opened_date'));
    }
}
?>
