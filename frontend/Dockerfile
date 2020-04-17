# docker build -t video-app-frontend . && clear && docker run -it --rm -p 3000:3000 -v ${PWD}/src:/app/src video-app-frontend

FROM node:13.12.0-alpine

WORKDIR /app

COPY . .

RUN npm install --silent

CMD ["npm", "start"]
