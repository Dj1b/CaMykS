<?php
/**
 * @brief Admin_GenericContactFormManager module, configuration library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Nov 2010
 * @date Modification: Jul 2025
 * @copyright 2010 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericContactFormManagerConfig class.
 */
final class Admin_GenericContactFormManagerConfig extends PluginConfig {
    /**
     * Class constructor.
     * @param string $name
     * @param Plugin $parent
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* site configuration */
        $this->add_newItem('notification_status', 'integer', 0);
        $this->add_newItem('notification_sender', 'sender', '');
        $this->add_newItem('notification_recipients', 'array', array());

        $this->add_newItem('statistic_status', 'intger', 0);

        /* generic initialisation */
        parent::init_config();
    }

    /* specific tool methods */

    /**
     * Return notification status list.
     * @return array
     */
    public function get_notificationStatusList() {
        return array(
            0 => $this->get_translation('confignotifstatus_disabled'),
            1 => $this->get_translation('confignotifstatus_enabled'),
        );
    }

    /**
     * Return notifications status value.
     * @param integer $value
     * @return string
     */
    public function get_notificationStatusValue($value=false) {
        $l = $this->get_notificationStatusList();
        if ($value === false)
            return $l[$this->vars['notification_status']];
        return $l[$value];
    }

    /**
     * Return notifications reciepients value.
     * @return string
     */
    public function get_notificationRecipientsValue() {
        global $camyks;

        if (count($this->vars['notification_recipients']) == 0)
            return $this->get_translation('confignotifrecipient_none');

        $s = array();
        $users = $camyks->modules['Admin_User']->get_activeUserList(true);
        foreach ($this->vars['notification_recipients'] as $login) {
            if (isset($users[$login]))
                $s[] = $users[$login]->get_nameDisplay();
        }
        return implode(', ', $s);
    }

    /**
     * Return statistic status list.
     * @return array
     */
    public function get_statisticStatusList() {
        return array(
            0 => $this->get_translation('configstatstatus_disabled'),
            1 => $this->get_translation('configstatstatus_enabled'),
        );
    }

    /**
     * Return notifications status value.
     * @param integer $value
     * @return string
     */
    public function get_statisticStatusValue($value=false) {
        $l = $this->get_statisticStatusList();
        if ($value === false)
            return $l[$this->vars['statistic_status']];
        return $l[$value];
    }
}
?>
