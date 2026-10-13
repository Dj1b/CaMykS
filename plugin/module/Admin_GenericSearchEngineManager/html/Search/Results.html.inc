<?php
/**
 * @brief Admin_GenericSearchEngineManager module, admin search result sub layout.
 * @details Plugin / Module Layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Sep 2026
 * @date Modification: Sep 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
global $camyks;

$query = $this->get_searchQuery();
if ($query['search'] == '')
    return;
$results = $this->get_searchResultData(0, 10);
$count = $this->get_searchResultCount();
?>
<div class="eTitle2">
    <?php if ($count == 0) : ?>
        <?= $this->get_translation('search_noresult'); ?>
    <?php elseif ($count == 1) : ?>
        <?= $this->get_translation('search_1result'); ?>
    <?php else : ?>
        <?= $this->get_translation('search_xresults', $count); ?>
    <?php endif; ?>
</div>

<div>
    <?php $alt = 0; ?>
    <?php foreach ($results as $result) : ?>
        <div class="eTableLine<?=$alt; ?>">
            <div>
                &nbsp;
            </div>
            <div class="eContent4">
                [<?= $result['type']; ?>] <?= $result['title']; ?>
            </div>
            <div class="eContent1">
                <?= $result['description']; ?>
            </div>
            <ul>
                <li>
                    [<?= $result['linkType']; ?>] <?= $result['linkURL']; ?>
                </li>
            </ul>
            <div>
                &nbsp;
            </div>
        </div>
        <?php $alt = abs($alt-1); ?>
    <?php endforeach; ?>
</div>
