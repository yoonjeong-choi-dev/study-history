#!/bin/bash

# Build docker iamge
docker build -t docker-ci-study/nodejs-app .

# Run node-app with connecting container port with local port
# -p <local port>:<container port which is defined on node-app>
docker run -d -p 8080:7166 docker-ci-study/nodejs-app
