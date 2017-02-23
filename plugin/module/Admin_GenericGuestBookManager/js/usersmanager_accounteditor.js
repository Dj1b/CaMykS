/*
 * CaMykS Engine
 * Developed by	       	: skymac.org
 * Author	       	: sky
 * CaMykS Version   	: 1.0a2
 * Object Version       : 1.0
 * Object Type          : Plugin / Module Javascript
 * Create Date		: Jan 2009
 * Last Modif Date	: Jan 2009
 * 
 * UsersManager Account Editor scripts
 */

function AccountEditor(name, form) {
  this._name = name;
  this._form = form;
  this._passwordPanel = null;

  /*
   * initialisation method
   * @return void
   * @access public
   */
  this.initialise = function() {
    /* get form object */
    this._form = eval('document.'+this._form);

    /* get password panel element */
    if (document.getElementById('password_panel'))
      this._passwordPanel = document.getElementById('password_panel');

  }    

  /*
   * update password panel status
   * return void
   * @access public
   */
  this.update_passwordPanel = function() {
    /* get change password value */
    change = this._form.change_password.options[this._form.change_password.options.selectedIndex].value;
    if ( this._passwordPanel )
      this._passwordPanel.style.display = (change==1?'block':'none');
  }
}
