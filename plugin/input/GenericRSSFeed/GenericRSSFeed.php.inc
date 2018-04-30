<?php
/**
 * @brief GenericRSSFeed Input
 * <br /> Send formatted articles as XML RSS feed.
 * @details Plugin / Input Engine
 * @file plugin/input/GenericRSSFeed/GenericRSSFeed.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Dec 2007
 * @date Modification: Apr 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * GenericRSSFeed Input class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
final class GenericRSSFeed extends Input {
    /**
     * var array $items
     * @brief Input parameters.
     */
    private $items;

    /**
     * var array $config
     * @brief Input configuration.
     */
    private $config = array(
        'title'         => '',
        'link'          => '',
        'description'   => '',
        'language'      => '',
        'copyright'     => '',
        'webMaster'     => '',
        'lastBuildDate' => '',
        'generator'     => '',
        'image'         => null,
    );

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('GenericRSSFeed', $path_type);
        /* set plugin version */
        $this->version = '1.0';

        /* set plugin package */
        $this->plugin_package = 'Generic';

        /* set plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';
    }

    /* overwrite input methods */

    /**
     * Initialise input.
     * @param array $config
     * @param array $items
     * @return void
     */
    public function initialise($config=array(), $items=array()) {
        global $camyks;
        $this->config = array_merge($this->config, $config);
        $this->items = $items;
    }

    /**
     * Display input.
     * @return void
     */
    public function display() {
        /* Send header */
        header("Content-type: application/atom+xml; charset=UTF-8");

        /* Write header */
        echo '<'.'?xml version="1.0" encoding="UTF-8"?>'."\n";
        echo '<rss version="2.0" xmlns:atom="http://www.w3.org/2005/Atom">'."\n";
        echo '<channel>'."\n";

        /* Write mandatory config data */
        echo '<title>'.$this->config['title'].'</title>'."\n";
        echo '<link>'.$this->config['link'].'</link>'."\n";
        echo '<description><![CDATA['.$this->config['description'].']]></description>'."\n";

        /* Write optional config data */
        if ($this->config['language'] != '')
            echo '<language>'.$this->config['language'].'</language>'."\n";
        if ($this->config['copyright'] != '')
            echo '<copyright>'.$this->config['copyright'].'</copyright>'."\n";
        if ($this->config['webMaster'] != '')
            echo '<webMaster>'.$this->config['webMaster'].'</webMaster>'."\n";
        if ($this->config['lastBuildDate'] != '')
            echo '<lastBuildDate>'.$this->config['lastBuildDate'].'</lastBuildDate>'."\n";
        if ($this->config['generator'] != '')
            echo '<generator>'.$this->config['generator'].'</generator>'."\n";
        else
            echo '<generator>'.$this->get_translation('rssgenerator').'</generator>'."\n";

        /* Check and write for linked image */
        if (is_array($this->config['image'])) {
            echo '<image>'."\n";
            echo '<url>'.$this->config['image']['url'].'</url>'."\n";
            if (isset($this->config['image']['title']))
                echo '<title><![CDATA['.$this->config['image']['title'].']]></title>'."\n";
            if (isset($this->config['image']['width']))
                echo '<width>'.$this->config['image']['width'].'</width>'."\n";
            if (isset($this->config['image']['height']))
                echo '<height>'.$this->config['image']['height'].'</height>'."\n";
            if (isset($this->config['image']['link']))
                echo '<link>'.$this->config['image']['link'].'</link>'."\n";
            echo '</image>'."\n";
        }

        /* Write item list */
        foreach ($this->items as $item) {
            echo '<item>'."\n";
            /* Write mandatory item data */
            echo '<title>'.$item['title'].'</title>'."\n";
            echo '<link>'.$item['link'].'</link>'."\n";
            echo '<description><![CDATA['.$item['description'].']]></description>'."\n";
            /* Write optional item data */
            if (isset($item['author']))
                 echo '<author>'.$item['author'].'</author>'."\n";
            if (isset($item['date']))
                 echo '<pubDate>'.date('r', $item['date']).'</pubDate>'."\n";
            if (isset($item['isPermalink']))
                 echo '<guid isPermaLink="'.$item['isPermalink'].'">'.$item['link'].'</guid>'."\n";
            echo '</item>'."\n";
        }
        echo '</channel>'."\n";
        echo '</rss>'."\n";
        die();
    }
}
?>