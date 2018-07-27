<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version	: 1.0.1
 * Object Type      : Plugin / Input Config
 * Creation Date	: Jan 2018
 * Last Modif Date	: Jul 2018
 *
 * SocialNetworksSharingPanel configuration object
 */

final class SocialNetworksSharingPanelConfig extends PluginConfig {
  /*
   * constructor
   * @param string $name
   * @param Module $parent
   */
  public function SocialNetworksSharingPanelConfig($name, &$parent) {
    parent::__construct($name, $parent);

    $dnetworks = array('facebook', 'twitter', 'gplus', 'linkedin');

    /* sharing params */
    foreach ($parent->networks as $network => $data) {
      if ($data['share'] == 1)
        $this->add_newItem('share_'.$network, 'integer', in_array($network, $dnetworks)? 1 : 0);
    }

    $this->add_newItem('like_facebook', 'integer', 0);
    $this->add_newItem('like_facebookLayout', 'string', 'standard');
    $this->add_newItem('like_facebookSize', 'string', 'small');
    $this->add_newItem('like_facebookAction', 'string', 'like');

    $this->add_newItem('share_pictureFormat', 'string', 'gif');

    /* follow params */
    foreach ($parent->networks as $network => $data)
      if ($data['follow'] == 1)
        $this->add_newItem('follow_'.$network, 'string', '');

    $this->add_newItem('follow_insertion', 'int', 0);  // 0 : manual / 1 : automatic
    $this->add_newItem('follow_styleSource', 'string', 'plugin');   // plugin / theme
    $this->add_newItem('follow_location', 'string', 'fixed-left'); // left / right

    $this->add_newItem('follow_pictureFormat', 'string', 'png');

    /* set up variables */
    $this->sharingValues = false;
    $this->likeValues = false;

    /* generic initialisation */
    parent::init_config();
  }

  /* generic tool methods */

  /*
   * return picture format value list
   * @return array
   */
  public function get_pictureFormatList() {
    return array(
      'gif' => 'GIF (.gif)',
      'png' => 'PNG (.png)',
      'jpg' => 'JPG (.jpg)',
    );
  }

  /*
   * return picture format value
   * @param string $mode
   * @return string
   */
  public function get_pictureFormatValue($mode='') {
    if (!isset($this->vars[$mode.'_pictureFormat']))
      return '';
    $list = $this->get_pictureFormatList();
    return $list[$this->vars[$mode.'_pictureFormat']];
  }

  /* sharing tool methods */

  /*
   * return sharing network value list
   * @return array
   * @access public
   */
  public function get_sharingNetworkList() {
    return array(
      0 => $this->get_translation('share_disabled'),
      1 => $this->get_translation('share_primary'),
      2 => $this->get_translation('share_secondary'),
    );
  }

  /*
   * return sharing network value
   * @param string $network
   * @return string
   * @access public
   */
  public function get_sharingNetworkValue($network='') {
    if (!isset($this->vars['share_'.$network]))
      return '';
    if ($this->sharingValues == false)
      $this->sharingValues = $this->get_sharingNetworkList();
    return $this->sharingValues[$this->vars['share_'.$network]];
  }

  /*
   * return network like value list
   * @return array
   * @access public
   */
  public function get_networkLikeList() {
    return array(
      0 => $this->get_translation('like_disabled'),
      1 => $this->get_translation('like_enabled'),
    );
  }

  /*
   * return network like value
   * @param string $network
   * @return string
   * @access public
   */
  public function get_networkLikeValue($network='') {
    if (!isset($this->vars['like_'.$network]))
      return '';
    if ($this->likeValues == false)
      $this->likeValues = $this->get_networkLikeList();
    return $this->likeValues[$this->vars['like_'.$network]];
  }

  /* facebook specific methods */

  /*
   * return facebook layout list
   * @return array
   * @access public
   */
  public function get_facebookLayoutList() {
    return array(
        'standard'      => 'standard',
        'box_count'     => 'box_count',
        'button_count'  => 'button_count',
        'button'        => 'button',
    );
  }

  /*
   * return facebook size list
   * @return array
   * @access public
   */
  public function get_facebookSizeList() {
    return array(
        'large'     => 'large',
        'small'     => 'small',
    );
  }

  /*
   * return facebook action list
   * @return array
   * @access public
   */
  public function get_facebookActionList() {
    return array(
        'like'      => 'like',
        'recommend' => 'recommend',
    );
  }

  /* follow related methods */

  /*
   * return follow insertion value list
   * @return array
   * @access public
   */
  public function get_followInsertionList() {
    return array(
      0 => $this->get_translation('followinsertion_manual'),
      1 => $this->get_translation('followinsertion_automatic'),
    );
  }

  /*
   * return insertion value title
   * @return string
   * @access public
   */
  public function get_followInsertionTitle() {
    $l = $this->get_followInsertionList();
    return $l[$this->vars['follow_insertion']];
  }

  /*
   * return style source value list
   * @return array
   * @access public
   */
  public function get_followStyleSourceList() {
    return array(
      'plugin'  => $this->get_translation('followstylesource_plugin'),
      'theme'   => $this->get_translation('followstylesource_theme'),
    );
  }

  /*
   * return style source value title
   * @return string
   * @access public
   */
  public function get_followStyleSourceTitle() {
    $l = $this->get_followStyleSourceList();
    return $l[$this->vars['follow_styleSource']];
  }

  /*
   * return location value list
   * @return array
   * @access public
   */
  public function get_followLocationList() {
    return array(
      'fixed-left'        => $this->get_translation('followlocation_fixedleft'),
      'fixed-right'       => $this->get_translation('followlocation_fixedright'),
    );
  }

  /*
   * return location value title
   * @return string
   * @access public
   */
  public function get_followLocationTitle() {
    $l = $this->get_followLocationList();
    return $l[$this->vars['follow_location']];
  }
}
?>
