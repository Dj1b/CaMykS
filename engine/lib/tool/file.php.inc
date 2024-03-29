<?php
/**
 * @brief File specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.7.1
 * @date Creation: Jun 2005
 * @date Modification: Sep 2023
 * @copyright 2005 - 2023 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @todo complete file type, extension, and mime list
 */

/**
 * @def FILE_ICON_EXTENSION
 */
define('FILE_ICON_EXTENSION', 'gif');

/**
 * Write given file with given content.
 * @param string $file_path
 * @param string $content
 * @param boolean $deleteCache
 * @return boolean success
 */
function file_write($file_path, $content, $deleteCache=false) {
    /* check path to file to be in website */
    if (!file_isInPath($file_path))
        return false;

    /* write file */
    if (@file_put_contents($file_path, $content, LOCK_EX) !== false) {
        /* remove cache from OPCache */
        if ($deleteCache and function_exists('opcache_invalidate')) opcache_invalidate($file_path);

        /* return sucess */
        return true;
    } else {
        return false;
    }
}

/**
 * Return CaMykS header for PHP file.
 * @param string $desc
 * @param string $version
 * @return string
 */
function file_getPHPFileHeader($desc="", $version="none") {
    $str = "<?php\n";
    $str .= "/*\n";
    $str .= " * CaMykS Engine\n";
    $str .= " * Version\t: ".$version."\n";
    $str .= " * Date\t: ".date("M Y")."\n";
    $str .= " * ** Generated file ** \n";
    $str .= " * ".$desc."\n";
    $str .= " */\n";
    return $str;
}

/**
 * Return CaMykS footer for PHP file.
 * @return string
 */
function file_getPHPFileFooter() {
    return "?".">";
}

/**
 * Return CaMykS header for htaccess file.
 * @param string $desc
 * @param string $version
 * @return string
 */
function file_getHTAccessFileHeader($desc="", $version="none") {
    $str = "# CaMykS Engine\n";
    $str .= "# Version\t: ".$version."\n";
    $str .= "# Date\t: ".date("M Y")."\n";
    $str .= "# ** Generated file ** \n";
    $str .= "# ".$desc."\n\n\n";
    return $str;
}

/**
 * Return CaMykS ender for htaccess file.
 * @return string
 */
function file_getHTAccessFileEnder() {
    return "";
}

/**
 * Return file content.
 * @param string $file
 * @return string
 */
function file_getContent($file) {
    /* check path to file to be in website */
    if (!file_isInPath($file))
        return '';

    /* check file */
    if (!file_exists($file)) {
        return '';
    }

    /* return file content */
    return file_get_contents($file);
}

/**
 * Download file with curl.
 * @param string $file
 * @param string $path
 * @return void
 */
function file_download($file, $path) {
    /* check path to file to be in website */
    if (!file_isInPath($path))
        return;

    /* open file to be written */
    $ff = fopen($path, "w");

    /* init curl object */
    $dl = curl_init();

    /* fill curl object info */
    curl_setopt($dl, CURLOPT_URL, $file);
    curl_setopt($dl, CURLOPT_FILE, $ff);
    curl_setopt($dl, CURLOPT_HEADER, 0);

    /* download file */
    curl_exec($dl);

    /* end download */
    curl_close ($dl);
    fclose ($ff);
}

/*
 * Delete file.
 * @param string $file
 * @return boolean sucesss
 */
function file_delete($file) {
    if (file_isInPath($file))
      return @unlink($file);
    return false;
}

/**
 * Return file type icon.
 * @param string $mime
 * @param int $size
 * @return string
 */
function file_getMimeIconURL($mime='', $size=32) {
    global $camyks;

    /* get file extension from mime */
    switch ($mime) {
        /* pictures */
        case 'image/gif': case 'image/pjpeg': case 'image/jpeg': case 'image/png':
        case 'image/jp2': case 'image/tiff': case 'image/x-tiff': case 'image/bmp':
        case 'image/x-windows-bmp': case 'image/pict': case 'image/x-pict':
            $ext = 'image'; break;
        /* audio */
        case 'audio/aiff': case 'audio/x-aiff': case 'audio/mpeg': case 'audio/mpeg3':
        case 'audio/x-mpeg-3': case 'audio/midi': case 'audio/x-midi': case 'application/x-midi':
        case 'audio/x-mid': case 'music/crescendo': case 'x-music/x-midi': case 'audio/wav':
        case 'audio/x-wav':
            $ext = 'audio'; break;
        /* real audio */
        case 'audio/x-pn-realaudio': case 'audio/x-pn-realaudio-plugin':
        case 'audio/x-realaudio': case 'audio/x-pn-realaudio':
            $ext = 'realaudio'; break;
        /* text */
        case 'text/plain':
            $ext = 'txt'; break;
        /* css */
        case 'text/css':
            $ext = 'css'; break;
        /* rich text */
        case 'text/richtext': case 'application/rtf':  case 'application/x-rtf':
        case 'text/vnd.rn-realtext':
            $ext = 'richtext'; break;
        /* sgml */
        case 'text/sgml': case 'text/x-sgml':
            $ext = 'sgml'; break;
        /* video */
        case 'video/avi': case 'application/x-troff-msvideo': case 'video/msvideo':
        case 'video/x-msvideo': case 'video/mpeg': case 'video/x-mpeg':
        case 'video/x-mpeg2a': case 'video/x-ms-asf': case 'video/x-dv':
        case 'video/x-motion-jpeg': case 'video/quicktime':
            $ext = 'video'; break;
        /* compressed file */
        case 'application/x-rar-compressed': case 'application/x-zip-compressed':
        case 'application/x-ace-compressed': case 'application/x-zip':
        case 'application/zip': case 'application/x-tar': case 'application/gnutar':
        case 'application/x-stuffit': case 'application/x-sit': case 'application/binhex':
        case 'application/binhex4': case 'application/mac-binhex': case 'application/mac-binhex40':
        case 'application/x-binhex40': case 'application/x-mac-binhex40': case 'multipart/x-gzip':
        case 'application/x-compressed': case 'application/x-gzip': case 'application/x-bzip':
        case 'application/x-bzip2': case 'application/mac-compactpro':
        case 'application/x-compactpro': case 'application/x-cpt':
            $ext = 'archive'; break;
        /* source file */
        case 'text/x-java-source': case 'application/x-javascript': case 'text/x-pascal':
        case 'text/pascal': case 'text/x-script.perl': case 'text/x-script.python':
        case 'application/x-bsh': case 'application/x-sh': case 'application/x-shar':
        case 'text/x-script.sh':
            $ext = 'source'; break;
        /* xml */
        case 'text/xml': case 'application/xml': case 'text/html':
            $ext = 'xml'; break;
        /* disk image */
        case 'application/x-apple-diskimage':
            $ext = 'applediskimage'; break;
        /* mac binary */
        case 'application/mac-binary': case 'application/macbinary':
        case 'application/x-binary': case 'application/x-macbinary':
            $ext = 'macbinary'; break;
        /* director */
        case 'application/x-director':
            $ext = 'director'; break;
        /* Adobe Photoshop */
        case 'image/photoshop': case 'image/x-photoshop': case 'image/psd':
        case 'application/photoshop': case 'application/psd':
            $ext = 'psd'; break;
        /* Adobe Illustrator */
        case 'application/illustrator':
            $ext = 'vector'; break;
        /* generic SVG */
        case 'image/svg+xml': case 'image/svg':
            $ext = 'vector'; break;
        /* generic EPS */
        case 'application/eps': case 'application/x-eps': case 'image/eps':
        case 'image/x-eps':
            $ext = 'vector'; break;
        /* M$ */
        case 'application/msword': case 'application/vnd.ms-word':
        case 'application/word': case 'application/x-msword':
        case 'application/vnd.ms-office':
            $ext = 'word'; break;
        case 'application/mspowerpoint': case 'application/vnd.ms-powerpoint':
        case 'application/powerpoint': case 'application/x-mspowerpoint':
            $ext = 'ppt'; break;
        case 'application/msexcel': case 'application/excel': case 'application/x-excel':
        case 'application/x-msexcel': case 'application/vnd.ms-excel':
            $ext = 'xls'; break;
        /* generic postscript */
        case 'application/postscript':
            $ext = 'postscript'; break;
        /* pdf */
        case 'application/pdf':
            $ext = 'pdf'; break;
        /* flash movie */
        case 'application/x-shockwave-flash':
            $ext = 'swf'; break;
        default:
            $ext = 'generic';
    }

    /* check size */
    if (!in_array($size, array(16, 32, 64, 128))) {
        $size = 32;
    }

    /* check if mime icon exists */
    if (!file_exists($camyks->camyks_engine_path.'/data/img/mime/'.$ext.$size.'.'.FILE_ICON_EXTENSION)) {
        $ext = 'generic';
    }

    return $camyks->site_data_url.'/img/mime/'.$ext.$size.'.'.FILE_ICON_EXTENSION;
}

/**
 * Return file type icon.
 * @param string $mime
 * @param int $size
 * @param string $styles
 * @return string
 */
function file_getMimeIcon($mime='', $size=32, $styles='') {
    /* get icon */
    $icon = file_getMimeIconURL($mime, $size);

    /* return icon */
    return '<img src="'.$icon.'"'.' width="'.$size.'" height="'.$size.'" alt="" style="'.$styles.'" border="0" />';
}

/**
 * Return file type description.
 * @param string $mime
 * @param string $ext
 * @return string
 */
function file_getTypeDescription($mime='', $ext=null) {
  global $camyks;
    /* get file extension from mime */
    if (!isset($ext)) {
        $ext = explode ('/', $mime);
        $ext = $ext[count($ext)-1];
    }

    switch ($mime) {
        /* folder */
        case 'folder':
            return $camyks->get_translation('file_folder');
        /* image */
        case 'image/gif':
        case 'image/pjpeg':
        case 'image/jpeg':
        case 'image/png':
        case 'image/jp2':
        case 'image/tiff':
        case 'image/x-tiff':
        case 'image/bmp':
        case 'image/x-windows-bmp':
        case 'image/pict':
        case 'image/x-pict':
            return $camyks->get_translation('file_imagefile', strtoupper($ext));
        /* audio */
        case 'audio/aiff':
        case 'audio/x-aiff':
        case 'audio/mpeg':
        case 'audio/mpeg3':
        case 'audio/x-mpeg-3':
        case 'audio/midi':
        case 'audio/x-midi':
        case 'application/x-midi':
        case 'audio/x-mid':
        case 'music/crescendo':
        case 'x-music/x-midi':
        case 'audio/wav':
        case 'audio/x-wav':
            return $camyks->get_translation('file_audiofile', strtoupper($ext));
        case 'audio/x-pn-realaudio':
        case 'audio/x-pn-realaudio-plugin':
        case 'audio/x-realaudio':
        case 'audio/x-pn-realaudio':
            return $camyks->get_translation('file_audiofile', 'Real');
        /* text */
        case 'text/plain':
        case 'text/html':
        case 'text/richtext':
        case 'application/rtf':
        case 'application/x-rtf':
        case 'text/css':
        case 'text/sgml':
        case 'text/x-sgml':
            return $camyks->get_translation('file_textfile', strtoupper($ext));
        /* video */
        case 'video/avi':
        case 'application/x-troff-msvideo':
        case 'video/msvideo':
        case 'video/x-msvideo':
        case 'video/mpeg':
        case 'video/x-mpeg':
        case 'video/x-mpeg2a':
        case 'video/x-ms-asf':
        case 'video/x-dv':
        case 'video/x-motion-jpeg':
            return $camyks->get_translation('file_videofile', strtoupper($ext));
        case 'video/quicktime':
            return $camyks->get_translation('file_videofile', 'Quicktime');
        /* compressed file */
        case 'application/x-rar-compressed':
        case 'application/x-zip-compressed':
        case 'application/x-ace-compressed':
        case 'application/x-zip':
        case 'application/zip':
        case 'application/x-tar':
        case 'application/gnutar':
        case 'application/x-stuffit':
        case 'application/x-sit':
        case 'application/binhex':
        case 'application/binhex4':
        case 'application/mac-binhex':
        case 'application/mac-binhex40':
        case 'application/x-binhex40':
        case 'application/x-mac-binhex40':
        case 'multipart/x-gzip':
        case 'application/x-compressed':
        case 'application/x-gzip':
        case 'application/x-bzip':
        case 'application/x-bzip2':
        case 'application/mac-compactpro':
        case 'application/x-compactpro':
        case 'application/x-cpt':
            return $camyks->get_translation('file_compressedfile', strtoupper($ext));
        /* source file */
        case 'text/x-java-source':
            return $camyks->get_translation('file_sourcefile', 'Java');
        case 'application/x-javascript':
            return $camyks->get_translation('file_sourcefile', 'JavaScript');
        case 'text/x-pascal':
        case 'text/pascal':
            return $camyks->get_translation('file_sourcefile', 'Pascal');
        case 'text/x-script.perl':
            return $camyks->get_translation('file_sourcefile', 'Perl');
        case 'text/x-script.python':
            return $camyks->get_translation('file_sourcefile', 'Python');
        case 'text/xml':
        case 'application/xml':
            return $camyks->get_translation('file_sourcefile', 'XML');
        /* disk image */
        case 'application/x-apple-diskimage':
            return $camyks->get_translation('file_diskimagefile', 'Mac OS X');
        /* mac binary */
        case 'application/mac-binary':
        case 'application/macbinary':
        case 'application/x-binary':
        case 'application/x-macbinary':
            return $camyks->get_translation('file_genericfile', 'Mac Binary');
        /* director */
        case 'application/x-director':
            return $camyks->get_translation('file_genericfile', 'Adobe Director');
        /* M$ */
        case 'application/msword':
            return $camyks->get_translation('file_genericfile', 'Microsoft Word');
        case 'application/mspowerpoint':
        case 'application/vnd.ms-powerpoint':
        case 'application/powerpoint':
        case 'application/x-mspowerpoint':
        case 'application/vnd.openxmlformats-officedocument.presentationml.presentation':
            return $camyks->get_translation('file_genericfile', 'Microsoft PowerPoint');
        case 'application/excel':
        case 'application/x-excel':
        case 'application/msexcel':
        case 'application/x-msexcel':
        case 'application/vnd.ms-excel':
            return $camyks->get_translation('file_genericfile', 'Microsoft Excel');
        /* generic postscript */
        case 'application/postscript':
            return $camyks->get_translation('file_genericfile', 'Postscript');
        /* latext */
        case 'application/x-latex':
            return $camyks->get_translation('file_genericfile', 'LaTEX');
        /* pdf */
        case 'application/pdf':
            return $camyks->get_translation('file_genericfile', 'PDF');
        /* bytecode python */
        case 'application/x-bytecode.python':
            return $camyks->get_translation('file_genericfile', 'Python Bytecode');
        /* flash movie */
        case 'application/x-shockwave-flash':
            return $camyks->get_translation('file_genericfile', 'Flash Movie');
        /* default : unknown file */
        default:
            return $camyks->get_translation('file_unknownfile');
    }
}

/**
 * Return file mime description.
 * @param string $mime
 * @return string
 */
function file_getMimeDescription($mime='') {
    switch ($mime) {
        /* image */
        case 'image/jpeg':
            return '';
        case 'image/gif':
            return 'Graphic Interchange Format';
        case 'image/png':
            return 'Portable Network Graphics';
        case 'image/tiff':
            return 'Tag Image File Format';
        default:
            return '';
    }
}

/**
 * Return human readable file size.
 * @param int $size
 * @return string
 */
function file_getFileSize($size) {
    $t = language_getFileUnit();
    $l = array('', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y');
    $s = 0;
    while ($size > 1024) {
        $s++;
        $size /= 1024.00;
    }
    $size = ((int)($size*10)/10);

    if ($s == 0)
        return $size.' '.($t=='o'?'octets':'bytes');
    return $size.' '.$l[$s].$t;
}

/**
 * Return file mime type.
 * @param string $file
 * @param string $ext
 * @return string
 */
function file_getMime($file, $ext=null)  {
    /* check file */
    if (!file_exists($file))
        return '';

    /* try to get file info from finfo methods */
    if (($mime = _file_getMimeFromFinfo($file)) !== false)
        return $mime;

    /* try to get file info from mime content type method */
    if (($mime = _file_getMimeFromMimeContentType($file)) !== false)
        return $mime;

    /* try to get file info from internal method */
    return _file_getMimeFromExtension($file, $ext);
}

/**
 * Return image size in pixel as formatted string.
 * @param string $file
 * @return string
 */
function file_getImageSize($file) {
    if (file_isImage($file)) {
        $d = getimagesize($file);
        return array('width'=>$d[0], 'height'=>$d[1]);
    }
    return array();
}

/**
 * Return image type
 * @param string $file
 * @return string
 */
function file_getImageType($file) {
    /* return image type from EXIF */
    if (function_exists('exif_imagetype') and ($type = @exif_imagetype($file)) !== false) {
        switch ($type) {
            case 1: return 'gif';
            case 2: return 'jpg';
            case 3: return 'png';
            case 5: return 'psd';
            case 6: return 'bmp';
        }
    }

    /* by default return type from its extension */
    preg_match('/.([^.]{1,4})$/', $file, $ext);
    return strtolower($ext[1]);
}

/**
 * Check if file is an image.
 * @param string $file
 * @return boolean
 */
function file_isImage($file) {
    if (file_exists($file)) {
        /* Check exif is available */
        if (!function_exists('exif_imagetype'))
            return false;

        /* Check file has stats */
        $s = stat($file);
        if ($s['size'] > 10)
            return (@exif_imagetype($file) > 0);
    }
    return false;
}

/**
 * Equivalent to php readfile, without the 2Mo limitation on PHP 5.0.0 to 5.0.4 bug.
 * @param string $filename
 * @param boolean $retbytes
 * @return mixed
 */
function file_readfile($filename, $retbytes=true) {
    /* check path to file to be in website */
    if (!file_isInPath($filename))
        return;

    /* load file size */
    $s = stat($filename);
    $s = (int)($s['size']/1024/1024);

    /* check PHP version and file size *
    if (preg_match('/(5.0.[0-4])/', phpversion(), $result) == 0 or $s < 80) {
        readfile($filename, $retbytes);
    }
    */

    $chunksize = 1*(1024*1024);
    $buffer = '';
    $cnt =0;
    $handle = fopen($filename, 'rb');
    if ($handle === false) {
        return false;
    }
    while (!feof($handle)) {
        $buffer = fread($handle, $chunksize);
        echo $buffer;
        ob_flush();
        flush();
        if ($retbytes) {
            $cnt += strlen($buffer);
        }
    }
    $status = fclose($handle);
    if ($retbytes && $status) {
        return $cnt;
    }
    return $status;
}

/**
 * Write a configration file.
 * @param string $file_path
 * @param string $desc
 * @param array $datas
 * @return boolean success
 */
function file_writeConfFile($file_path, $desc, $datas) {
    $file_content = file_getPHPFileHeader($desc);
    /* check for global value */
    $str = '';
    $str2 = '';
    foreach ($datas as $data_name => $data_content) {
        if (isset($data_content['isGlobal']) and $data_content['isGlobal']) {
            $str .= $data_name.", ";
        }
        if (isset($data_content['desc']) and trim($data_content['desc']) != '') {
            $str2 .= '// '.$data_content['desc']."\n";
        }
        $str2 .= $data_name.' = '.data_serialize($data_content['value']).';'."\n";
    }

    if ( $str!= '') {
        $file_content .= 'global '.substr($str, 0, strlen($str)-2).";\n\n";
    }
    $file_content .= $str2;
    $file_content .= file_getPHPFileEnder();
    return file_write($file_path, $file_content);
}

/**
 * Search a file in a folder.
 * @param string $pattern
 * @param string $rootPath
 * @param integer $globFlags
 * @return array
 */
function file_search($pattern='*', $rootPath='./', $globFlags=0) {
    /* check path to file to be in website */
    if (!folder_isInPath($rootPath))
        return;

    /* do the search */
    $paths = glob($rootPath.'*', GLOB_MARK|GLOB_ONLYDIR|GLOB_NOSORT);
    $files = glob($rootPath.$pattern, $globFlags);
    foreach ($paths as $path) {
        $files = array_merge($files, file_search($pattern, $path, $globFlags));
    }
    return $files;
}

/**
 * MD5_file replacement, to avoid 403 errors.
 * @param string $file
 * @param array $contextParams
 * @return mixed
 */
function file_md5($file, $contextParams=array()) {
    global $camyks;

    /* Check for no context */
    if (count($contextParams) == 0) {
        /* Check default md5_file method */
        if (($v = @md5_file($file)) !== false)
            return $v;

        /* Check if function exists */
        if (!function_exists('error_get_last'))
            return false;

        /* Get error from md5_file method */
        $error = error_get_last();

        /* Check operation failed error */
        if (preg_match('/operation failed/', $error['message']))
            return false;

        /* Check HTTP 404 error : file not found */
        if (preg_match('/HTTP\/1.(0|1) 404/', $error['message']))
            return false;

        /* Check HTTP 403 error : forbidden or HTTP 400 error : bad request */
        if (!preg_match('/HTTP\/1.(0|1) 403/', $error['message']) and !preg_match('/HTTP\/1.(0|1) 400/', $error['message']))
            return false;
    }

    /* Do md5 request with context */
    if (($v = http_getContents(array_merge($contextParams, array('url'=> $file)))) !== false)
        return md5($v);

    /* Send default result */
    return false;
}

/**
 * Check if folder is in path
 * @param string $file
 * @param string $path
 * @return boolean result
 */
function file_isInPath($file='', $path='') {
    if (file_exists($file))
        return folder_isInPath($file, $path);
    return folder_isInPath(dirname($file).'/', $path);
}

/* private mime gathering methods */

/**
 * Return file mime from finfo method.
 * @param string $file
 * @return string
 * @private
 */
function _file_getMimeFromFinfo($file) {
    if (!class_exists('finfo'))
        return false;

    /* load finfo */
    $finfo = @new finfo(FILEINFO_MIME);
    if (!$finfo) return false;

    /* check result */
    $mime = $finfo->file($file);
    $mime = explode(';', $mime);

    /* return result */
    if ($mime[0] == '')
      return false;
    return $mime[0];
}

/**
 * Return file mime from content_mime_type method.
 * @param string $file
 * @return string
 * @private
 */
function _file_getMimeFromMimeContentType($file) {
    if (!function_exists('mime_content_type'))
        return false;
    $mime = mime_content_type($file);
    if ($mime == '')
        return false;
    return ''.$mime;
}

/**
 * Return file mime from file extension.
 * @param string $file
 * @param string $ext
 * @return string
 * @private
 */
function _file_getMimeFromExtension($file, $ext=null) {
    /* try to get mime from extension */
    if (!isset($ext) and preg_match('/.*\.([^\.]*)/', $file, $ext))
        $ext = $ext[1];

    /* get mime from extension */
    switch ($ext) {
        /* image */
        case 'gif':
            return 'image/gif';
        case 'jpg':
        case 'jpeg':
        case 'jpe':
            return 'image/jpeg';
        case 'png':
            return 'image/png';
        case 'jp2':
            return 'image/jp2';
        case 'tiff':
        case 'tif':
            return 'image/tiff';
        case 'bmp':
            return 'image/bmp';
        case 'pct':
        case 'pic':
        case 'pict':
            return 'image/pict';
        /* audio */
        case 'aif':
        case 'aiff':
        case 'aifc':
            return 'audio/aiff';
        case 'm2a':
        case 'mp3':
        case 'mpa':
            return 'audio/mpeg';
        case 'mid':
        case 'midi':
            return 'audio/midi';
        case 'ra':
        case 'ram':
        case 'rm':
        case 'rmm':
        case 'rmp':
            return 'audio/x-realaudio';
        case 'wav':
            return 'audio/wav';
        /* text */
        case 'css':
            return 'text/css';
        case 'htm':
        case 'html':
        case 'htmls':
        case 'shtml':
            return 'text/html';
        case 'rt':
        case 'rtf':
        case 'rtx':
            return 'text/richtext';
        case 'sgm':
        case 'sgml':
            return 'text/sgml';
        case 'txt':
        case 'text':
            return 'text/plain';
        /* video */
        case 'asf':
            return 'video/x-ms-asf';
        case 'avi':
            return 'video/avi';
        case 'dv':
            return 'video/x-dv';
        case 'm1v':
        case 'm2v':
        case 'mp2':
        case 'mpg':
        case 'mpeg':
        case 'mpe':
            return 'video/mpeg';
        case 'mjpg':
            return 'video/x-motion-jpeg';
        case 'moov':
        case 'mov':
            return 'video/quicktime';
        /* compressed */
        case 'ace':
            return 'application/x-ace-compressed';
        case 'bz':
            return 'application/x-bzip';
        case 'bz2':
            return 'application/x-bzip2';
        case 'cpt':
            return 'application/x-compactpro';
        case 'gz':
        case 'gzip':
            return 'application/x-gzip';
        case 'hqx':
            return 'application/binhex';
        case 'rar':
            return 'application/x-rar-compressed';
        case 'sit':
        case 'sitx':
            return 'application/x-stuffit';
        case 'tar':
            return 'application/x-tar';
        case 'tgz':
            return 'application/gnutar';
        case 'z':
        case 'zip':
            return 'application/x-zip-compressed';
        /* source */
        case 'jav':
        case 'java':
            return 'text/x-java-source';
        case 'js':
            return 'application/x-javascript';
        case 'p':
            return 'text/x-pascal';
        case 'pas':
            return 'text/pascal';
        case 'pl':
            return 'text/x-script.perl';
        case 'py':
            return 'text/x-script.python';
        case 'pyc':
            return 'application/x-bytecode.python';
        case 'xml':
            return 'text/xml';
        /* disk image */
        case 'dmg':
            return 'application/x-apple-diskimage';
            /* application */
        case 'bin':
            return 'application/macbinary';
        case 'dcr':
        case 'dxr':
            return 'application/x-director';
        case 'doc':
        case 'dot':
        case 'word':
        case 'docx':
            return 'application/msword';
        case 'eps':
        case 'ps':
            return 'application/postscript';
        case 'latext':
            return 'application/x-latex';
        case 'pdf':
            return 'application/pdf';
        case 'pot':
        case 'ppa':
        case 'ppt':
        case 'pps':
        case 'ppz':
        case 'pwz':
        case 'pptx':
            return 'application/mspowerpoint';
        case 'swf':
            return 'application/x-shockwave-flash';
        case 'xl':
        case 'xla':
        case 'xlb':
        case 'xlc':
        case 'xld':
        case 'xlk':
        case 'xll':
        case 'xlm':
        case 'xls':
        case 'xlt':
        case 'xlv':
        case 'xlw':
        case 'xlwx':
            return 'application/msexcel';
        default:
            return 'application/octet-stream';
    }
    return '';
}


/* deprecated methods */

/**
 * @see file_getMimeIcon
 * @param string $mime
 * @param int $size
 * @return string
 * @deprecated Use file_getMimeIcon instead.
 */
function file_getFileIcon($mime='', $size=32) {
    return file_getMimeIcon($mime, $size);
}

/**
 * @see file_getPHPFileFooter
 * @return string
 * @deprecated Use file_getPHPFileFooter instead.
 */
function file_getPHPFileEnder() {
    return file_getPHPFileFooter();
}
?>
