const express = require("express");
const { createServer } = require("http");
const { ApolloServer } = require("apollo-server-express");
const { PubSub } = require("graphql-subscriptions");
const depthLimit = require("graphql-depth-limit");
const { MongoClient } = require('mongodb');
const expressPlayground = require("graphql-playground-middleware-express").default;
const { readFileSync } = require('fs');
const path = require("path");
const resolvers = require("./resolvers");   // Load graphql resolver

// Load graphql schema
const typeDefs = readFileSync('./typeDefs.graphql', 'UTF-8')




// Load Env
require('dotenv').config()

async function start() {
    // Define express App
    const app = express();

    // variable for PubSub
    const pubsub = new PubSub();

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
        validationRules: [depthLimit(5)],
        context: async ({ req, connection }) => {
            if (connection) {
                console.log("websocket");
                console.log(connection);
            }
            
            // 매 요청마다 컨텍스트 설정 : 요청 헤더의 인증 토큰으로 유저 확인
            // HTTP 요청은 req, 웹소켓 요청은 connection을 이용
            const githubToken = req? req.headers.authorization : connection.context.Authorization;
            const currentUser = await db.collection('users').findOne({ githubToken });
            return { db, currentUser, pubsub }
        },
        subscriptions: {
            path: '/subscriptions',
            onConnect: (connectionParams, webSocket, context) => {
              console.log('Client connected');
            },
            onDisconnect: (webSocket, context) => {
              console.log('Client disconnected')
            },
          },
    });
    
    // Mount express app to server
    server.applyMiddleware({ app });

    // Routing
    app.get("/", (req, res) => res.end("Welcome to PhotoShare API"));
    app.get("/playground", expressPlayground({ endpoint: "/graphql" }));
    app.use("/img/photos", express.static(path.join(__dirname, "assets", "photos")));

    // Create Http Server instance for web-socket
    const httpServer = createServer(app);

    // Add server handler for http server : 웹소켓을 이용한 서브스크립션 기능
    server.installSubscriptionHandlers(httpServer);
    httpServer.timeout = 5000;

    // Run the server
    const portNumber = 4000
    app.listen({ port: portNumber }, () => {
        console.log(`GraphQL Server running @ http://localhost:${portNumber}${server.graphqlPath}`);
        console.log(`Subscription endpoint ready at ws://localhost:${portNumber}${server.subscriptionsPath}`)
    })
}

start();