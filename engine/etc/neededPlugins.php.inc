<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0
 * Object Version	: 1.0
 * Object Type      : Engine / Configuration File
 * Creation Date	: Jun 2005
 * Last Modif Date	: Oct 2017
 * History :
 * 05-06-xx : Initial file
 * 08-01-07 : Update with new templates & themes names
 *
 * CaMykS Engine mandatory plugin list
 * Included in CaMykS object
*/

/* Modules */
$this->neededModules = array();
$this->neededModules['Tool_Login'] = array('name'=>'Tool_Login', 'version'=>'1.0');
$this->neededModules['Tool_ControlPanel'] = array('name'=>'Tool_ControlPanel', 'version'=>'1.0');
$this->neededModules['Tool_InfoBar'] = array('name'=>'Tool_InfoBar', 'version'=>'1.0');
$this->neededModules['Tool_Disconnect'] = array('name'=>'Tool_Disconnect', 'version'=>'1.0');


$this->neededModules['Admin_User'] = array('name'=>'Admin_User', 'version'=>'1.0');
$this->neededModules['Admin_Group'] = array('name'=>'Admin_Group', 'version'=>'1.0');
$this->neededModules['Admin_Site'] = array('name'=>'Admin_Site', 'version'=>'1.0');
$this->neededModules['Admin_ContentPage'] = array('name'=>'Admin_ContentPage', 'version'=>'1.0');
$this->neededModules['Admin_PluginManager'] = array('name'=>'Admin_PluginManager', 'version'=>'1.0');
//$this->neededModules['Dummy'] = array('name'=>'Dummy', 'version'=>'1.0');

/* Inputs */
$this->neededInputs = array();
//$this->neededInputs['TabBuilder'] = array('name'=>'TabBuilder', 'version'=>'1.0');

/* Templates */
$this->neededTemplates = array();
$this->neededTemplates['AdminPage'] = array('name'=>'AdminPage', 'version'=>'1.0');
//$this->neededTemplates['DefaultPage'] = array('name'=>'DefaultPage', 'version'=>'1.0');

/* Themes */
$this->neededThemes = array();
//$this->neededThemes['GreyStyle'] = array('name'=>'GreyStyle', 'version'=>'1.0');

/* add site configuration plugins */
if ($this->get_confValue('admin_default_theme') != '')
  $this->neededThemes[$this->get_confValue('admin_default_theme')] = array('name'=>$this->get_confValue('admin_default_theme'), 'version'=>'1.0');

if ($this->get_confValue('site_default_theme') != '')
  $this->neededThemes[$this->get_confValue('site_default_theme')] = array('name'=>$this->get_confValue('site_default_theme'), 'version'=>'1.0');

if ($this->get_confValue('site_default_template') != '')
  $this->neededTemplates[$this->get_confValue('site_default_template')] = array('name'=>$this->get_confValue('site_default_template'), 'version'=>'1.0');

?>