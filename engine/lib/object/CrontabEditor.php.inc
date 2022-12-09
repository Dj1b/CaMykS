<?php
/**
 * @brief CronTab Editor library.
 * <br /> Allows websites to add/edit/remove cron jobs from Apache crontab.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.2
 * @date Creation: Oct 2021
 * @date Modification: Feb 2022
 * @copyright 2021 - 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * CrontabEditor class.
 */
final class CrontabEditor {
    /**
     * @var array $jobs
     * @brief List of current crontab jobs.
     */
    private $jobs = array();

    /**
     * @var boolean $hasChanged
     * @brief Stores if loaded crontab has changed.
     */
    private $hasChanged = false;

    /**
     * @var integer $lastError
     * @brief Last error.
     */
    private $lastError = 0;

    /**
     * Class constructor.
     * @return void
     */
    public function __construct() {
        /* Load current jobs */
        $this->load_jobs();
    }

    /**
     * Class destructor.
     * @return void
     */
    public function __destruct() {
        /* Save jobs if changed */
        if ($this->hasChanged)
            $this->save_jobs();
    }

    /**
     * Makes somevariables accessible in read-only
     * @param string $variableName
     * @return mixed
     */
    public function __get($variableName) {
        if (in_array($variableName, array('jobs')))
            return $this->$variableName;
        return null;
    }

    /* I/O methods */

    /**
     * Load crontab jobs.
     * @return boolean success
     */
    public function load_jobs() {
        /* Reset object job list */
        $this->jobs = array();

        /* Read crontab job list */
        if (!exec('crontab -l', $jobs)) {
            $this->set_lastError(1);
            return false;
        }

        /* Create job object from crontab job */
        foreach ($jobs as $details) {
            $job = new CrontabJob($details);
            $this->jobs[$job->identifier] = $job;
        }

        /* Return success */
        return true;
    }

    /**
     * Save crontab jobs.
     * @return boolean success
     */
    public function save_jobs() {
        /* Initialise output */
        $output = '';

        /* No job in list, reset crontab */
        if (count($this->jobs) === 0) {
            if (exec('crontab -r') === '')
                return true;

            $this->set_lastError(11);
            return false;
        }

        /* Add all job to output */
        foreach ($this->jobs as $job)
            $output .= $job->output();

        /* Write temporary file */
        $rand = rand();
        $file = folder_getTemporaryFolder().'/crontab_'.$rand.'.txt';
        if (!file_put_contents($file, $output)) {
            $this->set_lastError(12);
            return false;
        }

        /* Write crontab job list */
        if (!exec('crontab '.$file) == '') {
            $this->set_lastError(11);
            return false;
        }

        /* Return success */
        return true;
    }

    /* Test methods */

    /**
     * Check if job exists.
     * @param string $identifier
     * @return boolean result
     */
    public function check_jobExists($identifier) {
        return isset($this->jobs[$identifier]);
    }

    /**
     * Check if task exists.
     * @param string $task
     * @return boolean result
     */
    public function check_taskExists($task) {
        return (!is_null($this->get_jobIdentifierByTask($task)));
    }

    /* Job related methods */

    /**
     * Return new job.
     * @param mixed $details
     * @param string $identifier
     * @return Object
     */
    public function get_newJob($details=null, $identifier=null) {
        return new CrontabJob($details, $identifier);
    }

    /**
     * Set job, by adding it or replacing existing one.
     * @param mixed $details
     * @param string $identifier
     * @return success
     */
    public function set_job($details, $identifier=null) {

        /* Check details is a job */
        if (is_object($details) and get_class($details) === 'CrontabJob') {
            $job = $details;
            if (!is_null($identifier))
                $job->set_identifier($identifier);
        } else
            $job = new CrontabJob($details, $identifier);

        /* Check job */
        if (!$job->is_valid()) {
            $this->set_lastError($job->get_lastError());
            return false;
        }

        /* Add job to job list */
        $this->jobs[$job->identifier] = $job;
        $this->hasChanged = true;
        return true;
    }

    /**
     * Delete job by identifier.
     * @param string $identifier
     * @return success
     */
    public function delete_job($identifier) {
        /* Check identifier */
        if (!isset($this->jobs[$identifier])) {
            $this->set_lastError(21);
            return false;
        }

        /* Remove job */
        unset($this->jobs[$identifier]);
        $this->hasChanged = true;
        return true;
    }

    /**
     * Delete job by task.
     * @param string $task
     * @return success
     */
    public function delete_jobByTask($task) {
        /* Search for a job with given task */
        foreach ($this->jobs as $identifier => $job) {
            if ($job->is_task($task)) {
                /* Remove job */
                unset($this->jobs[$identifier]);
                $this->hasChanged = true;
                return true;
            }
        }

        /* Job not found, return failure */
        $this->set_lastError(21);
        return false;
    }

    /* Tool methods */

    /**
     * Return job identifier by task value.
     * @param string $task
     * @return string
     */
    public function get_jobIdentifierByTask($task='') {
        /* Search for a job with given task */
        foreach ($this->jobs as $identifier => $job)
            if ($job->is_task($task))
                return $identifier;

        /* Return not found */
        return null;
    }

    /* Error management methods */

    /**
     * Return last error code.
     * @return integer
     */
    public function get_lastErrorCode() {
        return $this->lastError;
    }

    /**
     * Return last error message.
     * @return string
     */
    public function get_lastErrorMessage() {
        global $camyks;

        /* Load dictionnary */
        $camyks->add_generic_translation('crontabeditor');

        switch ($this->lastError) {
            case 0: return $camyks->get_translation('crontabeditor_error_none');

            /* Read errors */
            case 1: return $camyks->get_translation('crontabeditor_error_cantreadcrontab');

            /* Write errors */
            case 11: return $camyks->get_translation('crontabeditor_error_cantwritecrontab');
            case 12: return $camyks->get_translation('crontabeditor_error_cantwritetemporaryfile');

            /* Job errors */
            case 21: return $camyks->get_translation('crontabeditor_error_jobdoesntexist');

        }
        return $camyks->get_translation('crontabeditor_error_unknownerror');
    }

    /**
     * Define last error
     * @param integer $error
     * @return void
     */
    private function set_lastError($error) {
        $this->lastError = $error;
    }
}


/**
 * CrontabJob class.
 */
final class CrontabJob {
    /**
     * @var integer $lastError
     * @brief Last error.
     */
    private $lastError = 0;

    /**
     * @var mixed $details
     * @brief Source details.
     */
    private $details = null;

    /**
     * @var string $minute
     * @brief Minute value for crontab setup.
     */
    private $minute = '*';

    /**
     * @var string $hour
     * @brief Hour value for crontab setup.
     */
    private $hour = '*';

    /**
     * @var string $dayOfMonth
     * @brief Day of month value for crontab setup.
     */
    private $dayOfMonth = '*';

    /**
     * @var string $month
     * @brief Month value for crontab setup.
     */
    private $month = '*';

    /**
     * @var string $dayOfWeek
     * @brief Day of week value for crontab setup.
     */
    private $dayOfWeek = '*';

    /**
     * @var srting $task
     * @brief Task value for crontab setup.
     */
    private $task = '';

    /**
     * @var string $identifier
     * @brief Job identifier.
     */
    private $identifier = null;

    /**
     * Class constructor.
     * @param mixed $details
     * @param string $identifier
     * @return void
     */
    public function __construct($details=null, $identifier=null) {
        /* Set up values */
        if (!is_null($details))
            $this->details = $details;

        if (!is_null($identifier))
            $this->identifier = $identifier;

        /* Read job details */
        $this->load_fromDetails();

        /* Check identifier is set */
        if (is_null($this->identifier)) {
            /* Create identifier */
            $this->identifier = uniqid();
        }
    }

    /**
     * Makes variables accessible in read-only
     * @param string $variableName
     * @return mixed
     */
    public function __get($variableName) {
        if (isset($this->$variableName))
            return $this->$variableName;
        return null;
    }

    /* Values setting methods */

    /**
     * Define details and overwrite all values.
     * @param mixed $details
     * @return boolean success
     */
    public function set_details($details) {
        $this->details = $details;

        $this->load_fromDetails();

        return $this->is_valid();
    }

    /**
     * Define minute value.
     * @param string $minute
     * @return boolean success
     */
    public function set_minute($minute) {
        $this->minute = trim($minute);
        return true;
    }

    /**
     * Define hour value.
     * @param string $hour
     * @return boolean
     */
    public function set_hour($hour) {
        $this->hour = trim($hour);
        return true;
    }

    /**
     * Define day of month value.
     * @param string $dayOfMonth
     * @return boolean success
     */
    public function set_dayOfMonth($dayOfMonth) {
        $this->dayOfMonth = trim($dayOfMonth);
        return true;
    }

    /**
     * Define month value.
     * @param string $month
     * @return boolean success
     */
    public function set_month($month) {
        $this->month = trim($month);
        return true;
    }

    /**
     * Define day of week value.
     * @param string $dayOfWeek
     * @return boolean success
     */
    public function set_dayOfWeek($dayOfWeek) {
        $this->dayOfWeek = trim($dayOfWeek);
        return true;
    }

    /**
     * Define task value.
     * @param string $task
     * @return boolean success
     */
    public function set_task($task) {
        $this->task = trim($task);
        return true;
    }

    /**
     * Define identifier value.
     * @param string $identifier
     * @return boolean success
     */
    public function set_identifier($identifier) {
        $this->identifier = $identifier;
        return true;
    }

    /* I/O methods */

    /**
     * Output job.
     * @return string
     */
    public function output() {
        if ($this->is_valid() === false) {
            if (is_string($this->details))
                return $this->details.PHP_EOL;
            return '';
        }
        return $this->minute.' '.$this->hour.' '.$this->dayOfMonth.' '.$this->month.' '.$this->dayOfWeek.' '.$this->task.' #'.$this->identifier.PHP_EOL;
    }

    /**
     * Return job values as an array.
     * @return string
     */
    public function toArray() {
        return array(
            'minute'        => $this->minute,
            'hour'          => $this->hour,
            'dayOfMonth'    => $this->dayOfMonth,
            'month'         => $this->month,
            'dayOfWeek'     => $this->dayOfWeek,
            'task'          => $this->task,
            'identifier'    => $this->identifier,
        );
    }

    /* Check methods */

    /**
     * Check job is valid.
     * @return boolean success
     */
    public function is_valid() {
        /* Do the checks */


        /* Return default value */
        return true;
    }

    /**
     * Check task is the same as the given one.
     * @param string $task
     * @return boolean result
     */
    public function is_task($task) {
        return $this->task == trim($task);
    }

    /* Private methods */

    /**
     * Load job settings from details.
     * @return boolean success
     */
    private function load_fromDetails() {
        if (is_null($this->details))
            return true;
        if (is_array($this->details))
            return $this->load_fromArrayDetails();
        elseif (is_string($this->details))
           return $this->load_fromStringDetails();
        return false;
    }

    /**
     * Load job settings from details in an array.
     * @return void
     */
    private function load_fromArrayDetails() {
        if (isset($this->details['minute']))
            $this->set_minute($this->details['minute']);
        if (isset($this->details['hour']))
            $this->set_hour($this->details['hour']);
        if (isset($this->details['dayOfMonth']))
            $this->set_dayOfMonth($this->details['dayOfMonth']);
        elseif (isset($this->details['day']))
            $this->set_dayOfMonth($this->details['day']);
        if (isset($this->details['month']))
            $this->set_month($this->details['month']);
        if (isset($this->details['dayOfWeek']))
            $this->set_dayOfWeek($this->details['dayOfWeek']);
        if (isset($this->details['task']))
            $this->set_task($this->details['task']);
        if (isset($this->details['identifier']))
            $this->set_identifier($this->details['identifier']);
        return true;
    }

    /**
     * Load job settings from details in a string.
     * @return void
     */
    private function load_fromStringDetails() {
        $details = explode(' ', $this->details);

        /* Check details length */
        if (count($details) < 5)
            return false;

        /* Load date and time values */
        if (!$this->set_minute(array_shift($details)))
            return false;

        if (!$this->set_hour(array_shift($details)))
            return false;

        if (!$this->set_dayOfMonth(array_shift($details)))
            return false;

        if (!$this->set_month(array_shift($details)))
            return false;

        if (!$this->set_dayOfWeek(array_shift($details)))
            return false;

        /* Rebuild task value / identifier value */
        $details = implode(' ', $details);

        /* Split task and identifier */
        $details = explode('#', $details);

        /* Load task */
        if (!$this->set_task($details[0]))
            return false;

        /* Load identifier if it exists */
        if (isset($details[1]) and !$this->set_identifier($details[1]))
            return false;

        /* Return success */
        return true;
    }
}
?>
