<?php
/**
 * @brief Folder specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/folder.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.5
 * @date Creation: Jul 2005
 * @date Modification: Dec 2019
 * @copyright 2005 - 2019 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * Create all folder from root folder needed to complete path.
 * @param string $path
 * @param string $root
 * @param string $rights
 * @return boolean
 */
function folder_createPath($path, $root, $rights=0771) {
    $folders = explode ('/', $path);
    while ($folders[0] == '') {
        array_shift($folders);
    }
    $folder = $root;
    foreach ($folders as $dir) {
        $folder .= '/'.$dir;
        if (is_file($folder) or $dir == '') {
            return false;
        } else if (!is_dir ($folder)) {
            if (!mkdir ($folder, $rights)) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Create all folder needed to complete path.
 * @param string $path
 * @param string $rights
 * @return boolean
 */
function folder_completePath($path, $rights=0771) {
    $folders = explode ('/', $path);
    while ($folders[0] == '') {
        array_shift($folders);
    }
    $folder = '';
    foreach ($folders as $dir) {
        if ($dir == '.')
             $folder = realpath('.');
        else
            $folder .= '/'.$dir;
        if (is_file($folder) or $dir == '') {
            return false;
        } else if (!is_dir($folder)) {
            if (!@mkdir ($folder, $rights)) {
                return false;
            }
        }
    }
    return true;
}

/*
 * Delete folder object.
 * @param string $folder
 * @param boolean $recursive
 * @return boolean
 */
function folder_delete($folder, $recursive=false) {
    if (file_exists($folder) and is_dir($folder) and folder_isInPath($folder)) {
        if ($dir = opendir($folder)) {
            $files = array();
            while (($file = readdir ($dir)) !== false) {
                if ($file != '.' and $file != '..') {
                    if ($recursive) {
                        if (is_dir($folder.'/'.$file)) {
                            if (folder_delete($folder.'/'.$file, $recursive) === false)
                                return false;
                        } else {
                            if (unlink($folder.'/'.$file) === false)
                                return false;
                        }
                    } else {
                        /* folder is not empty, and recursive is set to false */
                        return false;
                    }
                }
            }
        }
        return rmdir($folder);
    }
    return false;
}

/**
 * Copy a folder and its content to another location.
 * @param string $source
 * @param string $target
 * @return boolean
 */
function folder_copy($source, $target) {
    if (is_dir($source)) {
        @mkdir($target);
        $folder = dir($source);
        while (($item = $folder->read()) !== false) {
            if ($item == '.' || $item == '..') {
                continue;
            }
            $sourceitem = $source . '/' . $item;
            $targetitem = $target . '/' . $item;
            if (is_dir($sourceitem)) {
                folder_copy($sourceitem, $targetitem);
            } else {
                copy($sourceitem, $targetitem);
            }
        }
        $folder->close();
        return true;
    } else {
        return copy($source, $target);
    }
    return false;
}

/**
 * Move a source folder to a target one.
 * @param string $source the full source path
 * @param string $target the target folder path
 * @return boolean
 */
function folder_move($source, $target) {
    /* test if source and target exist and if target is writable */
    if (file_exists($source)
        and file_exists($target)
        and is_writable ($target)) {
        /* get file or folder item name */
        if (is_dir($source) or is_file($source)) {
            $name = basename($source);
        }  else {
            return false;
        }
        /* move folder */
        return rename($source , $target.'/'.$name);
    }
    return false;
}


/**
 * Return system temporary folder.
 * @return mixed
 */
function folder_getTemporaryFolder() {
    if (function_exists('sys_get_temp_dir')) {
        /* try to use default PHP function */
        return sys_get_temp_dir();
    } else {
        /* try to get folder path into environment vars */
        if (isset($_ENV['TMP'])) {
            return realpath($_ENV['TMP']);
        } else if (isset($_ENV['TEMP'])) {
            return realpath($_ENV['TEMP']);
        } else if (isset($_ENV['TMPDIR'])) {
            return realpath($_ENV['TMPDIR']);
        } else {
            /* to write a temp file and get its path */
            $tfile = tempnam(md5(uniqid(rand(), TRUE)), '');
            if ($tfile) {
                $tdir = realpath(dirname($tfile));
                unlink($tfile);
                return $tdir;
            }
        }
    }
    return false;
}

/**
 * List files from a folder.
 * @param string $folder
 * @param boolean $recursive
 * @param array $excluded_folders
 * @param array $excluded_files
 * @param string $subFolder
 * @return array
 */
function folder_listFiles($folder, $recursive=false, $excluded_folders=array(), $excluded_files=array(), $subFolder='') {
    $folderPath = $folder.($subFolder != '' ? '/'.$subFolder:'');

    /* check given path is a folder */
    if (!is_dir($folderPath))
        return array();

    /* start listing folders */
    if ($dir = opendir($folderPath)) {
        $files = array();
        while (($item = readdir($dir)) !== false) {

            $itemPath = ($subFolder != '' ? $subFolder.'/':'').$item;

            if (is_dir($folderPath.'/'.$item)) {
                if (in_array($item, array('.', '..')))
                    continue;
                if ($recursive !== true)
                    continue;
                if (in_array($item, $excluded_folders))
                    continue;
                $files = array_merge($files, folder_listFiles($folder, $recursive, $excluded_folders, $excluded_files, $itemPath));
            } elseif (is_file($folderPath.'/'.$item)) {
                if (in_array($item, $excluded_files))
                    continue;
                $files[] = $itemPath;
            }
        }
        return $files;
    }
    return array();
}

/**
 * Return folder list inside a given folder.
 * @param string $folder
 * @return array
 */
function folder_listFolders($folder) {
    /* check given path is a folder */
    if (!is_dir($folder)) {
        return array();
    }

    /* initialise result */
    $folders = array();

    /* load folder's elements */
    $elements = scandir($folder);

    /* sort them */
    sort($elements);

    /* keep all folders */
    foreach ($elements as $element) {
        if (($element != '.') and ($element != '..') and (is_dir($folder.'/'.$element)))
            $folders[] = $element;
    }

    /* send result */
    return $folders;
}

/**
 * Return folder list inside a given folder matching.
 * @param string $folder
 * @param array $matching_folders
 * @return array
 */
function folder_listMatchingFolders($folder, $matching_folders = array()) {
    /* check for matching folders */
    if (!is_array($matching_folders) or $matching_folders == array())
        return array();

    /* check for given folder */
    if (!is_dir($folder)) {
        return array();
    }

    /* initialise result */
    $folders = array();

    /* load folder's elements */
    $elements = scandir($folder);

    /* sort them */
    sort($elements);

    /* keep all folders */
    foreach ($elements as $element) {
        if (($element != '.') and ($element != '..') and (is_dir($folder.'/'.$element)) and (in_array($element, $matching_folders)))
            $folders[] = $element;
    }

    /* send result */
    return $folders;
}

/**
 * Count all files in given directory and sub directories.
 * @param string $path
 * @param boolean $recursive
 * @return integer
 */
function folder_countFiles($path, $recursive=true) {
    $cnt = 0;
    $dir = @opendir($path);
    if (!$dir)
        return 0;
    while (($file = readdir($dir)) !== false) {
        if ($file == '.' or $file == '..')
            continue;
        if (is_dir($path.'/'.$file)) {
            if ($recursive)
                $cnt += folder_countFiles($path.'/'.$file);
        } else {
            $cnt++;
        }
    }
    closedir($dir);
    return $cnt;
}

/**
 * Create a zip archive from given folder.
 * @param string $source
 * @param string $target
 * @param string $includeRootFolder
 * @return boolean success
 */
function folder_createZipArchive($source='', $target='',  $includeRootFolder=false) {
    /* check source is a folder */
    if (!is_dir($source))
        return false;

    /* create folder path */
    folder_completePath(dirname($target));

    /* initialize archive object */
    $zip = new ZipArchive();
    if (!$zip->open($target, ZipArchive::CREATE))
        return false;

    /* get real path for our folder */
    if ($includeRootFolder) {
        $rootFolder = basename($source);
        $rootPath = substr($source, 0, -strlen($rootFolder));
        /* add root folder */
        $zip->addEmptyDir($rootFolder);
    } else {
        $rootFolder = '';
        $rootPath = $source.'/';
    }

    /* get files and folders as flat structure */
    $struct = folder_getFlatStructure($source);

    /* add files and folders to the zip file */
    foreach ($struct as $item) {
        $itemPath = substr ($item['path'], strlen($rootPath));

        if ($item['type'] == 'folder') {
            /* add folder */
            //$zip->addEmptyDir($itemPath);
        } elseif ($item['type'] == 'file') {
            /* add file */
            $content = file_get_contents($item['path']);
            $zip->addFromString($itemPath, $content);
        }
    }

    /* Zip archive will be created only after closing object */
    return $zip->close();
}

/**
 * Return flat file structure of given folder.
 * @param string $source
 * @return array
 */
function folder_getFlatStructure($source='') {
    $struct = array();

    if (!is_dir($source))
        return $struct;

    $folder = dir($source);
    while (($item = $folder->read()) !== false) {
        if ($item == '.' || $item == '..') {
            continue;
        }

        $fitem = $source.'/'.$item;

        if (is_dir($fitem)) {
            $struct[] = array('type'=>'folder', 'path'=> $fitem);
            $struct = array_merge($struct, folder_getFlatStructure($fitem));
        } else {
            $struct[] = array('type'=>'file', 'path'=> $fitem);
        }
    }
    return $struct;
}

/**
 * Check if folder is in path.
 * @param string $folder
 * @param string $path
 * @return boolean result
 */
function folder_isInPath($folder='', $path='') {
    global $camyks;

    if (!is_dir($path) or $path == '')
        $path = $camyks->site_path;
    $path = realpath($path).'/';

    if (!file_exists($folder))
        return false;
    $folder = realpath($folder).'/';

    return preg_match('#^'.$path.'#', $folder);
}

/**
 * Return folder size.
 * @param string $folder
 * @param boolean $humanReadable
 * @return string
 */
function folder_getSize($folder, $humanReadable=false) {
    /* Initialise folder size */
    $s = 0;

    /* Recursively get size of all files */
    $path = realpath($folder);
    if ($path !== false && $path != '' && file_exists($path)){
        foreach(new RecursiveIteratorIterator(new RecursiveDirectoryIterator($path, FilesystemIterator::SKIP_DOTS)) as $object){
            $s += $object->getSize();
        }
    }

    /* Check for human readable result */
    if (!$humanReadable)
        return $s;
    return file_getFileSize($s);
}

?>
