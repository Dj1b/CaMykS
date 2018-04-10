<?php
/**
 * @brief CaMykS required plugins configuration
 * @brief Automatically loaded by CaMykS object.
 * @details Engine / Configuration file
 * @file engine/etc/neededPlugins.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Jun 2005
 * @date Modification: Apr 2018
 * @copyright 2005 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * @var array $this->neededModules
 * @brief CaMykS required module list
 */
$this->neededModules = array(
    'Tool_Login'            => array('name'=>'Tool_Login', 'version'=>'1.0'),
    'Tool_ControlPanel'     => array('name'=>'Tool_ControlPanel', 'version'=>'1.0'),
    'Tool_InfoBar'          => array('name'=>'Tool_InfoBar', 'version'=>'1.0'),
    'Tool_Disconnect'       => array('name'=>'Tool_Disconnect', 'version'=>'1.0'),
    'Admin_User'            => array('name'=>'Admin_User', 'version'=>'1.0'),
    'Admin_Group'           => array('name'=>'Admin_Group', 'version'=>'1.0'),
    'Admin_Site'            => array('name'=>'Admin_Site', 'version'=>'1.0'),
    'Admin_ContentPage'     => array('name'=>'Admin_ContentPage', 'version'=>'1.0'),
    'Admin_PluginManager'   => array('name'=>'Admin_PluginManager', 'version'=>'1.0'),
);

/**
 * @var array $this->neededInputs
 * @brief CaMykS required input list
 */
$this->neededInputs = array();

/**
 * @var array $this->neededTemplates
 * @brief CaMykS required template list
 */
$this->neededTemplates = array(
    'AdminPage'             => array('name'=>'AdminPage', 'version'=>'1.0'),
);

/**
 * @var array $this->neededThemes
 * @brief CaMykS required theme list
 */
$this->neededThemes = array();

/* add site configuration plugins */
if ($this->get_confValue('admin_default_theme') != '')
  $this->neededThemes[$this->get_confValue('admin_default_theme')] = array('name'=>$this->get_confValue('admin_default_theme'), 'version'=>'1.0');

if ($this->get_confValue('site_default_theme') != '')
  $this->neededThemes[$this->get_confValue('site_default_theme')] = array('name'=>$this->get_confValue('site_default_theme'), 'version'=>'1.0');

if ($this->get_confValue('site_default_template') != '')
  $this->neededTemplates[$this->get_confValue('site_default_template')] = array('name'=>$this->get_confValue('site_default_template'), 'version'=>'1.0');
?>