#!/bin/bash

echo "Run with cli options"
npx babel src/simple-code.js --presets=@babel/preset-react \
--plugins=@babel/plugin-transform-template-literals,@babel/plugin-transform-arrow-functions

echo "Run with config file"
npx babel src/simple-code.js

