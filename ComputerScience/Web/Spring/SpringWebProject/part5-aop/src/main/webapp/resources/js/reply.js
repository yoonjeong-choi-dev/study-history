
const replyApi = (function() {
    const baseUrl = '/replies/';
    const register = (reply, callback, error=console.error) => {
        fetch(baseUrl + 'register', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(reply)})
            .then(response => response.text())
            .then(result => {
                if(callback) callback(result);
            })
            .catch(e => {
                if (error) error(e);
            });
    };

    const get = (id, callback, error)  => {
        fetch(baseUrl + id + '.json')
            .then(response => response.json())
            .then(result => {
                if(callback) callback(result);
            })
            .catch(e => {
                if (error) error(e);
            });
    };

    const getList = (param, callback, error) => {
        let boardId = param.boardId;
        let page = param.page || 1;

        fetch(baseUrl + 'pages/' + boardId + '/' + page + '.json')
            .then(response => response.json())
            .then(result => {
                if(callback) callback(result.numReplies, result.replies);
            })
            .catch(e => {
                if (error) error(e);
            })
    }

    const remove = (id, callback, error)  => {
        fetch(baseUrl + + id, {
            method: 'DELETE'})
            .then(response => response.text())
            .then(result => {
                if(callback) callback(result);
            })
            .catch(e => {
                if (error) error(e);
            });
    }

    const update = (reply, callback, error) => {
        fetch(baseUrl + reply.id, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(reply)})
            .then(response => response.text())
            .then(result => {
                if(callback) callback(result);
            })
            .catch(e => {
                if (error) error(e);
            });
    }


    return {
        register, getList, remove, update, get
    };

})();