<?php
/**
 * @brief File system file object library.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.2.1
 * @date Creation: Jun 2007
 * @date Modification: Jul 2025
 * @copyright 2007 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * FSFile class.
 */
final class FSFile {
    /**
     * @var string $filename
     * @brief File name.
     */
    public $filename;

    /**
     * @var string $path
     * @brief File path.
     */
    public $path;

    /**
     * @var string $fullpath
     * @brief Full file path with file name.
     */
    public $fullpath;

    /**
     * @var boolean $exists
     * @brief File exists.
     */
    public $exists;

    /**
     * @var integer $size
     * @brief File size in octet/byte.
     */
    public $size;

    /**
     * @var string $hsize
     * @brief Human readable file size.
     */
    public $hsize;

    /**
     * @var string $mime
     * @brief File mime.
     */
    public $mime;

    /**
     * @var string $type
     * @brief File type, first part of mime value.
     */
    public $type;

    /**
     * @var string $ext
     * @brief File extension.
     */
    public $ext;

    /**
     * @var integer $atime
     * @brief File last opening time.
     */
    public $atime;

    /**
     * @var integer $mtime
     * @brief File last modification time.
     */
    public $mtime;

    /**
     * @var integer $ctime
     * @brief File inode change time.
     */
    public $ctime;

    /**
     * @var string $mimedesc
     * @brief File mime description.
     */
    public $mimedesc;

    /**
     * @var string $typedesc
     * @brief File type description.
     */
    public $typedesc;

    /**
     * @var array $moreinfos
     * @brief File additional information.
     */
    public $moreinfos;

    /**
     * Class constructor.
     * @param string $path the path to the file
     * @param string $file the file name
     */
    public function __construct($path='', $file=null) {
        if (isset($file)) {
            $f = explode('?', $file);
            $file = $f[0];
            $this->filename = $file;
            $this->path = $path;
            $this->fullpath = $path.'/'.$file;
        } else {
            $f = explode('?', $path);
            $path = $f[0];
            $this->fullpath = $path;
            $p = explode('/', $path);
            $this->filename = array_pop($p);
            $this->path = implode('/', $p);
        }
        $this->exists = file_exists($this->fullpath);
        $this->moreinfos = array();
        $this->get();
    }

    /* methods */

    /**
     * Load file description.
     * @return void
     */
    private function get() {
        if ($this->exists === false) {
            return;
        }
        /* get file extension */
        if (preg_match('/.*\.([^\.]*)/', $this->filename, $ext))
            $this->ext = $ext[1];
        else
            $this->ext = '';

        /* get mime */
        $this->get_mime();
        /* get stat values */
        $this->get_stat();
        /* get description */
        $this->get_descriptions();
        /* get more infos */
        $this->get_moreInfos();
    }

    /**
     * Load file mime.
     * @return void
     */
    private function get_mime() {
        $this->mime = file_getMime($this->fullpath, $this->ext);
        $t = explode('/', $this->mime);
        $this->type = $t[0];
    }

    /**
     * Load file stats.
     * @return void
     */
    private function get_stat() {
        $stat = stat($this->fullpath);
        $this->size = $stat['size'];
        $this->atime = $stat['atime'];
        $this->mtime = $stat['mtime'];
        $this->ctime = $stat['ctime'];
        $this->inode = $stat['ino'];
    }

    /**
     * Load file description.
     * @return void
     */
    private function get_descriptions() {
        $this->typedesc = file_getTypeDescription($this->mime, $this->ext);
        $this->mimedesc = file_getMimeDescription($this->mime);
        $this->hsize = file_getFileSize($this->size);
    }

    /**
     * Load more information from file.
     * @return void
     */
    private function get_moreInfos() {
        if ($this->type == 'image') {
            $this->get_imageInfos();
        }
    }

    /**
     * Load more information from image file.
     * @return void
     */
    private function get_imageInfos() {
        $this->moreinfos = array_merge($this->moreinfos, file_getImageSize($this->fullpath));
    }

    /**
     * Return mime relative icon.
     * @param int $size
     * @param string $styles
     * @return string
     */
    public function get_mimeIcon($size=32, $styles='') {
        return file_getMimeIcon($this->mime, $size, $styles);
    }

    /**
     * Return mime relative icon URL.
     * @param int $size
     * @return string
     */
    public function get_mimeIconURL($size=32) {
        return file_getMimeIconURL($this->mime, $size);
    }

    /**
     * Download file to client browser.
     * @param string $title
     * @return void
     */
    public function download($title=null) {
        header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
        header('Content-Type: application/octet-stream');
        header('Content-Description: File Transfer');
        header('Content-Length: '.$this->size);
        if (isset($title)) {
            if (pathinfo($title, PATHINFO_EXTENSION) === '')
                $title .= '.'.$this->ext;
        } else {
            $title  = $this->filename;
        }
        header('Content-Disposition: attachment; filename="'.$title.'";');
        file_readfile($this->fullpath);
    }

    /**
     * Send file to client browser.
     * @param string $title
     * @return void
     */
    public function send($title=null) {
        header('Content-Type: '.$this->mime.'');
        if (isset($title)) {
            if (pathinfo($title, PATHINFO_EXTENSION) === '')
                $title .= '.'.$this->ext;
        } else {
            $title  = $this->filename;
        }
        header('Content-Disposition: inline; filename="'.$title.'"');
        file_readfile($this->fullpath);
    }

    /**
     * Return MD5 checksum of the file.
     * @param boolean $raw_output
     * @return string
     */
    public function md5($raw_output=false) {
        return md5_file($this->fullpath, $raw_output);
    }

    /**
     * Return file content.
     * @return string
     */
    public function get_contents() {
        return file_get_contents($this->fullpath);
    }

    /**
     * Return file content as base64 data.
     * @return string
     */
    public function get_base64Data() {
        return 'data:'.$this->mime.';base64,'.base64_encode(file_get_contents($this->fullpath));
    }
}
?>
