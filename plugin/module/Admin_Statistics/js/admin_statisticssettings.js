/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team
 * CaMykS Version	: 1.0b1
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Scripts
 * Create Date	       	: Oct 2009
 * Last Modif Date	: Oct 2009
 *
 * Admin_Statistics Settings editor javascript
 */

function StatisticsSettingsEditor (name) {
  this.name = name;
  this.loaded = false;
  this.form = null;
  this.ipbox = null;
  this.ipadder = null;
  this.ipcount = null;
  this.bttn = null;
  this.bttn_ = null;

  /*
   * initialise object
   * @return void
   * access private
   */
  this.initialise = function(form) {
    /* check form object */
    if (!document.getElementById(form))
      return;
    this.form = document.getElementById(form);

    /* get ip counter */
    if (!this.form.stat_filteredips_count_)
      return;
    this.ipcount = this.form.stat_filteredips_count_;

    /* check filtered ips box */
    if (!document.getElementById('filteredips'))
      return;
    this.ipbox = document.getElementById('filteredips');

    /* check filtered ip adder */
    if (!this.form.ipadder)
      return;
    this.ipadder = this.form.ipadder;

    /* set object loaded */
    this.loaded = true;
  }

  /*
   * add a filtered ip from adder input
   * @return void
   * @access private
   */
  this.add_filteredIp = function() {
    if (!this.loaded)
      return;
    
    line = html_getTrElement();
    line.id = 'filteredipline'+this.ipcount.value;

    cell = html_getTdElement();
    line.appendChild(cell);
    cell.className = 'eTableLine0';
    cell.style.padding = '6px 4px';

    ip = html_getInputElement();
    ip.setAttribute('type', 'hidden');
    ip.setAttribute('name', 'stat_filteredips_'+this.ipcount.value);
    ip.setAttribute('value', this.ipadder.value);
    cell.appendChild(ip);
    cell.innerHTML += this.ipadder.value;
    this.ipadder.value = '';

    cell2 = html_getTdElement();
    cell2.className = 'eTableLine0';
    cell2.style.width = '12px';
    cell.style.padding = '6px 4px';
    
    img = html_getImgElement();
    img.setAttribute('border', 0);
    img.setAttribute('alt' , '');
    img.setAttribute('src', this.bttn);

    img.setAttribute('onclick', this.name+'.remove_filteredIp("'+this.ipcount.value+'")');
    img.setAttribute('onmouseover', 'this.src="'+ this.bttn_ + '";');
    img.setAttribute('onmouseout', 'this.src="' + this.bttn + '";');

    cell2.appendChild(img);
    line.appendChild(cell2);

    this.ipbox.appendChild(line);
  
    this.ipcount.value++;
  }

  /*
   * remove filtered ip line
   * @return void
   * @access private
   */
  this.remove_filteredIp = function(line) {
    if (this.loaded && (line=document.getElementById('filteredipline'+line))) {
      this.ipbox.removeChild(line);
    }
  }
}
