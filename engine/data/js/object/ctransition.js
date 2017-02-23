/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type		: Engine / JS Object Lib
 * Create Date		: Jul 2008
 * Last Modif Date	: Jul 2008
 * History :
 * * 08-07-09 : Initial File
 *
 * Transition factory
 */

var ctransition = new CTransition('ctransition');

/* 
 * CTransition Object
 * @param string name
 * @access public
 */
function CTransition(name) {
  /* vars */
  this._name = name;
  this._params = null;
  
  /* used vars */
  this._interval1 = null;
  this._interval2 = null;
  
  /* methods */
  
  /*
   * perform a transparent swap between panels
   * @param array params
   * * panel_out : string, panel to hide
   * * panel_in : string, panel to show
   * * steps : int, fade steps
   * * speed : int, time between 2 steps
   * * action : action to perform when panels are swapped
   * @return void
   * @access public
   */
  this.execute_transparentPanelSwap = function(params) {    
    /* check if params is an array */
    if (typeof(params) != 'object' )
      return;
      
    this._params = params;
    /* check params : panels */
    if ( (!this._params['panel_out'] || !document.getElementById(this._params['panel_out'])) 
      && (!this._params['panel_in'] || !document.getElementById(this._params['panel_in']))) {
      /* no panel defined : do nothing */
      return;
    } else if (!this._params['panel_out'] || !document.getElementById(this._params['panel_out'])) {
      /* no panel_out defined : perform a fade in on panel_in */
      return this.execute_transparentPanelFadeIn(params);
    } else if (!this._params['panel_in'] || !document.getElementById(this._params['panel_in'])) {
      /* no panel_in defined : perform a fade out on panel_out */
      return this.execute_transparentPanelFadeOut(params);
    }
        
    /* check params : optional params */
    if ( !this._params['steps'] || typeof(this._params['steps'])!='number' || this._params['steps'] < 0 )
      this._params['steps'] = 10;
    else
      this._params['steps'] = parseInt(this._params['steps']);
    if ( !this._params['speed'] || typeof(this._params['speed'])!='number' || this._params['speed'] < 0 )
      this._params['speed'] = 50;
    else
      this._params['speed'] = parseInt(this._params['speed']);
    this._params['progress'] = Math.round(100/this._params['steps'])/100;
    
    /* check panels status */
    p_out = document.getElementById(this._params['panel_out']);
    p_in = document.getElementById(this._params['panel_in']);
    
    if ( p_out.style.display === 'none' || p_out.style.opacity === 0 ) {
      if ( this._params['action'] ) {
        try {
          if ( typeof(this._params['action']) == 'string' )
            eval(this._params['action']);
          else if ( typeof(this._params['action']) == 'function')
            this._params['action']();
        } catch(e) {
          return;
        }
      }
      return;
    } else if ( !p_out.style.opacity) {
      p_out.style.opacity = 1;
    }
    if ( p_in.style.display !== 'none' ) {
      return;
    }
       
    /* start transition */
    this._interval1 = setInterval(this._name+'._execute_transparentPanelSwapPhase1()', this._params['speed']);
  }
  
  /*
   * perform a transparent fade in on a panel
   * @param array params
   * * panel_in : string, panel to show
   * * steps : int, fade steps
   * * speed : int, time between 2 steps
   * * action : action to perform when panels are swapped
   * @return void
   * @access public
   */
  this.execute_transparentPanelFadeIn = function(params) {
  
    /* check if params is an array */
    if (typeof(params) != 'object' )
      return;
      
    this._params = params;
    
    /* check params : panels */
    if (!this._params['panel_in'] || !document.getElementById(this._params['panel_in'])) {
      return;
    }
    
    /* check params : optional params */
    if ( !this._params['steps'] || typeof(this._params['steps'])!='number' || this._params['steps'] < 0 )
      this._params['steps'] = 10;
    else
      this._params['steps'] = parseInt(this._params['steps']);
    if ( !this._params['speed'] || typeof(this._params['speed'])!='number' || this._params['speed'] < 0 )
      this._params['speed'] = 50;
    else
      this._params['speed'] = parseInt(this._params['speed']);
    this._params['progress'] = Math.round(100/this._params['steps'])/100;
    
    /* check panels status */
    p_in = document.getElementById(this._params['panel_in']);
    if ( !p_in.style.opacity )
      p_in.style.opacity = 0;
    if ( p_in.style.display == 'block' &&  p_in.style.opacity == 1 )
      return;
    else {
      p_in.style.display = 'block';
      if (p_in.style.opacity == 1)
        p_in.style.opacity = 0;
    }
    /* start fade in */
    this._interval1 = setInterval(this._name+'._execute_transparentPanelFadeInPhase()', this._params['speed']);
  }
  
  /*
   * perform a transparent fade out on a panel
   * @param array params
   * * panel_out : string, panel to hide
   * * steps : int, fade steps
   * * speed : int, time between 2 steps
   * * action : action to perform when panels are swapped
   * @return void
   * @access public
   */
  this.execute_transparentPanelFadeOut = function(params) {
    /* check if params is an array */
    if (typeof(params) != 'object' )
      return;

    this._params = params;
    /* check params : panels */
    if (!this._params['panel_out'] || !document.getElementById(this._params['panel_out'])) {
      return;
    }
    
    /* check params : optional params */
    if ( !this._params['steps'] || typeof(this._params['steps'])!='number' || this._params['steps'] < 0 )
      this._params['steps'] = 10;
    else
      this._params['steps'] = parseInt(this._params['steps']);
    if ( !this._params['speed'] || typeof(this._params['speed'])!='number' || this._params['speed'] < 0 )
      this._params['speed'] = 50;
    else
      this._params['speed'] = parseInt(this._params['speed']);
    this._params['progress'] = Math.round(100/this._params['steps'])/100;
    
    /* check panels status */
    p_out = document.getElementById(this._params['panel_out']);
    
    /* start fade out */
    if ( !p_out.style.opacity )
      p_out.style.opacity = 1;
    if ( p_out.style.display == 'none' || p_out.style.opacity == 0 )
      return;
    else {
      p_out.style.display = 'block';
      if (p_out.style.opacity == 0)
        p_out.style.opacity = 1;
    }
    this._interval1 = setInterval(this._name+'._execute_transparentPanelFadeOutPhase()', this._params['speed']);
  }
  
  
  /* sub methods */
  
  /*
   * phase 1 for transparentPanelSwap
   * @return void
   * @access private
   */
  this._execute_transparentPanelSwapPhase1 = function() {
    /* get panel */
    p_out = document.getElementById(this._params['panel_out']);
        
    /* update panel opacity */
    p_out.style.opacity = Math.round(Math.max(0, (parseFloat(p_out.style.opacity)-this._params['progress']))*100)/100;
      
    if ( p_out.style.opacity == 0 ) {
      p_out.style.display = 'none';
      p_out.style.opacity = 0;
      
      p_in = document.getElementById(this._params['panel_in']);
      p_in.style.opacity = 0;
      p_in.style.display = 'block';
      clearInterval(this._interval1);
      this._interval2 = setInterval(this._name+'._execute_transparentPanelSwapPhase2()', this._params['speed']);
    }
  }
  
  /*
   * phase 2 for transparentPanelSwap
   * @return void
   * @access private
   */
  this._execute_transparentPanelSwapPhase2 = function() {
    /* get panel */
    p_in = document.getElementById(this._params['panel_in']);
    /* update panel opacity */  
    p_in.style.opacity = Math.round(Math.min(1, (parseFloat(p_in.style.opacity)+this._params['progress']))*100)/100;
    
    if ( p_in.style.opacity == 1 ) {
      clearInterval(this._interval2);
      if ( this._params['action'] ) {
        try {
          if ( typeof(this._params['action']) == 'string' )
            eval(this._params['action']);
          else if ( typeof(this._params['action']) == 'function')
            this._params['action']();
        } catch(e) {
          return;
        }
      }
    }
  }
  
  /*
   * phase for transparentPanelFadeIn
   * @return void
   * @access private
   */
  this._execute_transparentPanelFadeInPhase = function() {
    /* get panel */
    p_in = document.getElementById(this._params['panel_in']);
    /*if (!p_in) {
      clearInterval(this._interval1); return;
    }*/
    /* update panel opacity */  
    p_in.style.opacity = Math.min(1, (parseFloat(p_in.style.opacity)+this._params['progress'])); 
    if ( p_in.style.opacity == 1 ) {
      clearInterval(this._interval1);
      if ( this._params['action'] ) {
        try {
          if ( typeof(this._params['action']) == 'string' )
            eval(this._params['action']);
          else if ( typeof(this._params['action']) == 'function')
            this._params['action']();
        } catch(e) {
          return;
        }
      }
    }
  }
  
  /*
   * phase for transparentPanelFadeOut
   * @return void
   * @access private
   */
  this._execute_transparentPanelFadeOutPhase = function() {
    /* get panel */
    p_out = document.getElementById(this._params['panel_out']);
    /*if (!p_out) {
      clearInterval(this._interval1); return;
    }*/
    /* update panel opacity */  
    p_out.style.opacity = parseInt(Math.max(0, (parseFloat(p_out.style.opacity)-this._params['progress']))); 
    if ( p_out.style.opacity == 0 ) {
      p_out.style.display = 'none';
      clearInterval(this._interval1);
      if ( this._params['action'] ) {
        try {
          if ( typeof(this._params['action']) == 'string' )
            eval(this._params['action']);
          else if ( typeof(this._params['action']) == 'function')
            this._params['action']();
        } catch(e) {
          return;
        }
      }
    }
  }
}