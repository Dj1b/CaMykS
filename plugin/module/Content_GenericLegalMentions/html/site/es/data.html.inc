<?php
/**
 * @brief Content_GenericLegalMentions module, site data, spanish sub layout.
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
<div id="LM-Data" class="anchor" title="7. Gestión de los datos personales"></div>

<h2 class="eTitle2">
    7. Gestión de los datos personales
</h2>

<p class="eContent1">
    Se informa al <span class="eContent2">Internauta</span> de las normas relativas a las comunicaciones comerciales, de la ley francesa de 21 de junio de 2014 sobre la confianza en la economía digital, de la Ley francesa de Informática y Libertades de 6 de agosto de 2004 y del Reglamento General de Protección de Datos (RGPD: n.º 2016-679).
</p>

<h3 class="eTitle3">
    7.1 Responsables de la recogida de datos personales
</h3>

<p class="eContent1">
    En relación con los <span class="eContent2">Datos Personales</span> recogidos durante el uso y la navegación por el <span class="eContent2">Sitio</span>, el responsable del tratamiento de los <span class="eContent2">Datos Personales</span> es <?= $this->contentItem->get_editorFullName(); ?>.
</p>

<p class="eContent1">
<?= $this->contentItem->vars['owner_name']; ?> está representado por <a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1"><?= $this->contentItem->vars['owner_managername']; ?></a><?php if (!$this->contentItem->is_individual()) : ?>, su representante legal<?php endif; ?>.
</p>

<p class="eContent1">
    Como responsable del tratamiento de los datos recogidos por el <span class="eContent2">Sitio</span>, <?= $this->contentItem->get_editorFullName(); ?> se compromete a respetar el marco legal vigente. Corresponde, en particular, al <span class="eContent2">Cliente</span> determinar las finalidades de sus tratamientos de datos, informar de manera completa a sus clientes potenciales y clientes sobre el tratamiento de sus <span class="eContent2">Datos Personales</span> al recabar su consentimiento y mantener un registro de tratamientos conforme a la realidad. Siempre que <?= $this->contentItem->get_editorFullName(); ?> trate <span class="eContent2">Datos Personales</span>, <?= $this->contentItem->get_editorFullName(); ?> adoptará todas las medidas razonables para garantizar la exactitud y pertinencia de los <span class="eContent2">Datos Personales</span> en relación con las finalidades para las que <?= $this->contentItem->get_editorFullName(); ?> los trata.
</p>

<h3 class="eTitle3">
    7.2 Finalidades de los datos recogidos
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> podrá tratar la totalidad o parte de los datos:
</p>

<ul>
    <li class="eContent1">
        <strong>para mejorar la navegación por el</strong> <span class="eContent2">Sitio</span>
        <ul>
            <li><b>Datos recogidos</b>: datos de conexión y de uso</li>
            <li><b>Plazo de conservación de los datos</b>: máximo 12 meses.</li>
        </ul>
    </li>

    <li class="eContent1">
        <strong>para prevenir y combatir el fraude informático (spam, piratería informática, etc.)</strong>
        <ul>
            <li><b>Datos recogidos</b>: equipo informático utilizado (agente de usuario) para la navegación y dirección IP</li>
            <li><b>Plazo de conservación de los datos</b>: máximo 12 meses.</li>
        </ul>
    </li>

    <?php foreach ($this->extraData as $plugin) : ?>
        <?php foreach ($plugin as $pluginData) : ?>
        <?php foreach ($pluginData as $data) : ?>
            <li class="eContent1">
                <strong><?= $data['title']; ?></strong>
                <ul>
                    <?php if ($data['description'] != '') : ?>
                        <li> <?= $data['description']; ?> </li>
                    <?php endif; ?>
                    <?php if ($data['data'] != '') : ?>
                    <li>
                        <b>Datos recogidos</b>: <?= $data['data']; ?>
                    </li>
                    <?php endif; ?>
                    <li>
                        <b>Plazo de conservación de los datos</b>:
                        <?php if ($data['duration'] != '') : ?>
                            <?= $data['duration']; ?>
                        <?php else : ?>
                            Máximo 12 meses.
                        <?php endif; ?>
                    </li>
                </ul>
            </li>
        <?php endforeach; ?>
        <?php endforeach; ?>
    <?php endforeach; ?>
</ul>

<h3 class="eTitle3">
    7.3 Derechos de acceso, rectificación y oposición
</h3>

<p class="eContent1">
    De conformidad con la normativa europea vigente, los <span class="eContent2">Usuarios</span> del <span class="eContent2">Sitio</span> <?= $this->contentItem->get_websiteURL(); ?> disponen de los siguientes derechos:

</p>

<ul>
    <li class="eContent1">
        derecho de acceso (artículo 15 del RGPD) y rectificación (artículo 16 del RGPD), actualización y completado de los <span class="eContent2">Datos Personales</span> de los <span class="eContent2">Usuarios</span>; derecho al bloqueo o supresión de los datos personales de los <span class="eContent2">Usuarios</span> (artículo 17 del RGPD) cuando sean inexactos, incompletos, ambiguos u obsoletos, o cuando su recogida, uso, comunicación o conservación esté prohibida,
    </li>

    <li class="eContent1">
        derecho a retirar el consentimiento en cualquier momento (artículo 13-2c del RGPD),
    </li>

    <li class="eContent1">
        derecho a la limitación del tratamiento de los datos de los <span class="eContent2">Usuarios</span> (artículo 18 del RGPD),
    </li>

    <li class="eContent1">
        derecho de oposición al tratamiento de los datos de los <span class="eContent2">Usuarios</span> (artículo 21 del RGPD),
    </li>

    <li class="eContent1">
        derecho a la portabilidad de los datos facilitados por los <span class="eContent2">Usuarios</span> cuando sean objeto de tratamientos automatizados basados en su consentimiento o en un contrato (artículo 20 del RGPD),
    </li>

    <li class="eContent1">
        derecho a determinar el destino de los datos de los <span class="eContent2">Usuarios</span> tras su fallecimiento y a elegir a quién <?= $this->contentItem->get_editorFullName(); ?> deberá comunicar (o no) esos datos entre los terceros designados previamente por el Usuario,
    </li>

    <li class="eContent1">
        cuando <?= $this->contentItem->get_editorFullName(); ?> tenga conocimiento del fallecimiento de un <span class="eContent2">Usuario</span> y, a falta de instrucciones de este, <?= $this->contentItem->get_editorFullName(); ?> se compromete a destruir sus <span class="eContent2">Datos Personales</span>, salvo que su conservación sea necesaria como prueba o para cumplir una obligación legal.
    </li>
</ul>

<p class="eContent1">
    Si el <span class="eContent2">Usuario</span> desea saber cómo <?= $this->contentItem->get_editorFullName(); ?> utiliza sus <span class="eContent2">Datos Personales</span>, solicitar su rectificación u oponerse a su tratamiento, el <span class="eContent2">Usuario</span> puede ponerse en contacto con <?= $this->contentItem->get_editorFullName(); ?> por escrito en la siguiente dirección: <br />
<br />
<?php if (!$this->contentItem->is_individual()) : ?>
    <span class="eContent2"><?= $this->contentItem->vars['owner_name']; ?></span> <br />
<?php endif; ?>
<a href="<?= mail_encode($this->contentItem->vars['owner_manageremail']); ?>" class="eLink1">
<?= $this->contentItem->vars['owner_managername']; ?> (DPO)</a> <br />
<?php if ($this->contentItem->has_content('owner_address')) : ?>
<?= $this->contentItem->vars['owner_address']; ?> <br />
<?php endif; ?>
<br />
En tal caso, el <span class="eContent2">Usuario</span> deberá indicar los <span class="eContent2">Datos Personales</span> que desea que <?= $this->contentItem->get_editorFullName(); ?> corrija, actualice o suprima, identificándose de manera precisa mediante una copia de un documento de identidad (documento nacional de identidad o pasaporte).
</p>

<p class="eContent1">
    Las solicitudes de supresión de <span class="eContent2">Datos Personales</span> estarán sujetas a las obligaciones legales impuestas a <?= $this->contentItem->get_editorFullName(); ?>, en particular en materia de conservación o archivo de documentos. Por último, los <span class="eContent2">Usuarios</span> del <span class="eContent2">Sitio</span> <?= $this->contentItem->get_websiteURL(); ?> pueden presentar una reclamación ante las autoridades de control y, en particular, ante la <a href="https://www.cnil.fr/fr/plaintes" class="eLink1" target="_blank" rel="noopener noreferer">CNIL</a>.
</p>

<h3 class="eTitle3">
    7.4 No comunicación de los datos personales
</h3>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> se abstendrá de tratar, alojar o transferir la información recogida sobre sus <span class="eContent2">Clientes</span> a un país situado fuera de la Unión Europea o considerado «no adecuado» por la Comisión Europea sin informar previamente al <span class="eContent2">Cliente</span>. No obstante, <?= $this->contentItem->get_editorFullName(); ?> podrá elegir libremente a sus encargados técnicos y comerciales siempre que ofrezcan garantías suficientes conforme a los requisitos del Reglamento General de Protección de Datos (RGPD: n.º 2016-679).
</p>

<p class="eContent1">
    <?= ucfirst($this->contentItem->get_editorFullName()); ?> se compromete a adoptar todas las precauciones necesarias para proteger la seguridad de los <span class="eContent2">Datos Personales</span> y evitar, en particular, que se comuniquen a personas no autorizadas. No obstante, si <?= $this->contentItem->get_editorFullName(); ?> tiene conocimiento de un incidente que afecte a la integridad o confidencialidad de los <span class="eContent2">Datos Personales</span> del <span class="eContent2">Cliente</span>, deberá informar a este lo antes posible y comunicarle las medidas correctivas adoptadas. Por otra parte, <?= $this->contentItem->get_editorFullName(); ?> no recoge «datos sensibles».
</p>

<?php if (!$this->contentItem->is_individual()) : ?>
<p class="eContent1">
    Los <span class="eContent2">Datos Personales</span> del <span class="eContent2">Usuario</span> podrán ser tratados por filiales de <?= $this->contentItem->get_editorFullName(); ?> y por encargados del tratamiento (proveedores de servicios), exclusivamente para cumplir las finalidades de la presente política.
</p>

<p class="eContent1">
    Las personas que puedan acceder a los <span class="eContent2">Datos Personales</span> de los <span class="eContent2">Usuarios</span> de <?= $this->contentItem->get_websiteURL(); ?> son designadas bajo la exclusiva responsabilidad del responsable de <?= $this->contentItem->get_editorFullName(); ?>. Además, sus respectivas atribuciones pueden limitarse según las necesidades y las finalidades mencionadas anteriormente.
</p>
<?php endif; ?>

<p class="eContent1">
    &nbsp;
</p>
