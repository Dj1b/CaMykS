<?php
/*
 * CaMykS Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Module Config
 * Creation Date    : Sep 2010
 * Last Modif Date  : Sep 2010
 *
 * Admin_GenericContactFormManager configuration file
 */

class Admin_GenericContactFormManagerConfig extends ModuleConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  function Admin_GenericContactFormManagerConfig ( $name, &$parent ) {
    parent::ModuleConfig($name, $parent);

    /* site configuration */
    $this->add_newItem('notification_status', 'integer', 0);
    $this->add_newItem('notification_sender', 'sender', '');
    $this->add_newItem('notification_recipients', 'array', array());

    $this->add_newItem('statistic_status', 'intger', 0);

    /* generic initialisation */
    parent::init_config();
  }

  /* specific tool methods */
  
  /*
   * return notification status list
   * @return array
   * @access private
   */
  function get_notificationStatusList() {
    return array(0 => $this->get_translation('confignotifstatus_disabled'),
		 1 => $this->get_translation('confignotifstatus_enabled'));
  }

  /*
   * return notifications status value
   * @param integer $value
   * @return string
   * @access private
   */
  function get_notificationStatusValue($value=false) {
    $l = $this->get_notificationStatusList();
    if ($value===false)
      return $l[$this->vars['notification_status']];
    return $l[$value];
  }

  /*
   * return notifications reciepients value
   * @return string
   * @access private
   */
  function get_notificationRecipientsValue() {
    global $camyks;
    
    if ( count($this->vars['notification_recipients']) == 0)
      return $this->get_translation('confignotifrecipient_none');

    $s = array();
    $users = $camyks->modules['Admin_User']->get_activeUserList(true);
    foreach ($this->vars['notification_recipients'] as $login) {
      if (isset($users[$login]))
	$s[] = $users[$login]->get_nameDisplay();
    }
    return implode(', ', $s);
  }

  /*
   * return statistic status list
   * @return array
   * @access private
   */
  function get_statisticStatusList() {
    return array(0 => $this->get_translation('configstatstatus_disabled'),
		 1 => $this->get_translation('configstatstatus_enabled'));
  }

  /*
   * return notifications status value
   * @param integer $value
   * @return string
   * @access private
   */
  function get_statisticStatusValue($value=false) {
    $l = $this->get_statisticStatusList();
    if ($value===false)
      return $l[$this->vars['statistic_status']];
    return $l[$value];
  }
}
?>