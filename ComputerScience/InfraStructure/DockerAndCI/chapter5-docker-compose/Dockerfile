FROM node:14

WORKDIR /yj-node-app

COPY package*.json ./
RUN npm install 

COPY . .

CMD ["node", "index.js"]