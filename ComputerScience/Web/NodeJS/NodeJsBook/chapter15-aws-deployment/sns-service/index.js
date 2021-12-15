const app = require('./app');

app.listen(app.get('port'), () => {
    console.log(`Listen to localhost:${app.get('port')}`);
});