<?php
/**
 * @brief Admin_SecurityTools Module admin help file for backup
 * @details Plugin / Module Help Layout
 * @file plugin/module/Admin_SecurityTools/help/fr/backup.html.inc
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
  Sauvegarde
</h2>

<p class="eContent1"> 
  Cet outil permet de g&eacute;n&eacute;rer automatiquement ou manuellement des sauvegardes du site. <br/>
</p>

<p class="eContent1">
  &nbsp;
</p>

<h3 class="eTitle3">
  Sauvegardes automatiques
</h3>

<p class="eContent1">
  Il est possible de programmer des sauvegardes automatiques pour votre site. Mensuelle, hebdomadaire, ou journali&egrave;re, vous pourrez r&eacute;gler la fr&eacute;quence des sauvegardes selon la fr&eacute;quentation et l'utilisation de votre site.
</p>

<p class="eContent1">
  Vous pourrez aussi cr&eacute;er des sauvegardes manuelles (avec des param&egrave;tres pouvant diff&eacute;rer des sauvegardes automatiques).
</p>

<p class="eContent1">
&nbsp;
</p>

<h3 class="eTitle3">
Param&egrave;tres
</h3>

<p class="eContent1">
  Hormis la fr&eacute;quence, vous pourrez param&eacute;trer le format de fichier de la sauvegarde. Actuellement, vous avez le choix entre les formats archive TAR, archive TAR compression GZ, archive TAR compression BZIP2 et archive ZIP.
</p>

<p class="eContent1">
  Vous pourrez d&eacute;cider des donn&eacute;es de votre site &agrave; sauvegarder. Il y a 3 possibilit&eacute;s:
</p>

<ul>
  <li class="eContent1">
    <span class="eContent2">Complet :</span> g&eacute;n&eacute;re un dump de la database &agrave; la racine du site, et sauvegarde la totalit&eacute; du dossier du site (configuration, plugins et donn&eacute;es).
  </li>
  <li class="eContent1">
    <span class="eContent2">Donn&eacute;es :</span> g&eacute;n&eacute;re un dump de la database dans le dossier des donn&eacute;es du site et sauvegarde ce dossier.
  </li>
  <li class="eContent1">
    <span class="eContent2">Fichiers :</span> sauvegarde uniquement le dossier des donn&eacute;es du site.
  </li>
</ul>

<p class="eContent1">
  &nbsp;
</p>

<h3 class="eTitle3">
  S&eacute;curit&eacute;
</h3>
<p class="eContent1">
  Par s&eacute;curit&eacute;, le nom des fichiers de sauvegarde est semi-al&eacute;atoire. De plus ces fichiers ne sont accessibles qu'aux administrateurs habilit&eacute;s &agrave; manipuler les sauvegardes.
</p>

<p class="eContent1">
  Autre facteur de s&eacute;curit&eacute;, il convient de n'autoriser l'acc&egrave;s aux sauvegardes qu'aux administrateurs de confiance.
  En fait, en effectuant une sauvegarde compl&egrave;te les identifiants et mot de passes de la base de donn&eacute;es seront accessibles. 
  En effectuant, une sauvegarde compl&egrave;te ou des donn&eacute;es, la base de donn&eacute;es sera enti&eacute;rement disponible &agrave; la lecture.
</p>

<p class="eContent1">
  &nbsp;
</p>