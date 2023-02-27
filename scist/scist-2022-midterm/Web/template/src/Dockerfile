FROM node:18

WORKDIR /app
COPY package*.json ./
RUN npm ci

COPY ./ ./

CMD ["bash", "-c", "timeout 60 node app.js"]
