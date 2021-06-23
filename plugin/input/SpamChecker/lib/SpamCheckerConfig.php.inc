<?php
/**
 * @brief SpamChecker Input configuration object
 * @details Plugin / Input Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Jun 2021
 * @date Modification: Jun 2021
 * @copyright 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * SpamCheckerConfig PluginConfig class.
 */
final class SpamCheckerConfig extends PluginConfig {
    /**
     * @var array $listRules
     * @brief List of rules that use a list of objects.
     */
    private $listRules = array('Email', 'Company', 'Word', 'LanguageScript', 'Country', 'Hostname');

    /**
     * Class constructor.
     * @param string $name
     * @param Module $parent
     * @return void
     */
    public function __construct($name, &$parent) {
        parent::__construct($name, $parent);

        /* Define plugin params */
        $this->add_newItem('enableLogs', 'integer', 1);
        // $this->add_newItem('autoBanIpAddress', 'boolean', 0);

        /* Spam score params */
        $this->add_newItem('isProbablySpamScore', 'integer', 60);
        $this->add_newItem('isSpamScore', 'integer', 100);

        /* Spam content rules */
        $this->add_newItem('checkSimilarNamesEnabled', 'boolean', false);
        $this->add_newItem('checkSimilarNamesScore', 'integer', 100);

        $this->add_newItem('checkHTMLEnabled', 'boolean', false);
        $this->add_newItem('checkHTMLScore', 'integer', 40);

        $this->add_newItem('checkJavascriptEnabled', 'boolean', false);
        $this->add_newItem('checkJavascriptScore', 'integer', 60);

        $this->add_newItem('checkEmailEnabled', 'boolean', 0);
        $this->add_newItem('checkEmailRules', 'array', array()); /*  array(rule => string, score => int) */

        $this->add_newItem('checkCompanyEnabled', 'boolean', 0);
        $this->add_newItem('checkCompanyRules', 'array', array()); /* array(rule => string, score => int) */

        $this->add_newItem('checkLinkEnabled', 'boolean', 0);
        $this->add_newItem('checkLinkScore', 'integer', 10);
        $this->add_newItem('checkLinkWithoutContentScore', 'integer', 50);

        $this->add_newItem('checkWordEnabled', 'boolean', 0);
        $this->add_newItem('checkWordRules', 'array', array()); /* array(rule => string, score => int) */

        $this->add_newItem('checkLanguageScriptEnabled', 'boolean', 0);
        $this->add_newItem('checkLanguageScriptRules', 'array', array()); /* array(rule => string, score => int) */

        /* Span origin rules */
        $this->add_newItem('checkCountryEnabled', 'boolean', 0);
        $this->add_newItem('checkCountryRules', 'array', array()); /* array(rule => string, score => int) */

        $this->add_newItem('checkHostnameEnabled', 'boolean', 0);
        $this->add_newItem('checkHostnameRules', 'array', array()); /* array(rule => string, score => int) */

        /* generic initialisation */
        parent::init_config();
    }

    /* Override PluginConfig methods */

    /**
     * Load object items values from header.
     * @return void
     */
    public function get_fromHeader() {
        /* Load generic objects */
        parent::get_fromHeader();

        /* Load specific objects */
        foreach ($this->listRules as $rule) {
            $values = $_REQUEST['check'.$rule.'RulesValues'];
            $scores = $_REQUEST['check'.$rule.'RulesScores'];

            $data = array();
            for ($i=0; $i < count($values); $i++) {
                if ($values[$i] !== '')
                    $data[] = array('rule'=>$values[$i], 'score'=>isset($scores[$i]) ? (int)$scores[$i] : 0);
            }

            $this->vars['check'.$rule.'Rules'] = $data;
        }
    }

    /* Data methods */

    /**
     * Return log enabling values.
     * @return array
     */
    public function get_enableLogsList() {
        global $camyks;

        return array(
            0 => $camyks->get_translation('no'),
            1 => $this->get_translation('enablelogs_withoutdetails'),
            2 => $this->get_translation('enablelogs_withdetails'),
        );
    }

    /**
     * Return log enabling title.
     * @return string
     */
    public function get_enableLogsTitle() {
        $list = $this->get_enableLogsList();
        if (isset($list[$this->vars['enableLogs']]))
            return $list[$this->vars['enableLogs']];
        return '';
    }
}
?>
