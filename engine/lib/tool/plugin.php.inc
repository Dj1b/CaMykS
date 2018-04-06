<?php
/*
 * CaMyks Engine
 * Developed by     : camyks.net
 * Author           : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0
 * Object Version   : 1.0.1
 * Object Type      : Engine / Tool Library
 * Creation Date    : Jan 2008
 * Last Modif Date  : Apr 2018
 *
 * Plugins static methods
 */

/*
 * load a plugin
 * @param string $type
 * @param string $name
 * @param string $path_type
 * @return mixed
 */
function plugin_get($type, $name, $path_type='camyks') {
    global $camyks;
    /* build module path */
    $path = $camyks->get_pluginPath($path_type);
    $path .= '/'.$type.'/'.$name.'/'.$name.$camyks->file_extension;
    
    /* check if module file exists */
    if (file_exists($path)===true) {
        require_once ($path);
        /* check if class is correctly implemented */
        if (class_exists($name)) {
            /* load module */
            eval("\$plugin = new ".$name. "('".$path_type."');");
            return $plugin;
        }
    }
    return false;
}

/*
 * load complete plugin list
 * @param string $path
 * @param string $path_type
 * @return array
 */
function plugin_getList($path, $path_type) {
    global $camyks;
    $list = array();
    /* get modules path */
    $folders = folder_listFolders($path);  
    /* test all folder */
    foreach ($folders as $folder) {
        
        /* check Unix . & .. folders */
        if ($folder != "." or $folder != "..") {
        
            /* check if folder is really a folder */
            if (is_dir($path."/".$folder)) {
                
                /* check if plugin file exists */
                if (file_exists ($path ."/".$folder."/".$folder.$camyks->file_extension)) {
                    if (!class_exists($folder)) {
                        require_once ($path ."/".$folder."/".$folder.$camyks->file_extension);
                    }
                    
                    /* check if class is correctly implemented  */
                    if (class_exists($folder)) {
                        /* load plugin */
                        eval("\$plugin = new ".$folder. "('".$path_type."');");
                        eval("\$list['".$folder."'] = \$plugin;");
                    }
                }
            }
        }
    }
    return $list;
}

/*
 * check plugin updates
 * @return void
 */
function plugin_checkUpdates() {
    global $camyks;
    /* TO DO : find a way to disable update check */
    if (true) {
    
        /* check modules version and update */
        foreach($camyks->modules as $plugin) {
            if (version_compare($plugin->version, $plugin->_installedVersion) == 1)
                $plugin->update($plugin->_installedVersion);
        }
        
        /* check themes version and update */
        foreach($camyks->themes as $plugin) {
            if (version_compare($plugin->version, $plugin->_installedVersion) == 1)
                $plugin->update($plugin->_installedVersion);
        }
        
        /* check templates version and update */
        foreach($camyks->templates as $plugin) {
            if (version_compare($plugin->version, $plugin->_installedVersion) == 1)
                $plugin->update($plugin->_installedVersion);
        }
        
        /* check inputs version and update */
        foreach($camyks->inputs as $plugin) {
            if (version_compare($plugin->version, $plugin->_installedVersion) == 1)
                $plugin->update($plugin->_installedVersion);
        }
    }
}
?>