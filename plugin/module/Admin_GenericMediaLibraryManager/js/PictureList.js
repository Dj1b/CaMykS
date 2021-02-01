/**
 * @brief Admin_GenericMediaLibraryManager module picture list script
 * @details Plugin / Module Scripts
 * @author CaMykS Team
 * @version 1.0.1
 * @date Creation: Jun 2015
 * @date Modification: Jan 2019
 * @copyright 2015 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
function PictureList(name) {
  this.name = name;
  this.params = {};
  this.locales = {};
  this.loaded = false;

  /*
   * add parameter
   * @param string name
   * @param mixed value
   * @return void
   * @access public
   */
  this.set_param = function(param, value, subvalue) {
    if ( subvalue != undefined && this.params[param] )
      this.params[param][value] = subvalue;
    else
      this.params[param] = value;
  };

  /*
   * return param value from name
   * @param mixed param
   * @return mixed
   * @access public
   */
  this.get_param = function(param, value) {
    if (value != undefined)
      if (this.params[param][value])
        return this.params[param][value];
    if (this.params[param])
      return this.params[param];
    return false;
  };

  /*
   * set locale value
   * @param string name
   * @param string value
   * @return void
   * @access public
   */
  this.set_locale = function(name, value) {
    this.locales[name.toLowerCase()] = value;
  };

  /*
   * get locale value
   * @param string name
   * @return void
   * @access public
   */
  this.get_locale = function(name) {
    if (this.locales[name.toLowerCase()])
      return this.locales[name.toLowerCase()];
    return name;
  };

  /*
   * initialise object
   * @return void
   * @access public
   */
  this.initialise = function() {

	/* finalise initialisation */
    this.loaded = true;
  };

  /*
   * display picture preview
   * @return void
   * @access private
   */
  this.display_picturePreview = function(pId) {
    container = document.getElementById('picturePreview');
    container.innerHTML = '';

    img = document.createElement('img');
    img.src = this.get_param('picturesURL', pId);
    img.alt = '';
    img.style.maxWidth = this.get_param('previewMaxWidth')+'px';

    container.appendChild(img);
  };
}
