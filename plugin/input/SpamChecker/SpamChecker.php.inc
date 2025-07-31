<?php
/**
 * @brief SpamChecker input.
 * <br /> Contact form or comment spam checker.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2021
 * @date Modification: Jul 2025
 * @copyright 2021 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SpamChecker Input class.
 */
final class SpamChecker extends Input {
    /**
     * var Object $config
     * @brief Input configuration.
     */
    protected $config;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('SpamChecker', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Register plugin as Admin_Site extension */
        $this->register_asExtension('Admin_Site');
    }

    /* Mark: Execute methods */

    /**
     * Execute input and return ip location.
     * @param array $params
     * @return mixed
     */
    public function execute($params=array()) {
        /* Load parameters */
        $defaultParams = array(
            'output' => 'result',
            'object' =>'',
            'objectId' => '',
            'data' => array(
                'fullName'  => '',
                'firstName' => '',
                'lastName'  => '',
                'email'     => '',
                'company'   => '',
                'phone'     => '',
                'content'   => '', // array | string
                'ipAddress' => '',
                'hostname'  => '',
            ),
        );
        $params = array_recursiveMerge($defaultParams, $params);

        /* Load configuration */
        $this->load_configuration();

        /* Check params */
        $params = $this->check_params($params);

        /* Return result of content is spam check */
        return $this->check_contentIsSpam($params);
    }

    /* Mark: Spam related methods */

    /**
     * Check content is spam.
     * @param array $params
     * @return mixed
     */
    private function check_contentIsSpam($params) {
        global $camyks;

        /* Initialise score result */
        $scores = array('score' => 0, 'result' => 'isNotSpam', 'data' => array());

        /* Load names if required */
        if ($this->get_configValue('checkSimilarNamesEnabled') or $this->get_configValue('checkRandomNamesEnabled')) {
            $firstName = '';
            $lastName = '';
            if ($params['data']['fullName'] !== '') {
                $name = explode(' ', $params['data']['fullName']);
                $firstName = trim(array_shift($name));
                if (count($name) > 0) {
                    $lastName = implode(' ', $name);
                }
            } else {
                $firstName = trim($params['data']['firstName']);
                $lastName = trim($params['data']['lastName']);
            }
        }


        /* Check similar name rule */
        if ($this->get_configValue('checkSimilarNamesEnabled')) {
            if ($firstName !== '' and $lastName !== '') {
                if ($firstName == $lastName and preg_match('/^'.string_escape4Regex($firstName).'[A-Za-z]{2}$/', $lastName) or preg_match('/^'.string_escape4Regex($lastName).'[A-Za-z]{2}$/', $firstName)) {
                    $scores['score'] += $this->get_configValue('checkSimilarNamesScore');
                    $scores['data'][] = 'Similar names: '.$this->get_configValue('checkSimilarNamesScore');
                }
            }
        }

        /* Check random letters name rule */
        if ($this->get_configValue('checkRandomNamesEnabled')) {
            $count = 0;

            /* Count caps blocks */
            if ($firstName != '' and preg_match_all('/([A-Z]+)/', $firstName, $matches)) {
                $count += max(0, count($matches[0]) - 2);
            }
            if ($lastName != '' and preg_match_all('/(^|[^ ][A-Z]+)/', $lastName, $matches)) {
                $count += max(0, count($matches[0]) - 2);
            }

            /* Count 4 successive consonants blocks */
            if ($firstName != '' and preg_match_all('/([^\dAEYUIOaeyuio]{4,})/', $firstName, $matches)) {
                $count += count($matches[0]);
            }
            if ($lastName != '' and preg_match_all('/([^\dAEYUIOaeyuio]{4,})/', $lastName, $matches)) {
                $count += count($matches[0]);
            }

            /* Check result */
            if ($count >= 2) {
                $scores['score'] += $this->get_configValue('checkRandomNamesScore');
                $scores['data'][] = 'Random names: '.$this->get_configValue('checkRandomNamesEnabled');
            }
        }

        /* Check HTML content rule */
        if ($this->get_configValue('checkHTMLEnabled')) {
            $cnt = 0;
            if (is_array($params['data']['content'])) {
                foreach ($params['data']['content'] as $content) {
                    if ($content != strip_tags($content))
                        $cnt++;
                }
            } elseif (is_string($params['data']['content'])) {
                if ($params['data']['content'] != strip_tags($params['data']['content']))
                    $cnt++;
            }

            if ($cnt > 0) {
                $scores['score'] += $this->get_configValue('checkHTMLScore');
                $scores['data'][] = 'Contains HTML (x'.$cnt.'): '.$cnt.'x'.$this->get_configValue('checkHTMLScore');
            }
        }

        /* Check javascript content rule */
        if ($this->get_configValue('checkJavascriptEnabled')) {
            $cnt = 0;
            if (is_array($params['data']['content'])) {
                foreach ($params['data']['content'] as $content) {
                    if (preg_match('/<script/', $content))
                        $cnt++;
                }
            } elseif (is_string($params['data']['content'])) {
                if (preg_match('/<script/', $params['data']['content']))
                    $cnt++;
            }

            if ($cnt > 0) {
                $scores['score'] += $this->get_configValue('checkJavascriptScore');
                $scores['data'][] = 'Contains Javascript (x'.$cnt.'): '.$cnt.'x'.$this->get_configValue('checkJavascriptScore');
            }
        }

        /* Check email rules */
        if ($this->get_configValue('checkEmailEnabled')) {
            foreach ($this->get_configValue('checkEmailRules') as $rule) {
                /* Check rule is a regexp */
                $c = substr($rule['rule'], 0, 1);
                if ($c == substr($rule['rule'], -1) and !ctype_alnum($c) and !ctype_space($c))
                    $pattern = $rule['rule'];

                /* Transform rule as a regexp with wildcard char support */
                else
                    $pattern = '#'.string_escape4Regex($rule['rule']).'#';

                /* Perform check */
                if (preg_match($pattern, $params['data']['email'])) {
                    $scores['score'] += $rule['score'];
                    $scores['data'][] = 'Email matches rule "'.$rule['rule'].'": '.$rule['score'];
                }
            }
        }

        /* Check company rules */
        if ($this->get_configValue('checkCompanyEnabled') and count($this->get_configValue('checkCompanyRules')) > 0) {
            foreach ($this->get_configValue('checkCompanyRules') as $rule) {
                /* Check rule is a regexp */
                $c = substr($rule['rule'], 0, 1);
                if ($c == substr($rule['rule'], -1) and !ctype_alnum($c) and !ctype_space($c))
                    $pattern = $rule['rule'];

                /* Transform rule as a regexp with wildcard char support */
                else
                    $pattern = '#'.preg_replace('/\*/', '(.*)', string_escape4Regex($rule['rule'])).'#';

                /* Perform check */
                if (preg_match($pattern, $params['data']['company'])) {
                    $scores['score'] += $rule['score'];
                    $scores['data'][] = 'Company matches rule "'.$rule['rule'].'": '.$rule['score'];
                }
            }
        }

        /* Check links rules */
        if ($this->get_configValue('checkLinkEnabled')) {

            $hasLink = false;

            /* Check for single link content */
            if ($this->get_configValue('checkLinkWithoutContentScore') > 0) {

                $pattern = '#^(https?|www\.)([\w\.]+)$#';
                if (is_array($params['data']['content'])) {
                    $cnt = 0;
                    foreach ($params['data']['content'] as $content)
                        if (preg_match($pattern, $content)) {
                            $hasLink = true;
                            $scores['score'] += $this->get_configValue('checkLinkWithoutContentScore');
                            $scores['data'][] = 'Single link content: '.$this->get_configValue('checkLinkWithoutContentScore');
                        }
                } elseif (is_string($params['data']['content'])) {
                    if (preg_match($pattern, $params['data']['content'])) {
                        $hasLink = true;
                        $scores['score'] += $this->get_configValue('checkLinkWithoutContentScore');
                        $scores['data'][] = 'Single link content: '.$this->get_configValue('checkLinkWithoutContentScore');
                    }
                }
            }

            /* Check for links in content */
            if (!$hasLink and $this->get_configValue('checkLinkScore') > 0) {

                $pattern = '#(https?|www\.)([\w\.]+)#';
                $cnt = 0;

                if (is_array($params['data']['content'])) {
                    foreach ($params['data']['content'] as $content)
                        $cnt += preg_match($pattern, $content);
                } elseif (is_string($params['data']['content'])) {
                    $cnt += preg_match($pattern, $params['data']['content']);
                }

                if ($cnt > 0) {
                    $scores['score'] += $cnt*$this->get_configValue('checkLinkScore');
                    $scores['data'][] = 'Contains links: '.$cnt.'x'.$this->get_configValue('checkLinkScore');
                }
            }
        }

        /* Check words rules */
        if ($this->get_configValue('checkWordEnabled') and count($this->get_configValue('checkWordRules')) > 0) {
            foreach ($this->get_configValue('checkWordRules') as $rule) {
                $pattern = '#'.preg_replace('/\*/', '(^W*)', string_escape4Regex($rule['rule'])).'#';

                $cnt = 0;
                if (is_array($params['data']['content'])) {
                    foreach ($params['data']['content'] as $content)
                        $cnt += preg_match_all($pattern, $content);
                } elseif (is_string($params['data']['content'])) {
                    $cnt += preg_match_all($pattern, $params['data']['content']);
                }

                if ($cnt > 0) {
                    $scores['score'] += $cnt*$rule['score'];
                    $scores['data'][] = 'Contains excluded word ('.$rule['rule'].'x'.$cnt.'): '.$cnt.'x'.$rule['score'];
                }
            }
        }

        /* Check language script rules */
        if ($this->get_configValue('checkLanguageScriptEnabled') and count($this->get_configValue('checkLanguageScriptRules')) > 0) {
            foreach ($this->get_configValue('checkLanguageScriptRules') as $rule) {
                $pattern = '#[\p{'.$rule['rule'].'}]{2,}#u';

                $cnt = 0;
                if (is_array($params['data']['content'])) {
                    foreach ($params['data']['content'] as $content)
                        $cnt += preg_match($pattern, $content);
                } elseif (is_string($params['data']['content'])) {
                    $cnt += preg_match($pattern, $params['data']['content']);
                }

                if ($cnt > 0) {
                    $scores['score'] += $rule['score'];
                    $scores['data'][] = 'Contains language script ('.$rule['rule'].'): '.$rule['score'];
                }
            }
        }

        /* Check country rules */
        if ($this->get_configValue('checkCountryEnabled') and count($this->get_configValue('checkCountryRules')) > 0) {
            $IPGeolocator = $camyks->get_input('IPGeolocator');
            if ($IPGeolocator !== false) {
                $country = $IPGeolocator->execute(array('ipAddress'=>$params['data']['ipAddress']));
                if ($country !== false) {
                    countries_loadLocales();
                    foreach ($this->get_configValue('checkCountryRules') as $rule) {
                        if ($country == $rule['rule']) {
                            $scores['score'] += $rule['score'];
                            $scores['data'][] = 'Origin country ('.countries_getTranslation($rule['rule']).'): '.$rule['score'];
                            break;
                        }
                    }
                }
            }
        }

        /* Check hostname rules */
        if ($this->get_configValue('checkHostnameEnabled') and count($this->get_configValue('checkHostnameRules')) > 0) {
            foreach ($this->get_configValue('checkHostnameRules') as $rule) {
                /* Check rule is a regexp */
                $c = substr($rule['rule'], 0, 1);
                if ($c == substr($rule['rule'], -1) and !ctype_alnum($c) and !ctype_space($c))
                    $pattern = $rule['rule'];

                /* Transform rule as a regexp with wildcard char support */
                else
                    $pattern = '#'.string_escape4Regex($rule['rule']).'#';

                /* Perform check */
                if (preg_match($pattern, $params['data']['hostname'])) {
                    $scores['score'] += $rule['score'];
                    $scores['data'][] = 'Hostname matches rule "'.$rule['rule'].'": '.$rule['score'];
                }
            }
        }

        /* Check result */
        if ($scores['score'] >= $this->get_configValue('isSpamScore'))
            $scores['result'] = 'isSpam';
        elseif ($scores['score'] >= $this->get_configValue('isProbablySpamScore'))
            $scores['result'] = 'isProbablySpam';

        /* Check for result logging */
        if ($this->get_configValue('enableLogs') > 0) {
            $camyks->log('SpamChecker', 'Spam check on object "'.$params['object'].' #'.$params['objectId'].'"', 'Result: '.$scores['result'].' - Score:'.$scores['score']);
            if ($this->get_configValue('enableLogs') == 2) {
                foreach ($scores['data'] as $line)
                    $camyks->log('SpamChecker', 'Spam check on object "'.$params['object'].' #'.$params['objectId'].'"', '|- '.$line);
            }
        }

        /* Return result */
        if ($params['output'] == 'result')
            return $scores['result'];
    }

    /* Parameters related methods */

    /**
     * Check parameters.
     * @param array $params
     * @return array
     */
    private function check_params($params) {
        global $camyks;

        /* Check IP address */
        if (empty($params['data']['ipAddress']) or !string_isValidIPv4($params['data']['ipAddress']))
            $params['data']['ipAddress'] = client_getIp();

        /* Add hostname from IP address */
        if ($params['data']['hostname'] === '' and ($v = @gethostbyaddr($params['data']['ipAddress'])) !== $params['data']['ipAddress']) {
            $params['data']['hostname'] = $v;
            $camyks->log('Dev', 'Hostname check', 'Hostname for '.$params['data']['ipAddress'].' is '.$v);
        }

        /* Return updated params */
        return $params;
    }

    /* CMark: onfiguration related methods */

    /**
     * Load configuration.
     * @return void
     */
    private function load_configuration() {
        $this->load_library('SpamCheckerConfig');
        $this->config = new SpamCheckerConfig('config', $this);
        $this->config->get();
    }

    /**
     * Return configuration value.
     * @param string $name
     * @return mixed
     */
    protected function get_configValue($name='') {
        return $this->config->get_value($name);
    }

    /* Mark: Admin_Site extension configuration methods */

    /**
     * Initialise object in Admin_Site / view configuration mode.
     * @return void
     */
    public function initialise_configDisplay() {
        /* load plugin configuration */
        $this->load_configuration();

        /* Load data */
        if ($this->get_configValue('checkCountryEnabled') == 1 and count($this->get_configValue('checkCountryRules')) > 0)
            countries_loadLocales();

        if ($this->get_configValue('checkLanguageScriptEnabled') == 1 and count($this->get_configValue('checkLanguageScriptRules')) > 0)
            language_loadLocales();
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
        /* Load plugin configuration */
        $this->load_configuration();

        /* Update form */
        $this->form = &$form;
        $this->form->set_object($this->config);

        /* Load data */
        $this->scriptList = language_getScriptTitleList();

        /* Adds scripts */
        $this->add_JSFile('SpamCheckerConfig.js');
        $this->add_JSLoadScript('SpamCheckerConfig.set_param("form", "'.$this->form->name.'");');
        $this->add_JSLoadScript('SpamCheckerConfig.initialise();');
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
     * @return void
     */
    public function save_configuration() {
        $this->load_configuration();
        $this->config->get_fromHeader();
        return $this->config->save();
    }
}
?>
