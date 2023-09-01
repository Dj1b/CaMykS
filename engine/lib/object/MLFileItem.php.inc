<?php
/**
 * @brief File item of Module Library Item
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jul 2007
 * @date Modification: Sep 2023
 * @copyright 2007 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * MLFileItem class.
 * @author CaMykS Team <camyks.contact@gmail.com>
 */
class MLFileItem extends ModuleLibraryItem {
    /**
     * @var string $folder
     * @brief Folder repository for files.
     */
    public $folder;

    /**
     * @var string $path
     * @brief Folder path for files.
     */
    public $path;

    /**
     * @var string $url
     * @brief Folder url for files.
     */
    public $url;

    /**
     * @var boolean $upload
     * @brief Is file in upload process.
     */
    public $upload = false;

    /**
     * @var string $uploadedFileName
     * @brief File original name.
     */
    public $uploadedFileName = '';

    /**
     * @var string $uploadedTempName
     * @brief File temporary name.
     */
    public $uploadedTempName = '';

    /**
     * @var boolean $delete
     * @brief Is file in delete process.
     */
    public $delete = false;

    /**
     * Class constructor.
     * @param string $name
     * @param string $folder
     * @param string $path
     * @param string $url
     * @return void
     */
    public function __construct($name, $folder, $path, $url) {
        $this->name = $name;
        $this->folder = $folder;
        $this->path = $path;
        $this->url = $url;
    }

    /**
     * Initialise object with empty value.
     * @return void
     */
    public function initialise() {
        $this->value = '';
    }

    /**
     * Load object value.
     * @param integer $_libObjId the parent object id
     * @return boolean
     */
    public function get($_libObjId) {
        /* get file path */
        if (($file = $this->exists($this->path.'/'.$this->get_folder($_libObjId).'/', $this->name.$_libObjId)) != '')  {
            $this->value = $this->url.'/'.$this->get_folder($_libObjId).'/'.$file;
        }
        return true;
    }

    /**
     * Save file item.
     * @param integer $_libObjId the parent object id
     * @return boolean
     */
    public function save($_libObjId) {
        if ($this->upload or $this->delete) {
            /* create parent library object folder */
            folder_completePath ($this->path.'/'.$this->get_folder($_libObjId),  0771);
            /* try to delete old file */
            $this->delete($_libObjId);
        }

        if ($this->upload) {
            /* get file extension */
            if (preg_match('/.*\.([^\.]*)/', $this->uploadedFileName, $ext))
                $ext = $ext[1];
            else
                $ext = '';

            /* add file */
            $path = $this->path.'/'.$this->get_folder($_libObjId).'/'.$this->name.$_libObjId.'.'.$ext;
            if (!move_uploaded_file($this->uploadedTempName, $path) and $this->get($_libObjId))
                return false;

            /* auto rotate picture with orientation in exif */
            $this->update_orientation($path);
        }

        /* return sucess */
        return true;
    }

    /**
     * Delete file.
     * @param integer $_libObjId the parent object id
     * @return boolean
     */
    public function delete($_libObjId) {
        if (($file = $this->exists($this->path.'/'.$this->get_folder($_libObjId).'/', $this->name.$_libObjId)) != '')
            unlink($this->path.'/'.$this->get_folder($_libObjId).'/'.$file);
        return true;
    }

    /**
     * Reset file folder by deleting all files.
     * @return boolean
     */
    public function reset() {
        return $this->uninstall() and $this->install();
    }

    /**
     * Install item by creating folders.
     * @return boolean
     */
    public function install() {
        /* create folders in site plugin */
        return folder_completePath($this->path.'/'.$this->get_folder(),  0771);
    }

    /**
     * Uninstall item.
     * @return boolean
     */
    public function uninstall() {
        return folder_delete($this->path.'/'.$this->get_folder(), true);
    }

    /**
     * Load object value from header.
     * @param string $prefix
     * @return void
     */
    public function get_fromHeader($prefix='') {
        /* set header name value */
         $name = $prefix.$this->name;

        /* load values */
        if (isset($_FILES[$name]) and $_FILES[$name]['name'] != '') {
            $this->uploadedFileName = $_FILES[$name]['name'];
            $this->uploadedTempName = $_FILES[$name]['tmp_name'];
            $this->upload = true;
        } else if (isset($_REQUEST[$name.'_deletefile']) and $_REQUEST[$name.'_deletefile']==1)
            $this->delete = true;
    }

    /**
     * Return item values as structured array $name => $value
     * @return array
     */
    public function get_exportedValue() {
        return array($this->name=>$this->value);
    }

    /**
     * Return item file existence.
     * @param string $path the folder path
     * @param string $filebase the file name base
     * @return string
     */
    public function exists($path, $filebase) {
        $filelist = glob($path.$filebase.'.*');

        if (count($filelist) == 0)
            return '';
        else
            return substr($filelist[0], strlen($path));
    }

    /**
     * Return real file name while uploading it.
     * @return string
     */
    public function get_uploadedFileName() {
        return $this->uploadedFileName;
    }

    /**
     * Return temporary file name while uploading it
     * @return string
     */
    public function get_temporaryFileName() {
        return $this->uploadedTempName;
    }

    /**
     * Return updated folder with parent id.
     * @param integer $_libObjId
     * @return string
     */
    public function get_folder($_libObjId=0) {
        return preg_replace('/%%ID%%/', $_libObjId, $this->folder);
    }

    /**
     * Check orientation and auto rotate picture.
     * @param string $picture
     * @return boolean sucess
     */
    protected function update_orientation($picture='') {
        /* Check exif */
        if (!function_exists('exif_read_data'))
            return false;

        /* load picture exif */
        $exif = @exif_read_data($picture);

        /* no exif data, quit */
        if ($exif === false)
            return false;

        /* check orientation from exif */
        if (isset($exif['Orientation']))
            $orientation = $exif['Orientation'];
        elseif (isset($exif['COMPUTED']['Orientation']))-
            $orientation = $exif['COMPUTED']['Orientation'];
        else
            return true;

        /* orientation is correct, quit */
        if ($orientation == 1)
            return true;

        /* rotate picture to follow given orientation */
        $img = new CImage($picture);
        $img->update_JPGQuality(90);

        switch($orientation) {
            case 3:
                $img->rotate(array('angle'=>180));
                break;
            case 6:
                $img->rotate(array('angle'=>-90));
                break;
            case 8:
                $img->rotate(array('angle'=>90));
                break;
        }
        return $img->save_image($picture);
    }
}
?>
