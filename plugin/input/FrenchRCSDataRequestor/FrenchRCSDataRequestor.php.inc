<?php
/**
 * @brief FrenchRCSDataRequestor input.
 * @details Plugin / Input Engine
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Jun 2025
 * @date Modification: Jul 2025
 * @copyright 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * @note API Documentation page: https://recherche-entreprises.api.gouv.fr/docs/
 * @note ResponseFormat values:
 * - Brut : Long string with brut (json) request answer
 * - Data : Decoded request answer as array
 * - CAJaxRequest : CAJaxRequest object with decoded request answer as array in 'Response' variable
 */

/**
 * FrenchRCSDataRequestor Input class.
 */
final class FrenchRCSDataRequestor extends Input {
    /**
     * @var array $requestParams
     * @brief HTTP request parameters.
     */
    private $requestParams = array();

    /**
     * @var array $requestErrors
     * @brief List of request errors
     */
    private $requestErrors;

    /**
     * Class constructor.
     * @param string $path_type
     */
    public function __construct($path_type) {
        parent::__construct('FrenchRCSDataRequestor', $path_type);

        /* Override Plugin variables */
        $this->version = '1.0';
        $this->plugin_package = 'Generic';

        /* Define plugin author */
        $this->author_name = 'CaMykS Team';
        $this->author_mail = 'camyks.contact@gmail.com';
        $this->author_group = 'camyks.net';

        /* Define request errors */
        $this->requestErrors = array(
            0 => 'Unknown error.',

            /* Request errors */
            1 => 'Unknown request action.',
            2 => 'Invalid request parameters.',
            3 => 'Service unavailable or request refused.',

            /* Response errors */
            11 => 'Empty response.',
            12 => 'Invalid JSON format',
        );
    }

    /* Mark: Override input methods */

    /**
     * Initialise input.
     * @param array $params
     * @return void
     */
    public function initialise($params=array()) {
        global $camyks;

        /* Set up request params */
        $defaultParams = array('IgnoreErrors'=>true, 'TimeOut'=>10, 'SSL'=>true, 'UserAgent'=>$camyks->get_confValue('UserAgent'), 'ResponseFormat'=>'Brut');
        $this->requestParams = array_merge($defaultParams, $params);

        /* Input generic initialization */
        parent::initialise();
    }

    /* Mark: Main action method */

    /**
     * Perform a request.
     * @param string $type
     * @param array $params
     * @return string
     */
    public function request($type, $params=array()) {
        switch ($type) {
            case 'text_search': return $this->request_textSearch($params);
            /* case 'loc_search': case 'near_point': return $this->request_locSearch($params);*/
            default: return $this->build_errorResponse(1);
        }
    }

    /**
     * Perform a textual search request.
     * @param array $params
     * @return string
     */
    private function request_textSearch($params) {
        /* Merge parameters */
        $defaultParams = array(
            'q' => '',
            'activite_principale' => '',
            'categorie_entreprise' => '',
            'code_collectivite_territoriale' => '',
            'convention_collective_renseignee' => '',
            'code_postal' => '',
            'code_commune' => '',
            'departement' => '',
            'region' => '',
            'epci' => '',
            'egapro_renseignee' => '',
            'est_achats_responsables' => '',
            'est_alim_confiance' => '',
            'est_association' => '',
            'est_bio' => '',
            'est_collectivite_territoriale' => '',
            'est_entrepreneur_individuel' => '',
            'est_entrepreneur_spectacle' => '',
            'est_ess' => '',
            'est_finess' => '',
            'est_organisme_formation' => '',
            'est_patrimoine_vivant' => '',
            'est_qualiopi' => '',
            'est_rge' => '',
            'est_siae' => '',
            'est_service_public' => '',
            'est_l100_3' => '',
            'est_societe_mission' => '',
            'est_uai' => '',
            'etat_administratif' => '',
            'id_convention_collective' => '',
            'id_finess' => '',
            'id_rge' => '',
            'id_uai' => '',
            'nature_juridique' => '',
            'section_activite_principale' => '',
            'tranche_effectif_salarie' => '',
            'nom_personne' => '',
            'prenoms_personne' => '',
            'date_naissance_personne_min' => '',
            'date_naissance_personne_max' => '',
            'type_personne' => '',
            'ca_min' => '',
            'ca_max' => '',
            'resultat_net_min' => '',
            'resultat_net_max' => '',
            'limite_matching_etablissements' => '',
            'minimal' => '',
            'include' => '',
            'page' => '',
            'per_page' => '',
        );
        $params = array_merge($defaultParams, $params);

        /* Check parameters */
        array_walk($params, 'trim');
        if ($params['q'] == '')
            return $this->build_errorResponse(2);

        /* Prepare request context */
        $opts = array(
            'http' => array(
                'method'  => 'GET',
                'header'  => "Content-Type: application/json\r\n".
                             "Accept: application/json\r\n",
                'user_agent' => $this->requestParams['UserAgent'],
                'ignore_errors' => $this->requestParams['IgnoreErrors'],
                'timeout' =>  $this->requestParams['TimeOut'],
            ),
        );
        if ($this->requestParams['TimeOut'] == false) {
            $opts['ssl'] = array(
                'verify_peer' => false,
                'verify_peer_name' => false,
            );
        }
        $context  = stream_context_create($opts);

        /* Build request */
        $request = 'https://recherche-entreprises.api.gouv.fr/search?';
        $p = array();
        foreach ($params as $name => $value) {
            if ($value != '')
                $p[] = $name.'='.urlencode($value);
        }
        $request .= implode('&', $p);

        /* Perform request */
        $result = file_get_contents($request, false, $context);

        /* Check response headers */
        if ($http_response_header[0] == 'HTTP/1.1 200 OK')
            return $this->build_resultResponse($result);

        /* Return result */
        return $this->build_errorResponse(3);
    }

    /* Mark: Private tool methods */

    /**
     * Build result answer.
     * @param string $result
     * @return mixed
     */
    private function build_resultResponse($result) {
        /* Check for brut */
        if (!in_array($this->requestParams['ResponseFormat'], array('CAJaxRequest', 'Data')))
            return $result;

        /* Check JSON */
        if (strlen($result) < 4)
            $this->build_errorResponse(11);

        $data = json_decode($result, true);
        if (!(json_last_error() == JSON_ERROR_NONE and is_array($data)))
            $this->build_errorResponse(12);

        /* Check for Data response */
        if ($this->requestParams['ResponseFormat'] == 'Data')
            return $data;

        /* Check for CAJaxRequest response */
        if ($this->requestParams['ResponseFormat'] == 'CAJaxRequest') {
            $response = new CAJaxRequest();
            $response->set_asSuccess();
            $response->update_param('Response', $data);
            return $response;
        }
    }

    /**
     * Build error response.
     * @param int $errorId
     * @return mixed
     */
    private function build_errorResponse($errorId) {
        /* Check errorId */
        if (!isset($this->requestErrors[$errorId]))
            $errorId = 0;

        /* Check for CAJaxRequest response */
        if ($this->requestParams['ResponseFormat'] == 'CAJaxRequest') {
            $response = new CAJaxRequest();
            $response->set_asFailure('', $this->requestErrors[$errorId]);
            return $response;
        }

        /* Build response */
        $error = array('ErrorId'=>$errorId, 'ErrorMessage'=>$this->requestErrors[$errorId]);

        /* Check for Data response */
        if ($this->requestParams['ResponseFormat'] == 'Data')
            return $error;

        /* Return Brut response */
        return json_encode($error);
    }
}
?>
