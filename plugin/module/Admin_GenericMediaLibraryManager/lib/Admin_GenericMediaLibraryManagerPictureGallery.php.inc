<?php
/**
 * @brief Admin_GenericMediaLibraryManager Module picture gallery library
 * @details Plugin, Module Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1.1
 * @date Creation: Jun 2015
 * @date Modification: Jan 2021
 * @copyright 2015 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Admin_GenericMediaLibraryManagerPictureGallery class.
 */
final class Admin_GenericMediaLibraryManagerPictureGallery extends ModuleLibrary {
    /**
     * var array $pictures
     * @brief Picture list.
     */
    public $pictures = array();

    /**
     * Class constructor.
     * @param integer $id
     * @param Module $module
     * @return void
     */
    public function __construct($id, &$module) {
        parent::__construct($id, $module);

        /* Define main attributes */
        $this->add_newItem('status', 'db', 'int', 'tinyint unsigned', '', 0);
        $this->add_newItem('cdate', 'db', 'date', 'bigint unsigned', '', time());
        $this->add_newItem('title', 'db', 'text', 'varchar', 128, '', true);
        $this->add_newItem('summary', 'db', 'text', 'text', '', '', true);
        $this->add_newItem('content', 'db', 'text', 'text', '', '', true);
        $this->add_newItem('defaultPicture', 'db', 'int', 'bigint unsigned', '', 0);

        /* Temporary items */
        $this->add_newItem('pictures', 'temp', 'int', '', '', 0);
        $this->add_newItem('defaultThumb', 'temp', 'text', '', '', '');

        /* Generic initialisation */
        $this->init_library();
    }

    /* Override ModuleLibrary methods */

    /**
     * Build sql condition for lists.
     * @param array $params
     * @return string
     */
    public function build_SQLCondition($params) {
        if (isset($params['status']) and $params['status'] > -1)
            return 'status='.$params['status'];
        return '';
    }

    /**
     * Delete object.
     * @return boolean success
     */
    public function delete() {
        /* delete objects */
        if (!parent::delete())
            return false;

        /* delete pictures files */

        /* delete pictures db entries */

        /* Return result */
        return true;
    }

    /* Specific tool methods */

    /**
     * Return single object status list.
     * @return array
     */
    public function get_statusList() {
        return array(
            0 => $this->get_translation('picturegallerystatus_inactive'),
            1 => $this->get_translation('picturegallerystatus_public'),
            2 => $this->get_translation('picturegallerystatus_private'),
       );
    }

    /**
     * Return multi object status list.
     * @param boolean $full
     * @return array
     */
    public function get_multiStatusList($full=false) {
        $list = array();
        if ($full)
            $list['-1'] = $this->get_translation('picturegalleries_all');
        $list['0'] = $this->get_translation('picturegalleriesstatus_inactive');
        $list['1'] = $this->get_translation('picturegalleriesstatus_public');
        $list['2'] = $this->get_translation('picturegalleriesstatus_private');
        return $list;
    }

    /**
     * Return single object status list.
     * @return array
     */
    public function get_statusIconList() {
        return array(
            0 => '<img src="'.$this->_libParent->theme->get_pictURL('empty', 12, 'std').'" alt="'.$this->get_translation('picturegallerystatus_inactive').'" />',
            1 => '<img src="'.$this->_libParent->theme->get_pictURL('valid', 12, 'std').'" alt="'.$this->get_translation('picturegallerystatus_public').'" />',
            2 => '<img src="'.$this->_libParent->theme->get_pictURL('minus', 12, 'std').'" alt="'.$this->get_translation('picturegallerystatus_private').'" />',
       );
    }

    /**
     * Return object list.
     * @param array $params
     * @return array
     */
    public function get_list($params=array()) {
        global $camyks;

        /* Build default params list */
        $dParams = array('status'=>-1, 'ids'=>-1, 'language'=>$camyks->current_language, 'load_pictures'=>0, 'load_defaultThumb'=>0, 'limit'=>-1, 'count'=>-1, 'order'=>'cdate', 'orderway'=>'desc');

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        /* Load list */
        $list = $this->get_objectList($params['language'], $where, $params['limit'], $params['count'], $params['order'], $params['orderway']);

        /* Check for load pictures option */
        if ($params['load_pictures'] > 0) {
            $galleryIds = array();
            foreach ($list as $gallery)
                $galleryIds[] = $gallery->id;
            $pictures = $this->get_pictures(array('galleries'=>$galleryIds, 'status'=>$params['status']==-1?-1:1));
            foreach ($pictures as $picture) {
                if (!isset($list[$picture->vars['gallery']]))
                    continue;
                $list[$picture->vars['gallery']]->pictures[$picture->id] = &$picture;
            }
        }

        /* Check for load default thumb option */
        if ($params['load_defaultThumb'] > 0) {
            if ($params['load_pictures'] > 0) {
                /* Search thumbs in loaded pictures */
                foreach ($list as &$gallery) {
                    if (isset($gallery->pictures[$gallery->vars['defaultPicture']]))
                        $gallery->vars['defaultThumb'] = $gallery->pictures[$gallery->vars['defaultPicture']]->vars['thumb'];
                    else {
                        foreach ($gallery->pictures as $p) {
                            $gallery->vars['defaultThumb'] = $p->vars['thumb'];
                            break;
                        }
                    }
                }

            } else {
                /* Search thumbs in default value */
                $pictureIds = array();
                foreach ($list as $gallery) {
                    if ($gallery->vars['defaultPicture'] > 0)
                        $pictureIds[] = $gallery->vars['defaultPicture'];
                }
                $pictures = $this->get_pictures(array('ids'=>$pictureIds));
                foreach ($pictures as $picture) {
                    if (!isset($list[$picture->vars['gallery']]))
                        continue;
                    $list[$picture->vars['gallery']]->vars['defaultThumb'] = $picture->vars['thumb'];
                }

                /* Search thumb for "no default value" */
                $galleryIds = array();
                foreach ($list as $gallery) {
                    if ($gallery->vars['defaultThumb'] == '')
                        $galleryIds[] = $gallery->id;
                }
                $pictures = $this->get_galleriesFirstPictures(array('galleries'=>$galleryIds, 'status'=>$params['status']==-1?-1:1));
                foreach ($pictures as $picture) {
                    if (!isset($list[$picture->vars['gallery']]))
                        continue;
                    $list[$picture->vars['gallery']]->vars['defaultThumb'] = $picture->vars['thumb'];
                }
            }
        }

        /* Return list */
        return $list;
    }

    /**
     * Return product count with given params.
     * @param array $params
     * @return array
     */
    public function count($params=array()) {
        global $camyks;
        $p = array('status'=>-1, 'ids'=>-1);
        $params = array_merge($p, $params);
        $where = $this->build_whereStatement($params);

        return $this->get_objectCount($where);
    }

    /**
     * Return title list.
     * @param array $params
     * @return array
     */
    public function get_titleList($params=array()) {
        global $camyks;

        /* Build default params list */
        $dParams = array('status'=>-1, 'addNone'=>0, 'addAll'=>0, 'language'=>$camyks->current_language);

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Build where statement */
        $where = $this->build_whereStatement($params);

        $l = array();
        if ($params['addNone'] == 1)
            $l['-1'] = $this->get_translation('picturegallery_none');
        if ($params['addAll'] == 1)
            $l['0'] = $this->get_translation('picturegalleries_all');

        /* Return title list */
        return $l + $this->get_nameList('title', $where, $params['language']);
    }

    /**
     * Build where statement from params.
     * @param array $params
     * @return string
     */
    private function build_whereStatement($params=array()) {
        $w = array();

        /* Check status */
        if ($params['status'] != -1)
            $w[] = 'status = '.$params['status'];

        /* Return result */
        return implode(' and ', $w);
    }

    /**
     * Load pictures.
     * @param array $params
     * @return boolean success
     */
    private function load_pictures($params=array()) {
        /* Build default params list */
        $dParams = array('gallery'=>$this->id);

        /* Merge params */
        $params = array_merge($dParams, $params);

        /* Load pictures */
        $this->pictures = $this->_libParent->get_pictureList($params);
        return true;
    }

    /**
     * Return pictures.
     * @param array $params
     * @return array
     */
    public function get_pictures($params=array()) {
        return $this->_libParent->get_pictureList($params);
    }

    /**
     * Return first pictures for given galleries.
     * @param array $params
     * @return arrray
     */
    public function get_galleriesFirstPictures($params=array()) {
        return $this->_libParent->get_firstPicturesList($params);
    }

    /**
     * Check for default picture.
     * @param int $pictureId
     * @return void
     */
    public function check_forDefaultPicture($pictureId=0) {
        if ($pictureId == 0) return;
        if ($this->vars['defaultPicture'] > 0)
            return;
        $this->_libItems['defaultPicture']->value = $pictureId;
        $this->update_databaseSpecificItems(array('defaultPicture'));
    }
}
?>
