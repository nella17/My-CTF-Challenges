FROM node:18-alpine

RUN apk update && \
    apk add python3 && \
    python3 -m ensurepip

WORKDIR /app
RUN addgroup -S user && adduser -S user -G user

COPY package*.json requirements.txt .
RUN npm ci && python3 -m pip install -r requirements.txt

ARG INDEX_JS=index.js
ARG FLAG4=?
COPY . .

RUN chown -R user:user . && chmod 550 -R . && \
    mv index.js $INDEX_JS && echo "node $INDEX_JS" > /run.sh && \
    chown user:user /run.sh && chmod 550 /run.sh && \
    mv send.py / && chmod 555 /send.py && \
    echo $FLAG4 > /flag4 && chmod 444 /flag4

# USER user
CMD /run.sh
