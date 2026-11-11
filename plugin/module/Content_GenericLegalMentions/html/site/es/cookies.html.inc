<?php
/**
 * @brief Content_GenericLegalMentions module, site cookies, spanish sub layout.
 * @details Plugin / Module layout
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0
 * @date Creation: Nov 2026
 * @date Modification: Nov 2026
 * @copyright 2026 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
?>
<div id="LM-Cookies" class="anchor" title="9. Cookies."></div>

<h2 class="eTitle2">
    9. Cookies
</h2>

<p class="eContent1">
    Una «cookie» es un pequeño archivo de información enviado al navegador del <span class="eContent2">Usuario</span> y almacenado en el dispositivo del <span class="eContent2">Usuario</span> (por ejemplo, ordenador o teléfono inteligente). Este archivo contiene información como el nombre de dominio del <span class="eContent2">Usuario</span>, el proveedor de acceso a Internet del <span class="eContent2">Usuario</span>, el sistema operativo del <span class="eContent2">Usuario</span> y la fecha y hora de acceso. Las cookies no pueden, en ningún caso, dañar el dispositivo del Usuario.
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> puede tratar información del <span class="eContent2">Usuario</span> relativa a su visita al <span class="eContent2">Sitio</span>, como las páginas consultadas y las búsquedas realizadas. Esta información permite a <?= $this->contentItem->get_editorFullName(); ?> mejorar el contenido del <span class="eContent2">Sitio</span> y la navegación del <span class="eContent2">Usuario</span>.
</p>

<p class="eContent1">
    Dado que las cookies facilitan la navegación y/o la prestación de los servicios ofrecidos por el <span class="eContent2">Sitio</span>, el <span class="eContent2">Usuario</span> puede configurar su navegador para decidir si desea aceptarlas o no, de modo que se almacenen en su dispositivo o, por el contrario, se rechacen, ya sea sistemáticamente o según su emisor. El <span class="eContent2">Usuario</span> también puede configurar el navegador para que se le solicite aceptar o rechazar las cookies en cada caso, antes de que se almacenen en su dispositivo durante la visita del <span class="eContent2">Usuario</span>. <?= ucfirst($this->contentItem->get_editorFullName()); ?> informa al <span class="eContent2">Usuario</span> de que, en tal caso, es posible que no estén disponibles todas las funciones ofrecidas por el <span class="eContent2">Sitio</span>.
</p>

<p class="eContent1">
    Si el <span class="eContent2">Usuario</span> rechaza el almacenamiento de cookies en su dispositivo o navegador, o si el <span class="eContent2">Usuario</span> elimina las ya almacenadas, se informa al <span class="eContent2">Usuario</span> de que su navegación y experiencia en el <span class="eContent2">Sitio</span> pueden verse limitadas. Esto también podría suceder cuando <?= $this->contentItem->get_editorFullName(); ?> o alguno de sus proveedores no pueda reconocer, por motivos de compatibilidad técnica, el tipo de navegador utilizado por el dispositivo, la configuración de idioma y visualización o el país desde el que parece conectarse a Internet.
</p>

<p class="eContent1">
    En su caso, <?= $this->contentItem->get_editorFullName(); ?> declina toda responsabilidad por las consecuencias de un funcionamiento limitado del <span class="eContent2">Sitio</span> y de los servicios que <?= $this->contentItem->get_editorFullName(); ?> pudiera ofrecer, derivadas (i) del rechazo de las cookies por el Usuario o (ii) de la imposibilidad de que <?= $this->contentItem->get_editorFullName(); ?> almacene o consulte las cookies necesarias para su funcionamiento debido a las preferencias del <span class="eContent2">Usuario</span>. La configuración de cada navegador para gestionar las cookies y las preferencias del <span class="eContent2">Usuario</span> es diferente. Se describe en el menú de ayuda del navegador, donde el <span class="eContent2">Usuario</span> podrá consultar cómo modificar sus preferencias en materia de cookies.
</p>

<p class="eContent1">
En cualquier momento, el <span class="eContent2">Usuario</span> puede expresar y modificar sus preferencias en materia de cookies. <?= ucfirst($this->contentItem->get_editorFullName()); ?> también podrá recurrir a proveedores externos para que le ayuden a recopilar y tratar la información descrita en esta sección.
</p>

<p class="eContent1">
Estas cookies solo se instalan en sus dispositivos si usted da su consentimiento al continuar navegando por el <span class="eContent2">Sitio</span> web o la aplicación móvil de <?= $this->contentItem->get_editorFullName(); ?>. No obstante, el <span class="eContent2">Usuario</span> puede retirar en cualquier momento su consentimiento para que el <span class="eContent2">Sitio</span> instale este tipo de cookies.
</p>

<?php if ($this->cookieAgreementInput !== false) : ?>
<p class="eContent1">
Esta es la lista de servicios presentes en el <span class="eContent2">Sitio</span> que utilizan cookies:
</p>
<ul>
    <?php foreach($this->cookieAgreementInput->get_servicesList() as $service) : ?>
        <li class="eContent1">
            <span class="eContent2"><?= $service['title']; ?></span>
            <br /><?= $service['purpose']; ?>
            <?php if ($service['usage'] !== '') : ?>
                <br />Uso: <?= $service['usage']; ?>
            <?php endif; ?>
            <?php if ($service['duration'] !== '') : ?>
                <br />Duración: <?= $service['duration']; ?>
            <?php endif; ?>
            <?php if ($service['aboutURL'] != '') : ?>
                <br /><a href="<?= $service['aboutURL']; ?>" class="link" target="_blank" rel="noopener,noreferer,nofollow">Más información</a>
            <?php endif; ?>
        </li>
    <?php endforeach; ?>
</ul>

<p class="eContent1" style="text-align:center;">
    <?= $this->theme->get_button(array(
        'title' => 'Abrir el panel de gestión de cookies',
        'url'   => $this->cookieAgreementInput->get_cookieManagementPanelOpenLink(),
    )); ?>
</p>

<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>

