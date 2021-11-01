const express = require("express");
const { ApolloServer } = require("apollo-server-express");
const { MongoClient } = require('mongodb');
const expressPlayground = require("graphql-playground-middleware-express").default;
const { readFileSync } = require('fs');


// Load graphql schema
const typeDefs = readFileSync('./typeDefs.graphql', 'UTF-8')

// Load graphql resolver
const resolvers = require("./resolvers");

// Load Env
require('dotenv').config()

async function start() {
    // Define express App
    var app = express();

    // variables for mongodb
    const MONGO_DB = process.env.DB_HOST
    let db;

    // Connect to Database
    try {
        const client = await MongoClient.connect(
            MONGO_DB,
            { useNewUrlParser: true }
        );
        db = client.db();
        console.log("Success to connect to local database");

    } catch (error) {
        console.log(
            `
        
            Mongo DB Host Not Found!
            Please add DB_HOST environmnet variable to .env file

            exit...
            `
        );

        process.exit(1);
    }

    // Define Server Instance with schema and resolver
    const server = new ApolloServer({
        typeDefs,
        resolvers,
        context: async ({ req }) => {
            //매 요청마다 컨텍스트 설정 : 요청 헤더의 인증 토큰으로 유저 확인
            const githubToken = req.headers.authorization
            const currentUser = await db.collection('users').findOne({ githubToken })
            return { db, currentUser }
        }
    });

    await server.start();

    // Mount express app to server
    server.applyMiddleware({ app });

    // Routing
    app.get("/", (req, res) => res.end("Welcome to PhotoShare API"));
    app.get("/playground", expressPlayground({ endpoint: "/graphql" }));

    // Run the server
    const portNumber = 4000
    app.listen({ port: portNumber }, () => {
        console.log(`GraphQL Server running @ http://localhost:${portNumber}${server.graphqlPath}`)
    })
}

start();