<?php
/**
 * @brief ExternalCustomerReviews Input.
 * <br /> Display customer reviews fetched from external platforms (Google, TripAdvisor, Trustpilot, Yelp, Avis Verifies, Facebook).
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Oct 2026
 * @date Modification: Oct 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * ExternalCustomerReviews Input class.
 */
final class ExternalCustomerReviews extends Input {
    /**
     * @var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * @var Object $form
     * @brief Edition form object.
     */
    protected $form;

    /**
     * @var mixed $reviewsData
     * @brief Normalized reviews data for display.
     */
    public $reviewsData = false;

    /**
     * @var boolean $isInitialised
     * @brief Track whether input has been initialised.
     */
    private $isInitialised = false;

    /**
     * @var array $params
     * @brief Input default parameters.
     */
    public $params = array(
        'styleSource'               => 'plugin',
        'source'                    => 'Google',
        'layout'                    => 'grid',
        'showSummary'               => 1,
        'maxReviews'                => 5,
        'minRating'                 => 1,
        'cacheTTL'                  => 86400,
        'language'                  => '',
        'google_apiKey'             => '',
        'google_placeId'            => '',
        'tripadvisor_apiKey'        => '',
        'tripadvisor_locationId'    => '',
        'trustpilot_apiKey'         => '',
        'trustpilot_businessUnitId' => '',
        'yelp_apiKey'               => '',
        'yelp_businessId'           => '',
        'avisverifies_websiteId'    => '',
        'avisverifies_secretKey'    => '',
        'facebook_pageId'           => '',
        'facebook_accessToken'      => '',
    );

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('ExternalCustomerReviews', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* Mark: Override Input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        /* Load configuration */
        $this->load_configuration();

        /* Check and merge parameters */
        $this->check_params($params);

        /* Add plugin stylesheet when styleSource is set to plugin */
        if ($this->params['styleSource'] == 'plugin') {
            $this->add_styleFile('css/styles.css?v=1.0.0');
        }

        /* Load reviews data from cache or external source API */
        $this->load_reviewsData();

        /* Mark as initialised */
        $this->isInitialised = true;

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Display input.
     * @param array $params
     * @return void
     */
    public function display($params=array()) {
        if (!$this->isInitialised or count($params) > 0)
            $this->initialise($params);

        if ($this->reviewsData !== false)
            parent::display();
    }

    /* Mark: Specific public methods */

    /**
     * Execute input and return normalized reviews data.
     * @param array $params
     * @return mixed
     */
    public function execute($params=array()) {
        $this->initialise($params);
        return $this->reviewsData;
    }

    /**
     * Return loaded reviews data.
     * @return mixed
     */
    public function get_reviewsData() {
        return $this->reviewsData;
    }

    /**
     * Clear cached reviews files.
     * @return boolean
     */
    public function clear_cache() {
        $cacheFolder = $this->plugin_var_path.'/cache';
        if (!is_dir($cacheFolder))
            return true;
        return folder_delete($cacheFolder, true);
    }

    /* Mark: Template helper methods */

    /**
     * Build HTML stars representation for given rating.
     * @param float $rating
     * @param integer $maxRating
     * @return string
     */
    public function get_starsHTML($rating, $maxRating=5) {
        $rating = max(0.0, min((float)$maxRating, (float)$rating));
        $maxRating = max(1, (int)$maxRating);

        $html = '<span class="ecr-stars" aria-label="'.htmlspecialchars(number_format($rating, 1).' / '.$maxRating).'">';
        for ($i = 1; $i <= $maxRating; $i++) {
            if ($rating >= $i) {
                $stateClass = 'ecr-star-full';
            } elseif ($rating >= ($i - 0.5)) {
                $stateClass = 'ecr-star-half';
            } else {
                $stateClass = 'ecr-star-empty';
            }
            $html .= '<span class="ecr-star '.$stateClass.'" aria-hidden="true">&#9733;</span>';
        }
        $html .= '</span>';
        return $html;
    }

    /**
     * Return author initials from author display name.
     * @param string $name
     * @return string
     */
    public function get_authorInitials($name) {
        $name = trim(strip_tags((string)$name));
        if ($name === '')
            return '?';
        $parts = preg_split('/\s+/', $name);
        $initials = '';
        foreach ($parts as $part) {
            if ($part !== '') {
                $initials .= mb_strtoupper(mb_substr($part, 0, 1, 'UTF-8'), 'UTF-8');
                if (mb_strlen($initials, 'UTF-8') >= 2)
                    break;
            }
        }
        return $initials !== '' ? $initials : '?';
    }

    /**
     * Return formatted date string for a review item.
     * @param array $review
     * @return string
     */
    public function get_formattedDate($review) {
        if (!empty($review['dateText']))
            return $review['dateText'];
        if (!empty($review['date']) and (int)$review['date'] > 0)
            return date_displayShortDate((int)$review['date']);
        return '';
    }

    /* Mark: Data & Cache internal methods */

    /**
     * Check parameters from default values, saved configuration and caller overrides.
     * @param array $params
     * @return void
     */
    private function check_params($params=array()) {
        global $camyks;

        /* Merge default params with saved configuration and caller overrides */
        $this->params = array_merge($this->params, $this->config->vars, $params);

        /* Normalize styleSource */
        if (!in_array($this->params['styleSource'], array('plugin', 'theme')))
            $this->params['styleSource'] = 'plugin';

        /* Normalize layout */
        if (!in_array($this->params['layout'], array('grid', 'list', 'badge')))
            $this->params['layout'] = 'grid';

        /* Normalize numeric parameters */
        $this->params['showSummary'] = (int)$this->params['showSummary'] ? 1 : 0;
        $this->params['maxReviews'] = max(0, (int)$this->params['maxReviews']);
        $this->params['minRating'] = max(1, min(5, (int)$this->params['minRating']));
        $this->params['cacheTTL'] = max(0, (int)$this->params['cacheTTL']);

        /* Set default language from CaMykS current language */
        if (empty($this->params['language'])) {
            $this->params['language'] = !empty($camyks->current_language) ? $camyks->current_language : 'fr';
        }
    }

    /**
     * Load reviews from cache or fetch from source connector and apply filters.
     * @return void
     */
    private function load_reviewsData() {
        $source = $this->params['source'];
        $sources = $this->config->get_sourceList();

        if (!isset($sources[$source])) {
            $this->reviewsData = false;
            return;
        }

        $cacheFile = $this->get_cacheFilePath($source);
        $rawData = false;

        /* Check valid cache first */
        if ($this->params['cacheTTL'] > 0 and file_exists($cacheFile)) {
            $age = time() - filemtime($cacheFile);
            if ($age < $this->params['cacheTTL']) {
                $rawData = $this->read_cacheFile($cacheFile);
            }
        }

        /* Query source API when cache is missing or expired */
        if ($rawData === false) {
            $this->load_library('ExternalCustomerReviewsSource');
            $library = 'ExternalCustomerReviews_'.$source;
            $this->load_library('Sources/'.$library);

            if (class_exists($library)) {
                $connector = new $library();
                $rawData = $connector->execute($this->params);

                if (is_array($rawData)) {
                    /* Write fresh cache */
                    if ($this->params['cacheTTL'] > 0) {
                        $this->write_cacheFile($cacheFile, $rawData);
                    }
                } elseif (file_exists($cacheFile)) {
                    /* Graceful fallback to stale cache if external API is temporarily unreachable */
                    $rawData = $this->read_cacheFile($cacheFile);
                }
            }
        }

        if (!is_array($rawData)) {
            $this->reviewsData = false;
            return;
        }

        /* Filter and limit reviews according to parameters */
        $filteredReviews = array();
        if (isset($rawData['reviews']) and is_array($rawData['reviews'])) {
            foreach ($rawData['reviews'] as $review) {
                $reviewRating = isset($review['rating']) ? (float)$review['rating'] : 0.0;
                if ($reviewRating >= $this->params['minRating']) {
                    $filteredReviews[] = $review;
                }
            }
        }

        if ($this->params['maxReviews'] > 0 and count($filteredReviews) > $this->params['maxReviews']) {
            $filteredReviews = array_slice($filteredReviews, 0, $this->params['maxReviews']);
        }

        $rawData['reviews'] = $filteredReviews;
        $this->reviewsData = $rawData;
    }

    /**
     * Build cache file path for given source and active credentials.
     * @param string $source
     * @return string
     */
    private function get_cacheFilePath($source) {
        $sources = $this->config->get_sourceList();
        $fields = isset($sources[$source]['Fields']) ? $sources[$source]['Fields'] : array();
        $keyParts = array($source, $this->params['language']);
        foreach ($fields as $field) {
            $keyParts[] = isset($this->params[$field]) ? $this->params[$field] : '';
        }
        $hash = md5(implode('|', $keyParts));
        return $this->plugin_var_path.'/cache/reviews_'.strtolower($source).'_'.$hash.'.json';
    }

    /**
     * Read and decode JSON cache file.
     * @param string $cacheFile
     * @return mixed
     */
    private function read_cacheFile($cacheFile) {
        $content = file_getContent($cacheFile);
        if ($content === '')
            return false;
        $data = json_decode($content, true);
        if (json_last_error() !== JSON_ERROR_NONE or !is_array($data))
            return false;
        return $data;
    }

    /**
     * Write normalized reviews data to JSON cache file.
     * @param string $cacheFile
     * @param array $data
     * @return boolean
     */
    private function write_cacheFile($cacheFile, $data) {
        $cacheFolder = dirname($cacheFile);
        if (!file_exists($cacheFolder))
            folder_completePath($cacheFolder);
        return file_write($cacheFile, json_encode($data));
    }

    /* Mark: Configuration related methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        if (!is_null($this->config))
            return;
        $this->load_library('ExternalCustomerReviewsConfig');
        $this->config = new ExternalCustomerReviewsConfig('config', $this);
        $this->config->get();
    }

    /**
     * Return configuration value.
     * @param string $name
     * @return mixed
     */
    protected function get_configValue($name='') {
        $this->load_configuration();
        return $this->config->get_value($name);
    }

    /* Mark: Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        $this->load_configuration();
    }

    /**
     * Display object in Admin_Site / view configuration mode.
     * @return void
     */
    public function display_configDisplay() {
        $this->load_file('html/configuration/view.html.inc');
    }

    /**
     * Initialise object in Admin_Site / edit configuration mode.
     * @param Object $form
     * @return void
     */
    public function initialise_configEdition($form) {
        $this->load_configuration();

        /* Update form */
        $this->form = &$form;
        $this->form->set_object($this->config);
    }

    /**
     * Display object in Admin_Site / edit configuration mode.
     * @return void
     */
    public function display_configEdition() {
        $this->load_file('html/configuration/edit.html.inc');
    }

    /**
     * Execute object in Admin_Site / save configuration mode.
     * @return boolean
     */
    public function save_configuration() {
        $this->load_configuration();
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
