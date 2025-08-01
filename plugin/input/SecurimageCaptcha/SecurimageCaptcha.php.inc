<?php
/**
 * @brief SecurimageCaptcha Input
 * <br /> Display captcha from Securimage.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jul 2009
 * @date Modification: Jul 2025
 * @copyright 2009 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note Includes Securimage version 1.0.3.1 (http://www.phpcaptcha.org)
 */

/**
 * SecurimageCaptcha Input class.
 */
final class SecurimageCaptcha extends Input {

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('SecurimageCaptcha', $path_type);

        /* Override Plugin information */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override input methods */

    /**
     * Install plugin.
     * @return boolean success
     */
    public function install() {
        return (extension_loaded('gd') && parent::install());
    }

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* update params */
        $params = array_merge(array('ttf_file'=>$this->get_filePath('securimage/elephant.ttf')), $params);
        /* save params */
        $camyks->set_sessionValue('sic_params', $params);

        /* Input generic initialization */
        parent::initialise();
    }

    /**
     * Display input.
     * @param string $layout
     * @return void
     */
    public function display($layout='captcha') {
        $this->set_selectedLayout('input_'.$layout.'.html.inc');
        parent::display();
    }

    /**
     * Execute input in request mode.
     * @return void
     */
    public function execute_request() {
        global $camyks;

        /* load Securimage */
        $this->load_file('securimage/securimage.php');
        $img = new Securimage();

        /* check Securimage parameters */
        if (($params = $camyks->get_sessionValue('sic_params', null)) != null) {
            if (isset($params['image_width']))
                $img->image_width = $params['image_width'];
            if (isset($params['image_height']))
                $img->image_height = $params['image_height'];
            if (isset($params['image_type']))
                $img->image_type = $params['image_type'];
            if (isset($params['code_length']))
                $img->code_length = $params['code_length'];
            if (isset($params['charset']))
                $img->charset = $params['charset'];
            if (isset($params['word_list'])) {
                $img->wordlist_file = $params['word_list'];
                $img->use_wordlist = true;
            } else {
                $img->use_wordlist = false;
            }
            if (isset($params['image_bg_color']))
                $img->image_bg_color = $params['image_bg_color'];
            if (isset($params['image_text_colors']))
                $img->multi_text_color = $params['image_text_colors'];
            if (isset($params['ttf_file']))
                $img->ttf_file = $params['ttf_file'];
        }

        /* clean parameters */
        $camyks->set_sessionValue('sic_params', null);

        /* display image */
        $img->show();
    }

    /* Mark: Specific tool methods */

    /**
     * Check captcha.
     * @return boolean result
     */
    public function check_captcha($code) {
        $this->load_file('securimage/securimage.php');
        $img = new Securimage();
        return $img->check($code);
    }
}
?>
