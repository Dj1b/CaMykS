<?php
/*
 * CaMyks Engine
 * Developed by		: camyks.net
 * Author		: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version	: 1.0a
 * Object Version	: 1.0
 * Object Type	        : Plugin / Module Layout
 * Create Date	       	: Sep 2008
 * Last Modif Date	: Sep 2008
 * 
 * Content_GoogleSearchResultsViewer Module Site Layout : search results display
 */
?>
<div id="cse-search-results"></div>
<script type="text/javascript">
var googleSearchIframeName = "cse-search-results";
var googleSearchFormName = "cse-search-box";
var googleSearchFrameWidth = <?=$this->gsrItem->vars['sr_width']?>;
var googleSearchDomain = "<?=$this->gsrItem->vars['sr_searchdomain']?>";
var googleSearchPath = "/cse";
</script>
<script type="text/javascript" src="http://www.google.com/afsonline/show_afs_search.js"></script>
