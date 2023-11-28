FROM nginx:alpine
COPY build/kloenk.html /usr/share/nginx/html
COPY build/kloenk.js /usr/share/nginx/html
COPY build/kloenk.wasm /usr/share/nginx/html