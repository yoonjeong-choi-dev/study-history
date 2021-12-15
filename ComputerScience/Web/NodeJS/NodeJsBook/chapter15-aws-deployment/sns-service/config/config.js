require('dotenv').config();

module.exports = {
    development: {
        username: "nodejsuser",
        password: process.env.SEQUELIZE_PASSWORD,
        database: "nodejsbook_sns",
        host: "127.0.0.1",
        dialect: "mysql",
    },
    test: {
        username: "nodejsuser",
        password: process.env.SEQUELIZE_PASSWORD,
        database: "nodejsbook_sns_test",
        host: "127.0.0.1",
        dialect: "mysql",
    },
    production: {
        username: "nodejsuser",
        password: process.env.SEQUELIZE_PASSWORD,
        database: "nodejsbook_sns",
        host: "127.0.0.1",
        dialect: "mysql",
        logging: false,
    }
};