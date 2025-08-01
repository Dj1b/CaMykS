<?php
/**
 * @brief BreadCrumbs Input
 * <br /> Display current page path on website.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jul 2008
 * @date Modification: Jul 2025
 * @copyright 2008 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * BreadCrumbs Input class.
 */
final class BreadCrumbs extends Input {
    /**
     * var array $path
     * @brief The page path.
     */
    protected $path = array();

    /**
     * var array $params
     * @brief Input parameters.
     */
    public $params = array(
        'separator'         => ' &gt; ',
        'container_class'   => '',
        'link_class'        => 'eLink1',
        'text_class'        => 'eContent1',
        'path_termination'  => array(),
   );

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('BreadCrumbs', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Default';

        /* Define author information */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* check if Admin_ContentPage exists */
        if (!isset($camyks->modules['Admin_ContentPage']))
            return;

        /* merge params */
        $this->params = array_merge($this->params, $params);

        /* get pages */
        $this->pages = $camyks->modules['Admin_ContentPage']->get_sitePages();

        /* get current page */
        $currentPage = $camyks->contentPage->id;

        /* get path */
        $this->path = array();
        while (isset($this->pages[$currentPage])) {
            $page = &$this->pages[$currentPage];
            if ($page->active == 1) {
                $p = array('title' => $page->get_shortTitleDisplay('html'), 'url'=>$page->get_siteLink());
            } elseif ($page->id !=0 and ($page->shorttitle != '' or $page->title != '')) {
                $p = array('title' => $page->get_shortTitleDisplay('html'), 'url'=>false);
            } else {
                break;
            }
            array_unshift($this->path, $p);
            $currentPage = $page->parent_id;
        }

        /* check path termination */
        if (is_array($this->params['path_termination']) and count($this->params['path_termination']) > 0)
            $this->path = array_merge($this->path, $this->params['path_termination']);

        /* Input generic initialization */
        parent::initialise();
    }
}
?>
