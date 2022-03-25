/**
 * @brief Websocket manager object.
 * @details Engine / Javascript object library
 * @author CaMykS Team
 * @version 1.0
 * @date Creation: Feb 2022
 * @date Modification: Feb 2022
 * @copyright 2022 CaMykS Team
 * @note This program is distributed as is - WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
function WebSocketConnector(name, uri) {
    this.name = name;
    this.serverURI = uri;
    this.autoReconnect = false;
    this.socket;
    this.onOpenHandlers = [];
    this.onCloseHandlers = [];
    this.onMessageHandlers = [];
    this.onErrorHandlers = [];
    this.reloadInterval;

    /**
     * Initialise object
     * @return void
     */
    this.initialise = function() {
        this.open_connection();
    };

    /* Handlers methods */

    /**
     * Add handler.
     * @param string action
     * @param mixed handler
     * @param mixed identifier
     * @return mixed
     */
    this.add_handler = function(action, handler, identifier) {
        /* Check handler list from action */
        if (eval('this.on'+action+'Handlers') === undefined)
            return false;

        /* Check identifier */
        if (identifier === undefined)
            identifier = eval('this.on'+action+'Handlers').length;

        /* Add handler */
        eval('this.on'+action+'Handlers')[identifier] = handler;
    };

    /**
     * Remove handler.
     * @param string action
     * @param mixed identifier
     * @return void
     */
    this.remove_handler = function(action,  identifier) {
        /* Check handler list from action */
        if (eval('this.on'+action+'Handlers') === undefined)
            return false;

        /* Check identifier */
        if (identifier === undefined)
            return false;

        /* Update handler */
        eval('this.on'+action+'Handlers')[identifier] = undefined;
    };

    /* Autoreconnect methods */

    /**
     * Enable auto reconnect.
     * @return void
     */
    this.enable_autoReconnect = function() {
        /* Check auto reconnect is already enabled */
        if (this.autoReconnect)
            return;

        /* Add a close handler */
        this.add_handler('Close', this.name+'.reload_connection();', 'AutoReconnect');

        /* Update auto reconnect value */
        this.autoReconnect = true;
    };

    /**
     * Disable auto reconnect.
     * @return void
     */
    this.disable_autoReconnect = function() {
        /* Check auto reconnect is already disabled */
        if (!this.autoReconnect)
            return;

        /* Remove handler */
        this.remove_handler('Close', 'AutoReconnect');

        /* Update auto reconnect value */
        this.autoReconnect = false;
    };

    /** Socket related main methods **/

    /**
     * Open connection.
     * @return void
     */
    this.open_connection = function() {
        /* Check serveur URI */

        /* Check socket already exists and is connecting */
        if (this.socket && this.socket.readyState !== this.socket.CLOSED) {
            console.log('websocket already connecting');
            return;
        }

        /* Open connection */
        this.socket = new WebSocket(this.serverURI);

        /* Attach handlers */
        this.socket.parent = this;
        this.socket.onopen = this.on_socketOpen;
        this.socket.onclose = this.on_socketClose;
        this.socket.onmessage = this.on_socketMessage;
        this.socket.onerror = this.on_socketError;
    };

    /**
     * Close connection.
     * @return void
     */
    this.close_connection = function() {
        /* Check sockect */
        if (!this.socket)
            return false;

        /* Remove auto reconnect on manual close */
        this.disable_autoReconnect();

        /* Close socket */
        this.socket.close();
    };

    /**
     * Send data to socket.
     * @param mixed data
     * @return void
     */
    this.send_data = function(data) {
        /* Check sockect */
        if (!this.socket)
            return false;

        /* Check socket status */
        if (this.socket.readyState !== this.socket.OPEN)
            return false;

        /* Check data format */
        data = JSON.stringify(data);

        /* Send data */
        this.socket.send(data);

        /* Return success */
        return true;
    };

    /** Socket handler methods */

    /**
     * Socket on open handler.
     * @param Object event
     * @return void
     */
    this.on_socketOpen = function(event) {
        this.parent.execute_handlers('Open', event);
    };

    /**
     * Socket on close handler.
     * @param Object event
     * @return void
     */
    this.on_socketClose = function(event) {
        this.parent.execute_handlers('Close', event);
    };

    /**
     * Socket on message handler.
     * @param Object event
     * @return void
     */
    this.on_socketMessage = function(event) {
        this.parent.execute_handlers('Message', event);
    };

    /**
     * Socket on error handler.
     * @param Object event
     * @return void
     */
    this.on_socketError = function(event) {
        this.parent.execute_handlers('Error', event);
    };

    /* Tool methods */

    /**
     * Reload connection.
     * @return void
     */
    this.reload_connection = function() {
        if (this.reloadInterval !== undefined)
            return;

        /* Clear socket */
        this.socket = undefined;

        /* Add handler to clear reload interval */
        this.add_handler('Open', this.name+'.clear_reloadInterval;', 'Reload');

        /* Create interval */
        this.reloadInterval = setInterval(this.name+'.open_connection();', 15000);
    };

    /**
     * Clear reload interval.
     * @return void
     */
    this.clear_reloadInterval = function() {
        clearInterval(this.reloadInterval);
    };

    /**
     * Execute handlers.
     * @param string action
     * @param Object event
     * @return void
     */
    this.execute_handlers = function(action, event) {
        /* Check handler list from action */
        if (eval('this.on'+action+'Handlers') === undefined)
            return false;

        /* Execute all handlers */
        for (i in eval('this.on'+action+'Handlers')) {
            h = eval('this.on'+action+'Handlers')[i];

            if (typeof h === 'function')
                h(event);
            else if (typeof h === 'string')
                eval(h+'(event)');
        }
    };
}
