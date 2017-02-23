/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * Camyks Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Javascript Library
 * Create Date		: Jul 2007
 * Last Modif Date	: Jul 2007
 *
 * PageChooser javascripts methods
 */

function PageChooser ( mode, callback, popurl ) {
  this.mode = mode;
  if (callback == null || callback == '')
    this.callback = 'pc.update_selectedPage';
  else
    this.callback = callback;
  this.popurl = popurl;
  this.selectedInput = null;
  
  /*
   * open page chooser
   * @param mixed $page
   * @return void
   * @access public
   */
  this.open = function(page, language) {
  	/* define popup url */
  	url = this.popurl+'&pc_mode='+this.mode+'&pc_callback='+this.callback+'&pc_page='+page;
  
  	/* check current language */
  	if (language)
  		url += '&pc_lg='+language;
  	
  	/* open popup */
  	pcw = window.open( url, '',
		    'width=750,height=530,scrollbars=auto,resize=no,toolbar=no,menubar=no,personalbar=no');
  	if ( pcw ) {
    	pcw.focus();
  	}
  };
  
  /*
   * old alias for open method
   * @param mixed page
   * @access public
   */
  this.openPageChooser = function(page) {
  	this.open(page);
  };
  
  /*
   * select page from given input id
   * @param string obj
   * @return void
   * @access public
   */
  this.select_page = function(obj) {
    if (document.getElementById(obj)) {
      this.selectedInput = obj;
      this.open(document.getElementById(obj).value);
    }
  };
 
  /*
   * update selected input
   * @param mixed page
   * @return void
   * @access public
   */
  this.update_selectedPage = function(page) {
    if (this.selectedInput != null && document.getElementById(this.selectedInput)) {
      document.getElementById(this.selectedInput).value = page;
    }
  };
}