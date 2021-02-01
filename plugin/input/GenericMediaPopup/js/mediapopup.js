/**
 * @brief GenericMediaPopup Input scripts
 * @details Plugin / Input Javascripts
 * @file plugin/input/GenericMediaPopup/js/mediapopup.js
 * @author CaMykS Team
 * @version 1.0.3
 * @date Creation: Oct 2011
 * @date Modification: Jan 2021
 * @copyright 2011 - 2021 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

function MediaPopup(name) {
    this.name = name;
    this.params = {};
    this.locales = {};
    this.loaded = false;
    this.params['pictures'] = {};
    this.params['diaporama'] = new Array();

    /*
     * Add parameter
     * @param string name
     * @param mixed value
     * @return void
     * @access public
     */
    this.set_param = function(param, value, subvalue) {
        if (subvalue != undefined && this.params[param])
            this.params[param][value] = subvalue;
        else
            this.params[param] = value;
    };

    /*
     * return param value from name
     * @param mixed param
     * @return mixed
     * @access public
     */
    this.get_param = function(param, value) {
        if (value != undefined && (this.params[param][value] || this.params[param][value] === 0))
                return this.params[param][value];
        if (value == undefined && this.params[param] || this.params[param] === 0)
            return this.params[param]
        return false;
    };

    /*
     * set locale value
     * @param string name
     * @param string value
     * @return void
     * @access public
     */
    this.set_locale = function(name, value) {
        this.locales[name.toLowerCase()] = value;
    };

    /*
     * get locale value
     * @param string name
     * @return void
     * @access public
     */
    this.get_locale = function(name) {
        if (this.locales[name.toLowerCase()])
            return this.locales[name.toLowerCase()];
        return name;
    };

    /*
     * initialise object
     * @return void
     * @access public
     */
    this.initialise = function() {

        /* default values */
        this.set_param('isMobile', -1);

        /* check navigator type */
        this.set_param('navType',    navigator.appName.indexOf("Microsoft")==-1? 'real':'msie');

        /* define body dom element */
        this.set_param('body', document.getElementsByTagName('body')[0]);

        /* define current popup */
        this.set_param('currentPopup', false);

        /* prepare background dom element */
        this._build_popupBackground();

        /* check and add key events */
        if (this.get_param('enableKeyboard') == 1) {
            if (typeof document.onkeyup == 'function')
                var oku = document.onkeyup.toString() + '(event);';
            else
                var oku = '';
            eval('document.onkeyup = function(event) {'+oku+''+this.name+'.on_keyPressed(event);};');
        }

        /* load diaporama controls */
        if (this.get_param('diaporama').length > 0) {
            this._get_diaporamaButtonsSize();
        }

        /* finalise initialisation */
        this.loaded = true;

        if (this.get_param('loadMedia') !== false) {
            loadMedia = this.get_param('loadMedia');
            if (!loadMedia['media'])
                return;
            if (loadMedia['width'] && loadMedia['height'])
                this.open_media(loadMedia['media'], loadMedia['title'], loadMedia['width'], loadMedia['height']);
            else
                this.open_media(loadMedia['media'], loadMedia['title']);
        }
    };

    /*
     * open media popup
     * @param string file
     * @param string title
     * @return void
     * @access private
     */
    this.open_media = function(file, title, width, height) {

        /* check for directly open file in a new window */
        if (this.check_openInANewWindow(width)) {
            var win = window.open(file, '_blank');
            win.focus();
            return;
        }

        /* show popup background */
        this.show_popupBackground();

        /* build popup div */
        popup = document.createElement('div').cloneNode(true);

        popup.className = 'mediaPopup';
        popup.style.display = 'none';
        this.get_param('body').appendChild(popup);

        /* attach close button */
        if (this.get_param('pictures', 'closeButton') !== false)
            popup.appendChild(this._get_closeButton());

        /* attach previous and next button bar */
        if (this.get_param('diaporamaButtonsShift') !== false)
            popup.appendChild(this._get_controlButtonsBar());

        /* build media box */
        contentBox = document.createElement('div').cloneNode(true);
        this.set_param('contentBox', contentBox);
        popup.appendChild(contentBox);
        this.set_param('currentPopup', popup);

        fileExt = file.split('.').pop().toLowerCase();
        if (fileExt == 'flv' && swfobject) { // display FLV movie

            /* update height with controller height */
            height += this.get_param('flvControlerHeight');

            /* update container div size */
            contentBox.style.width = width+'px';
            contentBox.style.height = height+'px';

            /* create movie box */
            movieBox = document.createElement('div').cloneNode(true);
            movieBox.id = 'MediaPopupContentBox';
            contentBox.appendChild(movieBox);

            /* add flash player video to popup */
            f_vars = {refresh: parseInt(Math.random()*9999), movieURL:this.get_param('baseURL')+'/'+file, controlsURL: this.get_param('baseURL')+'/'+this.get_param('flashControlsURL'), movieWidth:width, movieHeight:height, controlerColor:'0x'+this.get_param('flvControlerColor'), controlerAlpha:this.get_param('flvControlerAlpha')};
            f_params = {allowScriptAccess:"always", menu:true, scale:'noscale', WMode:'Transparent', salign:'tl', align:'t', defer:'defer'};

            swfobject.embedSWF(this.get_param('flashMovieURL'), "MediaPopupContentBox", width, height, "9.0.0", false, f_vars, f_params);

                /* display popup div */
             this.show_popup('flash', width, height);

        } else if (fileExt == 'swf' && swfobject) {

            /* update container div size */
            contentBox.style.width = width+'px';
            contentBox.style.height = height+'px';

            /* create movie box */
            movieBox = document.createElement('div').cloneNode(true);
            contentBox.id = 'MediaPopupContentBox';
            contentBox.appendChild(movieBox);

            swfobject.embedSWF(file, "MediaPopupContentBox", width, height, "9.0.0", false);

            /* display popup div */
            this.show_popup('flash', width, height);

        } else if (file.match(/https?:\/\/(www\.)?youtu\.be\//) != null) { // display youtube video
            /* update container div size */
            contentBox.style.width = width+'px';
            contentBox.style.height = height+'px';

            /* add youtube iframe */
            contentBox.innerHTML = '<iframe width="'+width+'" height="'+height+'"'
                + ' src="https://www.youtube.com/embed/'+file.substring(file.lastIndexOf('/'))+'"'
                + ' frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>';

            /* display popup div */
            this.show_popup('youtube', width, height);

        } else if (file.indexOf('http://www.dailymotion.com/video/') == 0 || file.indexOf('http://dai.ly/') == 0) { // display dailymotion video
             /* update container div size */
            contentBox.style.width = width+'px';
            contentBox.style.height = height+'px';

            video = file.substring(file.lastIndexOf('/'));
            if (video.indexOf('_') > 0)
                video = video.substring(0, video.indexOf('_'));

            /* add dailymotion iframe */
            contentBox.innerHTML = '<iframe width="'+width+'" height="'+height+'"'
                + ' src="https://www.dailymotion.com/embed/video/'+video+'"></iframe>';

            /* display popup div */
             this.show_popup('youtube', width, height);

        } else if (fileExt == 'html' || fileExt == 'htm' || file.indexOf('url:') == 0)    {    // display HTML file

            if (file.indexOf('url:') == 0) {
                file = file.substring(4);
            }

            /* update container div size */
            contentBox.style.width = width+'px';
            contentBox.style.height = height+'px';

            /* add html frame to popup */
            if (this.get_param('navType') == 'real') {
                html = document.createElement('object').cloneNode(true);
                html.setAttribute('data', file);
                html.setAttribute('type', 'text/html');
                html.style.width = width+'px';
                html.style.height = height+'px';
            } else {
                html = document.createElement('iframe').cloneNode(true);
                html.setAttribute('src', file);
                html.setAttribute('frameBorder', 0);
                html.setAttribute('width', width);
                html.setAttribute('height', height);
            }
            contentBox.appendChild(html);

            /* display popup div */
            this.show_popup('html', width, height);
        } else if (file.substring(0, 8) == 'content:')    {    // display HTML content

            /* update container div size */
            contentBox.style.width = width+'px';
            contentBox.style.height = height+'px';
            contentBox.style.maxWidth = '100%';

            contentBox.innerHTML = file.substring(8);

            /* display popup div */
            this.show_popup('html', width, height);
        } else if (fileExt == 'mp4' || fileExt == 'm4v') {

            /* update container div size */
            contentBox.style.width = width+'px';
            contentBox.style.height = height+'px';

            /* add video tag */
            contentBox.innerHTML = '<video controls="" width="'+width+'" height="'+height+'" preload="" src="'+file+'">&nbsp;</video>';

            /* display popup div */
            this.show_popup('video', width, height);
        } else { // display Image

                /* load image */
                var mainImage = new Image();
                mainImage.name = file;
                mainImage.onload = _mediaPopup_imageLoadingSuccess;
                mainImage.onerror = _mediaPopup_imageLoadingFailed;
                mainImage.src = file;
         }

        /* add title to popup */
        if (title != '') {
            ptitle = document.createElement('div').cloneNode(true);
            ptitle.className = 'mediaTitle';
            ptitle.innerHTML = title;
            popup.appendChild(ptitle);
        }
    };

    /*
     * add loaded image to popup
     * @param Image image
     * @return void
     * @access private
     */
    this.add_imageToPopup = function(image) {
        /* add image to popup */
        img = document.createElement('img').cloneNode(true);
        img.src = image.src;
        img.style.border = 'none';

        /* check sizes */
        if (this.get_param('maxWidth') === false || image.width < this.get_param('maxWidth')) {
            appliedWidth = image.width;
            appliedHeight = image.height;
        } else {
            appliedWidth = this.get_param('maxWidth');
            appliedHeight = image.height*appliedWidth/image.width;
            img.style.width = appliedWidth+'px';
        }

        /* attach actions */
        if (this.get_param('navType') == 'real') {
            img.setAttribute('onclick', this.name+'.close_media()');
        } else {
            img.onclick = new Function('onclick', this.name+'.close_media()');
        }
        this.get_param('contentBox').appendChild(img);

        /* check for diaporama */
        if (this.get_param('diaporama').length > 0) {
            diap = this.get_param('diaporama');
            for (var i in diap) {
                if (image.src.indexOf(diap[i]['picture']) > -1) {
                    /* display left button */
                    this.get_param('diapLeftButton').style.left = (-this.get_param('diaporamaButtonsWidth')+this.get_param('diaporamaButtonsShift')) + 'px';
                    this.get_param('diapLeftButton').style.top = parseInt(img.height/2) + 'px';
                    this.get_param('diapLeftButton').style.display = 'inline';

                    /* display right button */
                    if (this.get_param('maxWidth') > 0)
                        rPos = Math.min(img.width, this.get_param('maxWidth'));
                    else
                        rPos = img.width;
                    this.get_param('diapRightButton').style.left = (rPos-this.get_param('diaporamaButtonsWidth')-this.get_param('diaporamaButtonsShift')) + 'px';
                    this.get_param('diapRightButton').style.top = parseInt(img.height/2) + 'px';
                    this.get_param('diapRightButton').style.display = 'inline';

                    /* save current displayed image */
                    this.set_param('diaporamaCurrent', i);

                    break;
                }
            }
        }

        /* show popup */
        this.show_popup('image', appliedWidth, appliedHeight);
    };

    /*
     * show popup object
     * @param String mediaType
     * @parma integer mediaWidth
     * @param integer mediaHeight
     * @return void
     * @access public
     */
    this.show_popup = function(mediaType, mediaWidth, mediaHeight) {

        this.get_param('body').appendChild(this.get_param('currentPopup'));

        this.set_param('mediaType', mediaType);
        this.set_param('mediaWidth', mediaWidth);
        this.set_param('mediaHeight', mediaHeight);

        /* show popup with a micro delay : fixing a Webkit bug */
        setTimeout(this.name+'._show_popup()', 10);
    };

    /*
     * finalise popup object showing
     * @return void
     * @access public
     */
    this._show_popup = function() {
        this.get_param('currentPopup').style.display = 'block';
        this.refresh_position();
    };

    /*
     * close media popup
     * @return void
     * @access public
     */
    this.close_media = function() {
        if (!this.get_param('currentPopup'))
            return;

        /* hide current popup */
        this.get_param('currentPopup').innerHTML = '';
        this.get_param('currentPopup').style.display = 'none';

        /* hide popup background */
        this.hide_popupBackground();
    };

    /*
     * refresh popup position
     * @return void
     * @access public
     */
    this.refresh_position = function() {
        if (this.get_param('currentPopup') === false
            || this.get_param('currentPopup').style.display == 'none')
            return;

        popup = this.get_param('currentPopup');
        type = this.get_param('mediaType');
        mediaWidth = this.get_param('mediaWidth');
        mediaHeight = this.get_param('mediaHeight');

        /* update popup width */
        popup.style.width = Math.max(200, mediaWidth) + 'px';

        /* get window properties */
        if (this.get_param('navType') == 'real') {
            windowWidth = window.innerWidth;
            windowHeight = window.innerHeight;
        } else {
            windowWidth = this.get_param('body').offsetWidth;
            windowHeight = document.documentElement.clientHeight;
        }

        /* check super size media */
        if (type == 'image' && (mediaWidth > (windowWidth - 40)  || mediaHeight > (windowHeight - 40))) {
            popup.style.position = 'absolute';

            if (mediaWidth > (windowWidth - 40))
                popup.style.left = '20px';
            else
                popup.style.left = ((windowWidth-popup.offsetWidth)/2)+'px';

            if (mediaHeight > (windowHeight - 40))
                popup.style.top = '20px';
            else
                popup.style.top = ((windowHeight-popup.offsetHeight)/2)+'px';
        } else {
            popup.style.position = 'fixed';
            popup.style.left = ((windowWidth-popup.offsetWidth)/2)+'px';
            popup.style.top = ((windowHeight-popup.offsetHeight)/2)+'px';
        }

        /* update background */
        this.show_popupBackground();
    };

    /*
     * show popup background
     * @return void
     * @access public
     */
    this.show_popupBackground = function() {
        this.get_param('popupBkgd').style.width = '100%';
        this.get_param('popupBkgd').style.height = this._get_availableHeight() + 'px';
        this.get_param('popupBkgd').style.display = 'block';
    };

    /*
     * hide popup background
     * @return void
     * @access public
     */
    this.hide_popupBackground = function() {
        this.get_param('popupBkgd').style.display = 'none';
    };

    /*
     * open next diaporama picture
     * @return void
     * @access private
     */
    this.display_nextDiaporamaPicture = function() {
        if (this.get_param('diaporama').length == 0)
            return;
        c = parseInt(this.get_param('diaporamaCurrent'))+1;
        if (c == this.get_param('diaporama').length)
            c = 0;
        p = this.get_param('diaporama', c);
        this.close_media();
        this.open_media(p['picture'], p['title']);
    };

    /*
     * open previous diaporama picture
     * @return void
     * @access private
     */
    this.display_previousDiaporamaPicture = function() {
        if (this.get_param('diaporama').length == 0)
            return;
        c = parseInt(this.get_param('diaporamaCurrent'))-1;
        if (c == -1)
            c = this.get_param('diaporama').length-1;
        p = this.get_param('diaporama', c);
        this.close_media();
        this.open_media(p['picture'], p['title']);
    };

    /* internal methods */

    /*
     * build popup background
     * @return void
     * @access private
     */
    this._build_popupBackground = function() {
        d = document.createElement('div').cloneNode(true);
        d.className = 'mediaPopupBkgd';
        d.style.display = 'none';

        /* attach actions */
        if (this.get_param('clickBkgdToClose') == 1) {
            if (this.get_param('navType') == 'real') {
            d.setAttribute('onclick', this.name + '.close_media();');
            } else {
            d.onclick = new Function('onclick', this.name + '.close_media();');
             }
        }

        this.set_param('popupBkgd', d);
        this.get_param('body').appendChild(d);
    };

    /*
     * on key pressed handler
     * @param integer keyCode
     * @return void
     * @access private
     */
    this.on_keyPressed = function(event) {
        /* check if a popup is opened */
        if (this.get_param('popupBkgd').style.display == 'none')
            return;

        switch(event.keyCode) {
        case 27: /* key : escape */
            this.close_media();
            break;
        case 37: /* key : left */
            this.display_previousDiaporamaPicture();
            break;
        case 39: /* key : right */
            this.display_nextDiaporamaPicture();
            break;
        default:
            break;
        }
    };

    /*
     * return close button DOM Element
     * @return DOMElement
     * @access private
     */
    this._get_closeButton = function() {
        /* add close button box */
        bttnBox = document.createElement('div').cloneNode(true);
        bttnBox.className = 'closeButton';

        /* add close button image */
        bttnImg = document.createElement('img').cloneNode(true);
        bttnImg.src = this.get_param('pictures', 'closeButton');
        bttnImg.style.border = 'none';

        /* attach actions */
        if (this.get_param('navType') == 'real') {
            bttnImg.setAttribute('onmouseover', 'this.src="'+this.get_param('pictures', 'closeButtonOver')+'";');
        bttnImg.setAttribute('onmouseout', 'this.src="'+this.get_param('pictures', 'closeButton')+'";');
            bttnImg.setAttribute('onclick', this.name + '.close_media();');
        } else {
            bttnImg.onmouseover = new Function('this.src="'+this.get_param('pictures', 'closeButtonOver')+'";');
            bttnImg.onmouseout = new Function('this.src="'+this.get_param('pictures', 'closeButton')+'";');
            bttnImg.onclick = new Function('onclick', this.name + '.close_media();');
        }
        bttnBox.appendChild(bttnImg);
        return bttnBox;
    };

    /*
     * return control buttons bar DOM Element
     * @return DOMElement
     * @access private
     */
    this._get_controlButtonsBar = function() {
        /* attach diaporama bar */
        diapButtonBar = document.createElement('div').cloneNode(true);
        diapButtonBar.style.height = '1px';
        if (this.get_param('navType') == 'real') {
            diapButtonBar.style.overflow = 'visible';
        } else {
            diapButtonBar.style.CSSOverflow = 'visible';
        }
        diapButtonBar.style.textAlign = 'left';

        popup.appendChild(diapButtonBar);

        /* attach diaporama left button */
        diapLeftButton = document.createElement('img').cloneNode(true);
        diapLeftButton.src = this.get_param('pictures', 'leftButton');
        diapLeftButton.style.position = 'relative';
        diapLeftButton.style.display = 'none';
        diapLeftButton.style.cursor = 'pointer';
        /* attach actions */
        if (this.get_param('navType') == 'real') {
            diapLeftButton.setAttribute('onmouseover', 'this.src="'+this.get_param('pictures', 'leftButtonOver')+'";');
        diapLeftButton.setAttribute('onmouseout', 'this.src="'+this.get_param('pictures', 'leftButton')+'";');
            diapLeftButton.setAttribute('onclick', this.name+'.display_previousDiaporamaPicture()');
        } else {
            diapLeftButton.onmouseover = new Function('this.src="'+this.get_param('pictures', 'leftButtonOver')+'";');
            diapLeftButton.onmouseout = new Function('this.src="'+this.get_param('pictures', 'leftButton')+'";');
            diapLeftButton.onclick = new Function('onclick', this.name+'.display_previousDiaporamaPicture()');
        }
        this.set_param('diapLeftButton', diapLeftButton);
        diapButtonBar.appendChild(diapLeftButton);

        /* attach diaporama right button */
        diapRightButton = document.createElement('img').cloneNode(true);
        diapRightButton.src = this.get_param('pictures', 'rightButton');
        diapRightButton.style.position = 'relative';
        diapRightButton.style.display = 'none';
        diapRightButton.style.cursor = 'pointer';

        /* attach actions */
        if (this.get_param('navType') == 'real') {
            diapRightButton.setAttribute('onmouseover', 'this.src="'+this.get_param('pictures', 'rightButtonOver')+'";');
        diapRightButton.setAttribute('onmouseout', 'this.src="'+this.get_param('pictures', 'rightButton')+'";');
            diapRightButton.setAttribute('onclick', this.name+'.display_nextDiaporamaPicture()');
        } else {
            diapRightButton.onmouseover = new Function('this.src="'+this.get_param('pictures', 'rightButtonOver')+'";');
            diapRightButton.onmouseout = new Function('this.src="'+this.get_param('pictures', 'rightButton')+'";');
            diapRightButton.onclick = new Function('onclick', this.name+'.display_nextDiaporamaPicture()');
        }
        this.set_param('diapRightButton', diapRightButton);
        diapButtonBar.appendChild(diapRightButton);

        return diapButtonBar;
    };

    /*
     * load diaporama button to get there size
     * @return void
     * @access private
     */
    this._get_diaporamaButtonsSize = function() {
        /* load image */
        var mainImage = new Image();
        mainImage.name = this.get_param('pictures', 'leftButton');
        mainImage.onload = _mediaPopup_diaporamaButtonLoadingSuccess;
        mainImage.onerror = _mediaPopup_diaporamaButtonLoadingFailed;
        mainImage.src = this.get_param('pictures', 'leftButton');
    };

    /*
     * set diaporama buttons size
     * @return void
     * @access private
     */
    this._set_diaporamaButtonsSize = function(width, height) {
        this.set_param('diaporamaButtonsWidth', width);
        this.set_param('diaporamaButtonsHeight', height);
    };

    /*
     * get available height
     * @return void
     * @access private
     */
    this._get_availableHeight = function() {
        return document.documentElement.clientHeight;
    };

    /*
     * check file opening on a new window
     * @param width
     * @return void
     * @access private
     */
    this.check_openInANewWindow = function(width) {

        if (this.get_param('directOpenOnMobile') == 0)
            return false;
        if (this.get_param('isMobile') == 0)
            return false;
        if (this.get_param('isMobile') == 1)
            return true;
        if (this.get_param('isMobile') == -1) {
            return (window.innerWidth < 700 || window.innerWidth < (width+20));
        }
    };
}

/* main static methods */

/*
 * open media popup
 * @param string media
 * @param string title
 * @param string width
 * @param string height
 * @return void
 * @access public
 */
function mediaPopup_open(media, title, width, height) {
    __myMediaPopupObject.open_media(media, title, width, height);
}

/* event methods */

/*
 * on key pressed event handler
 * @return void
 * @access public
 */
function _mediaPopup_onKeyPressed(event) {
    __myMediaPopupObject.on_keyPressed(event.keyCode);
}

/* picture loading methods */

/*
 * picture loading success handler
 * @return void
 * @access public
 */
function _mediaPopup_imageLoadingSuccess() {
        __myMediaPopupObject.add_imageToPopup(this);
}

/*
 * picture loading failure handler
 * @return void
 * @access public
 */
function _mediaPopup_imageLoadingFailed() {
        __myMediaPopupObject.hide_popupBackground();
}

/*
 * diaporama button loading success handler
 * @return void
 * @access public
 */
function _mediaPopup_diaporamaButtonLoadingSuccess() {
        __myMediaPopupObject._set_diaporamaButtonsSize(this.width, this.height);
}

/*
 * diaporama button loading success handler
 * @return void
 * @access public
 */
function _mediaPopup_diaporamaButtonLoadingFailed() {
        __myMediaPopupObject._set_diaporamaButtonsSize(35, 35);
}


/* compatibility methods */

/*
 * open image in a media popup
 * @param string img
 * @param string title
 * @return void
 * @access private
 */
function open_modalImage(img, title) {
        __myMediaPopupObject.open_media(img, title);
}
