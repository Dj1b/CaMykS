<?php
/**
 * @brief Hacks client bots specific methods
 * @details Engine / Tool Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.9
 * @date Creation: May 2018
 * @date Modification: Dec 2021
 * @copyright 2018 - 2021 CaMykS Team
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

    /* Bash Exploit */
    $knownHacks['/usr/bin'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Unknown hack',
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

    /* PHP Exploit */
    $knownHacks['<'.'?'.'php'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'PHP Exploit',
    );

    /* PHP Exploit */
    $knownHacks['<'.'?'.'='] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'PHP Exploit',
    );

    /* PHP Exploit */
    $knownHacks['{${'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'PHP Exploit',
    );

    /* PHP Exploit */
    $knownHacks['print('] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'PHP Exploit',
    );

    /* the beast malware */
    $knownHacks['the beast'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'the beast malware',
    );

    /* ua/url exploit  */
    $knownHacks['("*'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'UA/URL Exploit',
    );

    /* xss attack */
    $knownHacks['<script'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'XSS Exploit',
    );

    /* Nuclei vulnerability hack */
    $knownHacks['nuclei (@'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Nuclei vulnerability hack',
    );

    /* Log4j exploit */
    $knownHacks['ldap://'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Log4j Exploit',
    );

    /* unknown hack */
    $knownHacks['ua.tools.random'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Unknown hack',
    );

    /* unknown hack */
    $knownHacks['idbte4m code87'] = array(
        'platform_type' => 'hack',
        'hack_info'     => 'Unknown hack',
    );

    /* return list */
    return $knownHacks;
}
?>
