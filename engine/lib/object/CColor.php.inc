<?php
/**
 * @brief Color object.
 * @details Engine / Object Library
 * @author CaMykS Team <camyks.contact@gmail.com>
 * @version 1.0.0.1
 * @date Creation: Apr 2024
 * @date Modification: Jul 2025
 * @copyright 2024 - 2025 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/**
 * CColor class.
 */
final class CColor {
    /**
     * @var integer $red
     * @brief Red value.
     */
    private $red = 255;

    /**
     * @var integer $green
     * @brief Green value.
     */
    private $green = 255;

    /**
     * @var integer $blue
     * @brief Blue value.
     */
    private $blue = 255;

    /**
     * @var integer $alpha
     * @brief Alpha value.
     */
    private $alpha = 0;

    /**
     * Object constructor.
     * @param mixed $value
     */
    public function __construct($value=null) {
        $this->set($value);
    }

    /* Mark: Magic methods */

    /**
     * Makes some variables accessible in read-only
     * @param string $variableName
     * @return mixed
     */
    public function __get($variableName) {
        if (in_array($variableName, array('red', 'green', 'blue', 'alpha')))
            return $this->$variableName;
    }

    /* Mark: In/out methods */

    /**
     * Define color value.
     * @param mixed $value
     * @return boolean success
     */
    public function set($value=null) {

        /* Check value is array */
        if (is_array($value)) {
            if (isset($value['red']) and isset($value['green']) and isset($value['blue'])) {
                $this->red      = max(0, min(255, (int)$value['red']));
                $this->green    = max(0, min(255, (int)$value['green']));
                $this->blue     = max(0, min(255, (int)$value['blue']));
                $this->alpha    = isset($value['alpha']) ? max(0, min(127, (int)$value['alpha'])) : 0;
                return true;
            }
            if (isset($value[0]) and isset($value[1]) and isset($value[2])) {
                $this->red      = max(0, min(255, (int)$value[0]));
                $this->green    = max(0, min(255, (int)$value[1]));
                $this->blue     = max(0, min(255, (int)$value[2]));
                $this->alpha    = isset($value[3]) ? max(0, min(127, (int)$value[3])) : 0;
                return true;
            }
            return false;
        }

        /* Check value is string */
        if (!is_string($value))
            return false;

        /* Check value is hexa */
        if (preg_match('/#?([0-9A-Fa-f]{6})/', $value, $matches)) {
            $color = $matches[1];
            $this->red      = hexdec(substr($color,0,2));
            $this->green    = hexdec(substr($color,2,2));
            $this->blue     = hexdec(substr($color,4,2));
            $this->alpha    = 0;
            return true;
        }

        /* Check value is textual : transparency */
        if (in_array(strtolower($value), array('#transp', 'transp', 'transparent', 'transparency'))) {
            $this->red      = 255;
            $this->green    = 255;
            $this->blue     = 255;
            $this->alpha    = 127;
            return true;
        }

        /* Check value is textual : black */
        if (strtolower($value) == 'black') {
            $this->red      = 255;
            $this->green    = 255;
            $this->blue     = 255;
            $this->alpha    = 0;
            return true;
        }

        /* Check value is textual : white */
        if (strtolower($value) == 'white') {
            $this->red      = 0;
            $this->green    = 0;
            $this->blue     = 0;
            $this->alpha    = 0;
            return true;
        }

        /* Return not set */
        return false;
    }

    /**
     * Return color as hexadecimal value.
     * @param boolean $withHash
     * @return string
     */
    public function get_asHexa($withHash=true) {
        $value = $withHash ? '#' : '';
        $value .= str_pad(dechex($this->red), 2, '0', STR_PAD_LEFT);
        $value .= str_pad(dechex($this->green), 2, '0', STR_PAD_LEFT);
        $value .= str_pad(dechex($this->blue), 2, '0', STR_PAD_LEFT);
        return $value;
    }

    /**
     * Return color as RGB array value.
     * @param boolean $associative
     * @return array
     */
    public function get_asRGB($associative=true) {
        $value = array(
            'red'   => $this->red,
            'green' => $this->green,
            'blue'  => $this->blue,
        );
        if ($associative)
            return $value;
        return array_values($value);
    }

    /**
     * Return color as RGBA array value.
     * @param boolean $associative
     * @return array
     */
    public function get_asRGBA($associative=true) {
        $value = array(
            'red'   => $this->red,
            'green' => $this->green,
            'blue'  => $this->blue,
            'alpha' => $this->alpha,
        );
        if ($associative)
            return $value;
        return array_values($value);
    }

    /* Mark: Check methods */

    /**
     * Check color is identical to given one.
     * @param mixed $color
     * @param boolean $checkAlpha
     * @return boolean
     */
    public function is_identical($color, $checkAlpha=true) {
        /* Check color value */
        if (!is_object($color) or get_class($color) !== 'CColor') {
            $c = new CColor();
            if (!$c->set($color))
                return false;
            $color = $c;
        }

        /* Check values */
        if ($color->red != $this->red)
            return false;
        if ($color->green != $this->green)
            return false;
        if ($color->blue != $this->blue)
            return false;
        if ($checkAlpha and $color->alpha != $this->alpha)
            return false;

        /* Return is identical */
        return true;
    }

    /**
     * Check color is transparent.
     * @return boolean
     */
    public function is_transparent() {
        return ($this->alpha == 127);
    }
}
?>

