<?php
/**
 * @brief Admin_GenericEmailingManager module, emailing library.
 * @details Plugin / Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.3
 * @date Creation: Dec 2012
 * @date Modification: Jan 2026
 * @copyright 2012 - 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericEmailingManagerEmailing class.
 */
final class Admin_GenericEmailingManagerEmailing extends ModuleLibrary {
    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Admin attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('cdate', 'db', 'int', 'bigint unsigned', '', time());
        $this->add_newItem('sdate', 'db', 'int', 'bigint unsigned', '', 0);
        $this->add_newItem('edate', 'db', 'int', 'bigint unsigned', '', 0);

        /* Main attributes */
        $this->add_newItem('contact_source', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('contact_group', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('email_title', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('email_content', 'db', 'text', 'text','', '');

        $this->add_newItem('sender_name', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('sender_email', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('replyto_name', 'db', 'text', 'varchar', 64, '');
        $this->add_newItem('replyto_email', 'db', 'text', 'varchar', 128, '');

        /* File attributes */
        $this->add_newItem('email_contentfile', 'file', 'email_contents', '', '', '');

        /* Advanced params attributes */
        $this->add_newItem('advanced_envelope_email', 'db', 'text', 'varchar', 128, '');
        $this->add_newItem('advanced_include_listunsub', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('advanced_sending_interval', 'db', 'int', 'float unsigned', '', 0);

        $this->config = null;

        /* generic initialisation */
        $this->init_library();
    }

    /* Mark: Override ModuleLibrary methods */

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        $search = array();

        if (isset($params['status']) and $params['status']!='' and $params['status'] > -1)
            $search[] = 'status='.$params['status'];

        return implode(' and ', $search);
    }

    /**
     * Check object data.
     * @return boolean success
     */
    public function check_data() {
        /* Load emailing config */
        $this->load_config();

        /* Check for content file */
        if ($this->_libItems['email_contentfile']->upload) {

            $contentFile = $_FILES['email_contentfile']['tmp_name'];
            if (file_exists($contentFile)) {

                /* Read content from file */
                $content = file_get_contents($contentFile);

                /* Parse content */
                $data = $this->parse_emailContent($content);
                $this->config->vars['content_images'] = $data['images'];
                $this->config->vars['content_links'] = $data['links'];
                $this->_libItems['email_content']->value = $data['content'];
            }
        } elseif ($this->id > 0) {
            if ($this->_libItems['email_content']->value == '') {
                /* Load previous content */
                $old = $this->get_newObject($this->id);
                $old->get();
                $old->get_fromItems();

                /* Copy previous email content */
                $this->_libItems['email_content']->value = $old->vars['email_content'];
            }
        }

        /* Check image upload */
        foreach ($this->config->vars['content_images'] as $index => $name) {
            $file = 'email_contentimage'.$index;

            if (isset($_FILES[$file]) and $_FILES[$file]['name'] != '') {
                /* complete folder path */
                $path = $this->get_imageFolderPath();
                folder_completePath($path, 0771);

                /* move images to folder */
                if ($name == $_FILES[$file]['name']) {
                    $path .= '/'.$_FILES[$file]['name'];
                    move_uploaded_file($_FILES[$file]['tmp_name'], $path);
                }
            }
        }

        return true;
    }

    /**
     * Save object and current.
     * @return boolean success
     */
    public function save() {
        /* generic object save */
        if (!parent::save())
            return false;

        /* check config name for new objects */
        if ($this->config->name == 'emailing0') {
            $this->config->name = 'emailing'.$this->id;
            $this->config->vars['emailing_id'] = $this->id;
        }

        /* save config */
        return $this->config->save();
    }

     /**
      * get object from items
      * @return void
      */
     public function get_fromItems() {
         parent::get_fromItems();

         /* load emailing config */
         $this->load_config();

         $this->vars['valid_images'] = 0;

         /* check for files */
         foreach ($this->config->vars['content_images'] as $index => $file) {
             if (file_exists($this->get_imageFolderPath().'/'.$file)) {
                 $this->vars['email_contentimage'.$index] = $this->get_imageFolderPath().'/'.$file;
                 $this->vars['valid_images']++;
             }
         }
     }

    /* Mark: Check methods */

    /**
     * Return if object is still editable.
     * @return void
     */
    public function is_editable() {
        return ($this->vars['status'] == 0);
    }

    /* Mark: Attribute values methods */

    /**
     * Return object status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('emailingstatus_opened'),
            1 => $this->get_translation('emailingstatus_started'),
            2 => $this->get_translation('emailingstatus_done'),
        );
    }

    /**
     * Return objects status list.
     * @param boolean $more
     * @return array
     */
    public function get_multiStatusList($more=false) {
        $l = array();
        if ($more)
            $l['-1'] = $this->get_translation('emailings_all');
        return $l + array(
            0 => $this->get_translation('emailingsstatus_opened'),
            1 => $this->get_translation('emailingsstatus_started'),
            2 => $this->get_translation('emailingsstatus_done'),
        );
    }

    /**
     * Return object status list/
     * @return array
     */
    public function get_statusIconList() {
        return array(
            0 => '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="" border="0" />',
            1 => '<img src="'.$this->_libParent->theme->get_pictURL('minus', 12, 'std').'" alt="" border="0" />',
            2 => '<img src="'.$this->_libParent->theme->get_pictURL('valid', 12, 'std').'" alt="" border="0" />',
        );
    }

    /* Mark: Display methods */

    /**
     * Return group title.
     * @return string
     */
    public function get_groupTitle() {
        $groups = $this->_libParent->get_contactGroupList(true);
        return $groups[$this->vars['contact_group']];
    }

    /* Mark: Email content related methods */

    /**
     * Parse email content.
     * @param string $content
     * @return array
     */
    public function parse_emailContent($content='') {
        /* Initialise all replacements to do at the end */
        $patterns = array();
        $replaces = array();

        /* Initialise links and images lists */
        $links = array();
        $images = array();

        /* Get images urls */
        preg_match_all('/src="([^"]*)"/i', $content, $matches);

        /* Save image list */
        foreach ($matches[1] as $img) {
            if (!preg_match('/http?s:\/\//', $img) and !in_array(basename($img), $images)) {
                $images[] = basename($img);
                /* prepare path replacement */
                $patterns[] = '#src="'.$img.'"#i';
                $replaces[] = 'src="{image_path}'.basename($img).'"';
            }
        }

        /* Get links urls */
        if (preg_match_all('/href="(https?:\/\/[^"]*)"/i', $content, $matches)) {

            /* Save links urls */
            $matches = array_values(array_unique($matches[1]));

            /* Replace links urls with internal value */
            foreach($matches as $index => $link) {
                $links[] = $link;
                /* prepare path replacement */
                $patterns[] = '#href="'.preg_replace('/\?/', '\?', $link).'"#i';
                $replaces[] = 'href="{link_'.$index.'}"';
            }
        }

        /* Get close body tag */
        if (preg_match_all('/<\/body>/i', $content, $matches)) {
            foreach ($matches[0] as $tag) {
                /* prepare path replacement */
                $patterns[] = '#</body>#i';
                $replaces[] = '<img src="{opened_img}" alt="" border="0" width="0" height="0" style="display:none; width:0; height:0;"></body>';
            }
        }

        /* Replace images path and links url with internal value */
        $content = preg_replace($patterns, $replaces, $content);

        return array(
            'content'   => $content,
            'images'    => $images,
            'links'     => $links,
        );
    }

    /**
     * Send built email content.
     * @param array $params
     * @return void
     */
    public function get_emailContent($params=array()) {
        /* default params */
        $dParams = array('image_path'=>'');
        $params = array_merge($dParams, $params);

        $c = $this->vars['email_content'];

        $patterns = array();
        $replacements = array();

        foreach ($params as $name => $value) {
            $patterns[] = '/{'.$name.'}/';
            $replacements[] = nl2br(htmlentities($value));
        }

        /* add some html specificities */
        $patterns[] = '/<br ?\/>/';
        $replacements[] ='<br>';

        /* do replacements */
        $c = preg_replace($patterns, $replacements, $c);

        /* return result */
        return $c;
    }

    /**
     * Return content file description
     * @return string
     */
    public function get_contentFileDescription() {
        if ($this->vars['email_contentfile'] == '') {
            if ($this->vars['email_content'] != '')
                return '<span class="eContent3">'.$this->get_translation('email_insertedcontent').'</span>';
            return $this->get_translation('none');
        }
        $f = new FSFile($this->vars['email_contentfile']);
        return $f->hsize.', '.$f->typedesc;
    }

    /* Mark: Pictures related methods */

    /**
     * Return image folder path.
     * @return array
     */
    public function get_imageFolderPath() {
        return $this->_libParent->get_varFilePath('').'email_images/emailing'.$this->id;
    }

    /**
     * Return image folder URL
     * @return array
     */
    public function get_imageFolderURL() {
        return $this->_libParent->get_varFileURL('', true).'email_images/emailing'.$this->id;
    }

    /* Mark: Config related methods */

    /**
     * Load config.
     * @return boolean success
     */
    public function load_config() {
        if ($this->config != null)
            return;
        $this->config = new Admin_GenericEmailingManagerEmailingConfig('emailing'.$this->id, $this->_libParent);
        $this->config->get();
    }

    /* Mark: External methods */

    /**
     * Import from data.
     * @param array $params
     * @return boolean success
     */
    public function import_fromData($params) {
        /* Load emailing config */
        $this->load_config();

        /* Load data from params */
        $this->get_fromArray($params, null, true);

        /* Parse content */
        $data = $this->parse_emailContent($params['email_content']);
        $this->config->vars['content_images'] = $data['images'];
        $this->config->vars['content_links'] = $data['links'];
        $this->_libItems['email_content']->value = $data['content'];

        /* Save content */
        if (!$this->save())
            return false;

        /* Create emailing picture folder path */
        $path = $this->get_imageFolderPath();
        folder_completePath($path, 0771);

        /* Copy pictures from params into emailing picture folder */
        foreach ($params['images'] as $name => $originPath) {
            if (in_array($name, $data['images'])) {
                /* Check file exists and is identical */
                if (file_exists($path.'/'.$name) and md5_file($originPath) == md5_file($path.'/'.$name))
                    continue;
                /* Copy origin file to newsletter pictures folder */
                copy ($originPath, $path.'/'.$name);
            }
        }

        /* Return success */
        return true;
    }
}
?>
