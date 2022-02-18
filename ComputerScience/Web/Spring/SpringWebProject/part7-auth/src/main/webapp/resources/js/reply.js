const replyApi = (function () {
    const baseUrl = '/replies/';
    const register = (csrf, reply, callback, error = console.error) => {
        fetch(baseUrl + 'register', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json;charset=utf-8',
                [csrf.header]: csrf.token,
            },
            body: JSON.stringify(reply)
        })
            .then(response => response.text())
            .then(result => {
                if (callback) callback(result);
            })
            .catch(e => {
                if (error) error(e);
            });
    };

    const get = (id, callback, error) => {
        fetch(baseUrl + id + '.json')
            .then(response => response.json())
            .then(result => {
                if (callback) callback(result);
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
                if (callback) callback(result.numReplies, result.replies);
            })
            .catch(e => {
                if (error) error(e);
            })
    }

    const remove = (csrf, id, replier, callback, error) => {
        fetch(baseUrl + +id, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json;charset=utf-8',
                [csrf.header]: csrf.token,
            },
            body: JSON.stringify({
                id: id,
                replier: replier,
            }),
        },)
            .then(response => response.text())
            .then(result => {
                if (callback) callback(result);
            })
            .catch(e => {
                if (error) error(e);
            });
    }

    const update = (csrf, reply, callback, error) => {
        fetch(baseUrl + reply.id, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json;charset=utf-8',
                [csrf.header] : csrf.token,
            },
            body: JSON.stringify(reply)
        })
            .then(response => response.text())
            .then(result => {
                if (callback) callback(result);
            })
            .catch(e => {
                if (error) error(e);
            });
    }


    return {
        register, getList, remove, update, get
    };

})();