#!/bin/bash

echo "----- HandleFunc Test -----"
curl localhost:8080/helloWorldHandlerLegacy -d '{"name":"YJ"}'

echo "----- Handle Test -----"
curl localhost:8080/hello -d '{"name":"YJ"}'