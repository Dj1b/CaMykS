<?php
/*
 * CaMykS Engine
 * Developed by		: camyks.net
 * Author		    : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0b
 * Object Version	: 1.0
 * Object Type      : Engine / Object
 * Creation Date    : Mar 2014
 * Last Modif Date  : Oct 2017
 *
 * Request Answer generic object
 */

final class CBench {
  /* params */
  private $params;
  private $status;
  private $bench;

  /*
   * object constructor
   * @param array $params
   * @return void
   * @access public
   */
  public function __construct($params=array()) {
    /* build default param list */
    $defaultParams = array(
        'output'=>'html',
    );
    
    /* build object param list */
    $this->params = array_merge($defaultParams, $params);
    $this->status = 'idle';
    
    /* initialise bench */
    $this->bench = array();
    $this->results = array();
  }

  /* public methods */
  
  /*
   * return param
   * @param string $title
   * @return mixed
   * @access public
   */
  public function start($title='Start') {
    $this->status = 'running';
    $this->bench[] = array('title'=>$title, 'time'=>microtime(true));
  }
  
  /*
   * update params 
   * @param array $params
   * @return void
   * @access public
   */
  public function add_steps($title='Step') {
    $this->status = 'running';
    if ($title == 'step') $title .= '-'.count($this->bench);
  	$this->bench[] = array('title'=>$title, 'time'=>microtime(true));
  }
  
  /*
   * update param
   * @param string $title
   * @return void
   * @access public
   */
  public function stop($title='Stop') {
    $this->status = 'stopped';
  	$this->bench[] = array('title'=>$title, 'time'=>microtime(true));
  }
  
  /*
   * export results
   * @return void
   * @access public
   */
  public function export($method='') {
    /* check if bench is stopped */
    if ($this->status != 'stopped')
        $this->stop();
    
    /* compute result */
    $this->_compute_results();
  
    /* export */
    switch ($method) {
      case 'logs': return $this->_export_toCaMykSLogs();
      case 'html': default : return $this->_export_toHTML();
    }
    return;
  }
  
  /* private methods */
  
  /*
   * export results to CaMykS logs
   * @return void
   * @access private
   */
  private function _export_toCaMykSLogs() {
  	global $camyks;
  	  	
  	/* send error */
  	$camyks->log_information($this->params['parent'], $msg1, $msg2, $this->params['file'], $this->params['line']);
  }
  
  /*
   * export results to HTML
   * @return void
   * @access private
   */
  private function _export_toHTML($params=array()) {    
    /* display results as HTML */
  	echo '<div style="display:none">'."\n";
  	foreach ($this->results as $r) {
  	  echo $r['title'] . ' : '.$r['time']."<br />\n";
  	}
  	echo '</div>';
  }
  
  
  /*
   * compute results 
   * @return void
   * @access private
   */
  private function _compute_results() {
    for ( $i=0; $i<count($this->bench)-1; $i++) {
      $t = round($this->bench[$i+1]['time']-$this->bench[$i]['time'], 4);
      $this->results[$i] = array('title'=>$this->bench[$i]['title'], 'time'=>$t.' s');
    }
    $t = round($this->bench[count($this->bench)-1]['time']-$this->bench[0]['time'], 4);
    $this->results[$i] = array('title'=>'Total', 'time'=>$t.' s');
  }
}
?>