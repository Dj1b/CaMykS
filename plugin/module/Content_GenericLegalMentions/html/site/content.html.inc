<?php
/**
 * @brief Content_GenericLegalMentions Module site content sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Jan 2020
 * @date Modification: Apr 2021
 * @copyright 2020 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

/* Check language to display */
$language = in_array($camyks->current_language, array('fr', 'en')) ? $camyks->current_language : 'en';

/* Display properties part */
$this->load_file('html/site/'.$language.'/properties.html.inc');

/* Display conditions part */
$this->load_file('html/site/'.$language.'/conditions.html.inc');

/* Display services part */
$this->load_file('html/site/'.$language.'/services.html.inc');

/* Display limitations part */
$this->load_file('html/site/'.$language.'/limitations.html.inc');

/* Display copyright part */
$this->load_file('html/site/'.$language.'/copyright.html.inc');

/* Display responsability part */
$this->load_file('html/site/'.$language.'/responsability.html.inc');

/* Display data part */
$this->load_file('html/site/'.$language.'/data.html.inc');

/* Display notifications part */
$this->load_file('html/site/'.$language.'/notifications.html.inc');

/* Display cookies part */
$this->load_file('html/site/'.$language.'/cookies.html.inc');

/* Display tags part */
$this->load_file('html/site/'.$language.'/tags.html.inc');

/* Display links part */
$this->load_file('html/site/'.$language.'/links.html.inc');

/* Display tags part */
$this->load_file('html/site/'.$language.'/law.html.inc');

/* Display additional part */
if ($this->contentItem->has_content('additional_content')) {
    echo $this->contentItem->vars['additional_content'];
    echo '<p class="eContent1">&nbsp;</p>';
}

/* Display definitions part */
$this->load_file('html/site/'.$language.'/definitions.html.inc');
?>
