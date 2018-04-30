<?php
/*
 * CaMykS Engine
 * Developed by	    : camyks.net
 * Author	       	  : CaMykS Team <camyks.contact@gmail.com>
 * CaMykS Version   : 1.0b
 * Object Version   : 1.0
 * Object Type      : Plugin / Input Layout
 * Create Date		  : Apr 2010
 * Last Modif Date	: Apr 2010
 * 
 * PerpetualCalendar layout
 */
/**
 * @cond Exclude
 */
$cnt = 0;
$line = 0;

$refDay = mktime(0, 0, 0, 4, 25, 2010);
$difDay = 24*60*60;

if ($this->params['enableHighlight']==1) {
  $over = 'this.className=\'cell%sOver\';';
  $out = 'this.className=\'cell%s\';';
 } else {
  $over = '';
  $out = '';
 }
?>
<table cellspacing="<?=$this->params['styleCellspacing'];?>" cellpadding="0" class="perpetualCalendar">
<tbody id="<?=$this->params['name']?>Object">
<tr>
  <td class="cellLink">
    <?=$this->get_buttonDisplay('left', $this->params['prevMonthLink']);?>
  </td>
  
  <td colspan="5" class="cellDate" id="<?=$this->params['name']?>Date"><?=ucfirst(strftime('%B %Y', $this->calendarFirstDay)); ?></td>
  
  <td class="cellLink">
    <?=$this->get_buttonDisplay('right', $this->params['nextMonthLink']);?>
  </td>
</tr>

<tr>
  <?php for($i=0; $i<7; $i++) : ?>
  <td class="cellDay"><?=strtoupper(substr(strftime('%a', $refDay+($i*$difDay)),0 , 1));?></td>
  <?php endfor; ?>
</tr>

<?php if (date('w', $this->calendarFirstDay) > 0 ) : ?>   
<tr id="<?=$this->params['name']?>Line<?=$line++?>">
<?php for ( $i=0; $i<date('w', $this->calendarFirstDay); $i++ ) : ?>
<td class="cellOut"> &nbsp; </td>
<?php $cnt++; ?>
<?php endfor; ?>
<?php endif; ?>

<?php for ( $day=1; $day<=date('j', $this->calendarLastDay); $day++ ) : ?>
<?php if ( $cnt == 0 ) : ?>
<tr id="<?=$this->params['name']?>Line<?=$line++?>">
<?php endif; ?>

<?php if (isset($this->displayedItems[$day])) : ?>
	<?php if (count($this->displayedItems[$day]) > 1 and $this->params['multiItem']['enabled'] == 1) : ?>
		<?php $item = $this->params['multiItem']; ?>
	<?php else : ?>
  	<?php $item = $this->params['items'][$this->displayedItems[$day][0]]; ?>
  <?php endif; ?>
<?php else : ?>
  <?php $item = $this->params['defaultItem']; ?>
<?php endif; ?>
  
<td id="<?=$this->params['name'].'Cell'.$day;?>" class="cell<?=$item['class'];?>"
<?php if (!isset($item['hadEvents']) or $item['hadEvents'] == 1) : ?>

  <?php if (isset($item['overEvent']) and $item['overEvent'] != '') : ?>
    onmouseover="<?=vsprintf($over, $item['class']).$item['overEvent'].'('.$day.');';?>"
  <?php elseif ($this->params['defaultEvents']['overEvent'] != '') : ?>
    onmouseover="<?=vsprintf($over, $item['class']).$this->params['defaultEvents']['overEvent'].'('.$day.');';?>"
  <?php endif;?>

  <?php if (isset($item['outEvent']) and $item['outEvent'] != '') : ?>
    onmouseout="<?=vsprintf($out, $item['class']).$item['outEvent'].'('.$day.');';?>"
  <?php elseif ($this->params['defaultEvents']['outEvent']!= '') : ?>
    onmouseout="<?=vsprintf($out, $item['class']).$this->params['defaultEvents']['outEvent'].'('.$day.');';?>"
  <?php endif;?>

  <?php if (isset($item['clickEvent']) and $item['clickEvent'] != '') : ?>
    onclick="<?=$item['clickEvent'].'('.$day.');';?>"
  <?php elseif ($this->params['defaultEvents']['clickEvent'] != '') : ?>
    onclick="<?=$this->params['defaultEvents']['clickEvent'].'('.$day.');';?>"
  <?php endif;?>
<?php elseif ($this->params['selectionCallBack'] != '') : ?>
    onclick="<?=$this->params['selectionCallBack'].'('.$this->params['dateYear'].', '.$this->params['dateMonth'].', '.$day.');';?>"
<?php endif;?>><?=$day?></td>

<?php if ( ++$cnt == 7 ) : ?>
<?php $cnt = 0; ?>
</tr>
<?php endif; ?>
<?php endfor; ?>
  
<?php if ( $cnt > 0 ) : ?>
<?php for ( $i=$cnt; $i<7; $i++ ) : ?>
<td class="cellOut"> &nbsp; </td>
<?php endfor; ?>
</tr>
<?php endif; ?>
</tbody>
</table>
<?php 
/**
 * @endcond Exclude
 */
?>