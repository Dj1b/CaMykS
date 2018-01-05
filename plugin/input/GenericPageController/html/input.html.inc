<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	: CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Creation Date	: Jan 2010
 * Last Modif Date	: Jan 2010
 * 
 * GenericPageController layout
*/
global $camyks;

if ($camyks->get_confValue('html_version') == 5) {
  $tableStyles = 'style="border-spacing: 0; border-collapse: collapse; border:0;"';
} else {
  $tableStyles = 'cellspacing="0" cellpadding="0" style="border:0;"';
}
?>
<?php if ( $this->params['hideEmpty'] == 1 ) : ?>

<div class="genericPageEmptyController">
&nbsp;
</div>

<?php else : ?>

<div class="genericPageController">
  <table <?=$tableStyles?> class="gpcBox">
    <tr>
      <?php if ( $this->params['buttonSource'] != 'none' ) : ?>
      <td class="gpcButton">
        <?php if ( ($l=$this->get_previousPageURL()) == '' ) : ?>
          <img src="<?=$this->get_buttonURL('pager_off')?>" alt="<?=$this->get_translation('isfirstpage');?>" style="border:0;" />
        <?php else : ?>
          <a href="<?=$l;?>" style="font-size:0;">
            <img src="<?=$this->get_buttonURL('pager_left')?>" alt="<?=$this->get_translation('gotopreviouspage');?>" style="border:0;"
              onmouseover="this.src='<?=$this->get_buttonURL('pager_left_r')?>';"
              onmouseout="this.src='<?=$this->get_buttonURL('pager_left')?>';" />
          </a>
        <?php endif; ?>
      </td>
      <?php endif; ?>

      <?php if ( $this->params['pageCount'] <= 5 ) : ?>
        <?php for ( $i=0; $i<$this->params['pageCount']; $i++ ) : ?>
          <td class="gpc<?=($i == $this->params['pageCount']-1 ) ? 'R' : '' ?>Page">
            <a href="<?=$this->get_pageURL($i);?>" class="gpc<?=( $this->params['pageCurrent'] == $i ? 'Selected':'Link')?>">
              <?=($i+1)?>
            </a>
          </td>
        <?php endfor; ?>
      <?php elseif ( $this->params['pageCurrent'] < 3 ) : ?>
        <?php for ( $i=0; $i<4; $i++ ) : ?>
          <td class="gpcLPage">
            <a href="<?=$this->get_pageURL($i);?>" class="gpc<?=( $this->params['pageCurrent'] == $i ? 'Selected':'Link')?>">
              <?=($i+1)?>
            </a>
          </td>
        <?php endfor; ?>
        <td class="gpcSpacer">
          ...
        </td>
        <td class="gpcRPage">
          <a href="<?=$this->get_pageURL($this->params['pageCount']-1);?>" class="gpcLink">
            <?=$this->params['pageCount']?>
          </a>
        </td>
      <?php elseif ( $this->params['pageCurrent'] >= $this->params['pageCount'] - 3 ) : ?>
        <td class="gpcPage">
          <a href="<?=$this->get_pageURL(0);?>" class="gpcLink">
            1
          </a>
        </td>
        <td class="gpcSpacer">
          ...
        </td>
        <?php for ( $i=$this->params['pageCount']-4; $i<$this->params['pageCount']-1; $i++ ) : ?>
          <td class="gpcPage">
            <a href="<?=$this->get_pageURL($i);?>" class="gpc<?=( $this->params['pageCurrent'] == $i ? 'Selected':'Link')?>">
              <?=($i+1)?>
            </a>
          </td>
        <?php endfor; ?>
	<td class="gpcRPage">
          <a href="<?=$this->get_pageURL($this->params['pageCount']-1);?>" class="gpc<?=( $this->params['pageCurrent'] == $this->params['pageCount']-1 ? 'Selected':'Link')?>">
    <?=$this->params['pageCount'];?>
          </a>
        </td>
      <?php else : ?>
        <td class="gpcPage">
          <a href="<?=$this->get_pageURL(0);?>" class="gpcLink">
            1
          </a>
        </td>
        <td class="gpcLPage">
          ...
        </td>
        <?php for ( $i=$this->params['pageCurrent']-1; $i<$this->params['pageCurrent']; $i++ ) : ?>
          <td class="gpcPage">
            <a href="<?=$this->get_pageURL($i);?>" class="gpcLink">
              <?=($i+1)?>
            </a>
          </td>
        <?php endfor; ?>
        <td class="gpcPage" >
          <a href="<?=$this->get_pageURL($this->params['pageCurrent']);?>" class="gpcSelected">
            <?=($this->params['pageCurrent']+1)?>
          </a>
        </td>
        <?php for ( $i=$this->params['pageCurrent']+1; $i<$this->params['pageCurrent']+2; $i++ ) : ?>
          <td class="gpcPage">
            <a href="<?=$this->get_pageURL($i);?>" class="gpcLink">
              <?=($i+1)?>
            </a>
          </td>
        <?php endfor; ?>
        <td class="gpcSpacer">
          ...
        </td>
        <td class="gpcRPage">
          <a href="<?=$this->get_pageURL($this->params['pageCount']-1);?>" class="gpcLink">
            <?=$this->params['pageCount']?>
          </a>
        </td>
      <?php endif; ?>
    
      <?php if ( $this->params['buttonSource'] != 'none' ) : ?>
      <td class="gpcButton">
        <?php if ( ($l = $this->get_nextPageURL()) == '' ) : ?>
          <img src="<?=$this->get_buttonURL('pager_off')?>" alt="<?=$this->get_translation('islastpage');?>" style="border:0;" />
        <?php else : ?>
          <a href="<?=$l;?>" style="font-size:0;">
            <img src="<?=$this->get_buttonURL('pager_right')?>" alt="<?=$this->get_translation('gotonextpage');?>" style="border:0;"
              onmouseover="this.src='<?=$this->get_buttonURL('pager_right_r')?>';"
              onmouseout="this.src='<?=$this->get_buttonURL('pager_right')?>';" />
          </a>
        <?php endif; ?>
      </td>
      <?php endif; ?>
    </tr>
  </table>
</div>
<?php endif; ?>