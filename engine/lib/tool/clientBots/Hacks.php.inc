<?php
/**
 * @brief Hacks client bots specific methods
 * @details Engine / Tool Library
 * @file engine/lib/tool/clientBots/Hacks.php.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: May 2018
 * @date Modification: May 2018
 * @copyright 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @warning This library is not loaded with CaMykS initialisation.
 */

/**
 * Return given known web hack or hack list.
 * @return array
 * @private
 */
function _client_getKnownHacks() {
    $knownHacks = array();
    
    /* Joomla Exploit */
    $knownHacks['jdatabasedrivermysqli'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Joomla Exploit',
    );
    
    /* Joomla Exploit */
    $knownHacks['bot/0.1 (bot for jce)'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Joomla JCE Exploit',
    );
    
    /* Bash Exploit */
    $knownHacks['() { foo;};echo; /bin/bash'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Bash Exploit',
    );
    
    /* Bash Exploit */
    $knownHacks['() { :; }; echo'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Bash Exploit',
    );
    
    /* Bash Exploit */
    $knownHacks['() { :;};'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Bash Exploit',
    );
    
    /* Drupal Fckeditor exploit */
    $knownHacks['webfuck v2.1 t0phackteam www.t0p.xyz'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Drupal Fckeditor exploit',
    );
    
    /* betaBot : should be in bot list with a trustee level to "unwanted" */
    $knownHacks['betabot'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Unwanted bot',
    );
    
    /* PHP Exploit */
    $knownHacks['php system'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'PHP Exploit',
    );
    
    /* the beast malware */
    $knownHacks['the beast'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'the beast malware',
    );
    
    /* return list */
    return $knownHacks;
}
?>