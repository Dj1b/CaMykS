<?php
/**
 * @brief Admin_SecurityTools Module admin help file for IP Filter
 * @details Plugin / Module Help Layout
 * @file plugin/module/Admin_SecurityTools/help/fr/ipfilter.html.inc
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0
 * @date Creation: Nov 2007
 * @date Modification: Jun 2018
 * @copyright 2007 - 2018 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<h2 class="eTitle2">
  Filtre IP
</h2>

<p class="eContent1"> 
  Cet utilitaire vous permet de bannir une ou plusieurs adresse IP voir des groupes d'adresse IP.
</p>

<p class="eContent1">
  Bas&eacute; sur des r&egrave;gles, vous pourrez combiner les restrictions d'acc&egrave;s.
</p>

<p class="eContent1">
  &nbsp;
</p>

<h3 class="eTitle3">
  Les r&egrave;gles
</h3>

<p class="eContent1">
  Pour construire une r&egrave;gle, il y a 5 param&egrave;tres &agrave; renseigner :
</p>

<ul>
  <li class="eContent1">
    <span class="eContent2">l'adresse IP ou le groupe d'adresse IP :</span> Pour ins&eacute;rer une groupe d'IP, il suffit de remplacer un ou plusieurs octets par le caract&egrave;re &eacute;toile ( * ), par exemple : 192.168.*.* . <br />
    Pour l'instant le syst&egrave;me ne supporte que les IPv4.
  </li>
  <li class="eContent1">
    <span class="eContent2">l'activation :</span> Ce param&egrave;tre indique tout simplement si cette r&egrave;gle doit &ecirc;tre v&eacute;rifi&eacute;e lors du test de s&eacute;curit&eacute;.
  </li>
  <li class="eContent1">
    <span class="eContent2">le mode :</span> Ce param&egrave;tre vous permet de cibler la partie visiteur, la partie administrative ou indiff&eacute;rement les deux parties du site sur lequel la r&egrave;gle s'applique.
  </li>
  <li class="eContent1">
    <span class="eContent2">le type :</span> Ce param&egrave;tre est fondamental pour le bon fonctionnement de vos r&egrave;gles puisqu'il s'agit d'indique si la r&egrave;gle est une autorisation ou un refus.
  </li>
  <li class="eContent1">
    <span class="eContent2">le commentaire :</span> vous permet d'indiquer un texte court de commentaire &agrave; propos de cette r&egrave;gle.
  </li>
</ul>

<p class="eContent1">
  Par d&eacute;faut, sans aucune r&egrave;gle activ&eacute;e, toutes les adresses IP sont accept&eacute;es.
</p>

<p class="eContent1">
  La priorit&eacute; va aux autorisations. Si une m&ecirc;me adresse IP est simultan&eacute;ment dans une r&egrave;gle de refus et d'autorisation, elle sera accept&eacute;e. Cela permet de faire des r&egrave;gles simples qui refuserait tout une s&eacute;rie d'adresse IP tout en acceptant une bien particuli&egrave;re. Par exemple :
Vous pouvez refuser les adresses IP correspondent &agrave; 192.168.0.* mais accepter 192.168.0.1.
</p>

<p class="eContent1">
  <span class="error"> Attention : </span> Vous pouvez bannir votre propre adresse et donc vous refuser tout acc&egrave;s votre site.
</p>

<p class="eContent1">
  &nbsp;
</p>
