<?php
/**
 * @brief Content_GoogleSearchResultsViewer module, site search results display sublayout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.1
 * @date Creation: Sep 2008
 * @date Modification: Jul 2021
 * @copyright 2008 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="cse-search-results"></div>
<script type="text/javascript">
    var googleSearchIframeName = "cse-search-results";
    var googleSearchFormName = "cse-search-box";
    var googleSearchFrameWidth = <?= $this->gsrItem->vars['sr_width']; ?>;
    var googleSearchDomain = "<?= $this->gsrItem->vars['sr_searchdomain']; ?>";
    var googleSearchPath = "/cse";
</script>
<script type="text/javascript" src="http://www.google.com/afsonline/show_afs_search.js"></script>
