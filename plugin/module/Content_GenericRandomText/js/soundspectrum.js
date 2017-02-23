/*
        Camyks Engine
        Company                 : skymac.org
        Author                  : sky
        Camyks Version          : 1.0a
        Object Version          : 1.0
        Object Type             : Plugin / Module Javascript
        Creation Date           : Mar 2007
        Last Modif Date         : Mar 2007
        SoundSpectrum javascript object
*/

function SoundSpectrum ( name ) {
    /* vars */
    this.name = name;

    /* conf vars */
    this.animspeed = 100;
    this.cellfirstcolor = '9DCFAB';
    this.celllastcolor = '3DD668';
    this.cellbgcolor = 'F0F0F0';
    this.tablecols = 6;
    this.tablerows = 6;
    
    /* execution vars */
    this.values = null;
    this.colors = null;
    this.interval = null;
}

SoundSpectrum.prototype.initialise = function ( ) {
    /* init values */
    this.values = new Array();
    for ( i=0; i<this.tablecols; i++ )
      this.values[i] = 0;
    /* init colors */
    this.colors = color_getColorRange ( this.cellfirstcolor, this.celllastcolor, this.tablerows-1 );
}

SoundSpectrum.prototype.start = function ( ) {
    this.interval = setInterval( this.name+'.update();', this.animspeed);
}

SoundSpectrum.prototype.stop = function ( ) {
    clearInterval ( this.interval );
}

SoundSpectrum.prototype.update = function ( ) {
    for ( var i=0; i<this.tablecols; i++ ) {
	diff = parseInt(3*Math.random())-1;
	if ( diff == -1 && this.values[i] > 0 ) {
	    document.getElementById(this.name+'_cell_'+i+'_'+this.values[i]).style.background='#'+this.cellbgcolor;
	    this.values[i]--;
	} else if ( diff == 1 && this.values[i] < this.tablerows-1 ) {
	    this.values[i]++;
	    document.getElementById(this.name+'_cell_'+i+'_'+this.values[i]).style.background='#'+this.colors[this.values[i]];
	}
    }
}