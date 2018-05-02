<?php
/**
 * @brief Benching library
 * <br /> Is automatically loaded by CaMykS, when loading page with head param "_cBench=<output_mode>"
 * <br /> Developers can add their own steps in CaMykS running bench, or create their own bench.
 * @details Engine / Object Library
 * @file engine/lib/object/CBench.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Mar 2014
 * @date Modification: Apr 2018
 * @copyright 2014 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CBench class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class CBench {
    /**
     * @var array $params
     * @brief CBench parameters.
     */
    private $params = array('output'    =>'html');

    /**
     * @var string $status
     * @brief CBench status.
     */
    private $status = 'idle';

    /**
     * @var array $bench
     * @brief CBench saved steps.
     */
    private $bench = array();

    /**
     * @var array $results
     * @brief CBench computed results.
     */
    private $results = array();

    /**
     * object constructor
     * @param array $params
     * @parblock - Available parameters are <br />
     * \e string output - \b none / \b shared / \b session / \b logs / \b html  <br />
     * @endparblock
     * @return void
     */
    public function __construct($params=array()) {
        /* merge params */
        $this->params = array_merge($this->params, $params);
    }

    /* public methods */

    /**
     * Start bench.
     * @param string $title
     * @return mixed
     */
    public function start($title='Start') {
        $this->status = 'running';
        $this->bench[] = array('title'=>$title, 'time'=>microtime(true));
    }

    /**
     * Add a step to bench.
     * @param string $title
     * @return void
     */
    public function add_steps($title='Step') {
        $this->status = 'running';
        if ($title == 'Step') $title .= '-'.count($this->bench);
        $this->bench[] = array('title'=>$title, 'time'=>microtime(true));
    }

    /**
     * Stop bench.
     * @param string $title
     * @return void
     */
    public function stop($title='Stop') {
        $this->status = 'stopped';
        $this->bench[] = array('title'=>$title, 'time'=>microtime(true));
    }

    /**
     * Export results.
     * @return void
     */
    public function export($output='') {
        /* check if bench is stopped */
        if ($this->status != 'stopped')
            $this->stop();

        $method = $output != '' ? $output : $this->params['output'];

        /* compute result */
        $this->_compute_results();

        /* export */
        switch ($method) {
            case 'none': return;
            case 'shared': return $this->_export_toSharedData();
            case 'session': return $this->_export_toSession();
            case 'logs': return $this->_export_toCaMykSLogs();
            case 'html': default : return $this->_export_toHTML();
        }
        return;
    }

    /**
     * Return results.
     * @return array
     */
    public function get_results() {
        return $this->results;
    }

    /* private methods */

    /**
     * Export results to CaMykS shared data.
     * @return void
     */
    private function _export_toSharedData() {
        global $camyks;

        /* save bench to shared data  */
        $camyks->set_sharedData('_cBenchResult', $this->results);
    }

    /**
     * Export results to session.
     * @return void
     */
    private function _export_toSession() {
        global $camyks;

        /* save bench to session  */
        $camyks->set_sessionValue('_cBenchResult', $this->results);
    }

    /**
     * Export results to CaMykS logs.
     * @return void
     */
    private function _export_toCaMykSLogs() {
        global $camyks;

        /* log information */
        $camyks->log_information($this->params['parent'], $msg1, $msg2, $this->params['file'], $this->params['line']);
    }

    /**
     * Export results to HTML.
     * @return void
     */
    private function _export_toHTML() {
        /* display results as HTML */
        echo '<div style="display:none">'."\n";
        foreach ($this->results as $r) {
            echo $r['title'] . ' : '.$r['time']."<br />\n";
        }
        echo '</div>';
    }

    /**
     * Compute results.
     * @return void
     */
    private function _compute_results() {
        for ( $i=0; $i<count($this->bench)-1; $i++) {
            $t = (int)(($this->bench[$i+1]['time']-$this->bench[$i]['time'])*1000);
            $this->results[$i] = array('title'=>$this->bench[$i]['title'], 'time'=>$t.' ms');
        }
        $t = (int)(($this->bench[count($this->bench)-1]['time']-$this->bench[0]['time'])*1000);
        $this->results[$i] = array('title'=>'Total', 'time'=>$t.' ms');
    }
}
?>