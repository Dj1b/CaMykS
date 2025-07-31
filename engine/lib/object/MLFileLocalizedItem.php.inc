<?php
/**
 * @brief File localised item of Module Library item
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jul 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MLFileItem class.
 */
final class MLFileLocalizedItem extends MLFileItem {
    /**
     * @var array $value
     * @brief Item current values.
     */
    public $value = array();

    /**
     * @var array $upload
     * @brief Are files in upload process.
     */
    public $upload = array();

    /**
     * @var array $uploadedFileName
     * @brief Files original name.
     */
    public $uploadedFileName = array();

    /**
     * @var array $uploadedTempName
     * @brief Files temporary name.
     */
    public $uploadedTempName = array();

    /**
     * @var array $delete
     * @brief Are files in delete process.
     */
    public $delete = array();

    /**
     * Class constructor.
     * @param string $name
     * @param string $folder
     * @param string $path
     * @param string $url
     */
    public function __construct($name, $folder, $path, $url) {
        $this->name = $name;
        $this->folder = $folder;
        $this->path = $path;
        $this->url = $url;
    }

    /**
     * Initialise object with empty values.
     * @return void
     */
    public function initialise() {
        global $camyks;
        $this->value = array();
        foreach ($camyks->get_confValue('editing_languages') as $l) {
            $this->value[$l] = '';
        }
    }

    /**
     * Load object value.
     * @param integer $_libObjId the parent object id
     * @param string $language the language to get
     * @return boolean
     */
    public function get($_libObjId, $language=null) {
        global $camyks;

        $path = $this->path.'/'.$this->get_folder($_libObjId).'/';
        $url = $this->url.'/'.$this->get_folder($_libObjId).'/';

        if (isset($language)) {
            /* get specific language */
            if (($file = $this->exists($path , $this->name.$_libObjId.'_'.$language)) != '')
                $this->value[$language] = $url.$file;
            else
                $this->value[$language] = '';
        } else {
            /* get all language */
            foreach ($camyks->get_confValue('editing_languages') as $language) {
                if (($file = $this->exists($path, $this->name.$_libObjId.'_'.$language)) != '')
                    $this->value[$language] = $url.$file;
                else
                    $this->value[$language] = '';
            }
        }
        return true;
    }

    /**
     * Save files.
     * @param integer $_libObjId the parent object id
     * @return void
     */
    public function save($_libObjId) {
        /* initialise result value */
        $ok = true;

        /* check if there is at least one file to upload or delete */
        if (count($this->upload) == 0 and count($this->delete) == 0)
            return true;

        /* create parent library object folder */
        folder_completePath($this->path.'/'.$this->get_folder($_libObjId),  0771);

        /* try to delete removed files */
        foreach ($this->delete as $l) {
            $this->delete($_libObjId, $l);
        }

        /* update files */
        foreach($this->upload as $l) {
            /* try to delete old file */
            $this->delete($_libObjId, $l);

            /* get file extension */
            if (preg_match( '/.*\.([^\.]*)/', $this->uploadedFileName[$l], $ext))
                $ext = $ext[1];
            else
                $ext = '';

            /* add file */
            $path = $this->path.'/'.$this->get_folder($_libObjId).'/';
            $path .= $this->name.$_libObjId.'_'.$l.'.'.$ext;
            if (!move_uploaded_file($this->uploadedTempName[$l], $path))
                $ok = false;
            $this->get($_libObjId, $l);

            /* auto rotate picture with orientation in exif */
            $this->update_orientation($path);
        }
        return $ok;
    }

    /**
     * Delete files.
     * @param integer $_libObjId the parent object id
     * @param string $language the language
     * @return boolean
     */
    public function delete($_libObjId, $language=null) {
        global $camyks;
        $path = $this->path.'/'.$this->folder.'/';

        if (isset($language)) {
            /* delete given language file */
            if (($file = $this->exists($path , $this->name.$_libObjId.'_'.$language)) != '')
                unlink($this->path.'/'.$this->get_folder($_libObjId).'/'.$file);
        } else {
            /* delete all files */
            foreach ($camyks->get_confValue('editing_languages') as $language) {
                if (($file = $this->exists($path , $this->name.$_libObjId.'_'.$language)) != '')
                    unlink($this->path.'/'.$this->get_folder($_libObjId).'/'.$file);
            }
        }
        return true;
    }

    /**
     * Load object value from header.
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix='') {
        global $camyks;

        /* set header value name */
        $name = $prefix.$this->name;

        /* load values */
        foreach ($camyks->get_confValue('editing_languages') as $language) {
            if (isset($_FILES[$name.'_'.$language ]) and $_FILES[$name.'_'.$language]['name'] != '') {
                $this->uploadedFileName[$language] = $_FILES[$name.'_'.$language]['name'];
                $this->uploadedTempName[$language] = $_FILES[$name.'_'.$language]['tmp_name'];
                $this->upload[] = $language;
            } else if (isset($_REQUEST[$name.'_'.$language.'_deletefile']) and $_REQUEST[$name.'_'.$language.'_deletefile']==1)
                $this->delete[] = $language;
        }
    }

    /**
     * Return values as structured array.
     * @return array
     */
    public function get_exportedValue() {
        if (count($this->value) == 0)
            return array();
        $a = array();
        if (count($this->value) == 1) {
            foreach ($this->value as $l => $v) {
                $a[$this->name] = $v;
                $a[$this->name.'_'.$l] = $v;
            }
        } else {
            foreach ($this->value as $l => $v)
            $a[$this->name.'_'.$l] = $v;
        }
        return $a;
    }

    /**
     * Return real file name while uploading it.
     * @param mixed $language
     * @return string
     */
    public function get_uploadedFileName($language=false) {
        if ($language === false)
            return $this->uploadedFileName;
        if (isset($this->uploadedFileName[$language]))
            return $this->uploadedFileName[$language];
        return '';
    }

    /**
     * Return temporary file name while uploading it.
     * @param mixed $language
     * @return string
     */
    public function get_uploadedTempName($language=false) {
        if ($language === false)
            return $this->uploadedTempName;
        if (isset($this->uploadedTempName[$language]))
            return $this->uploadedTempName[$language];
        return '';
    }
}
?>
