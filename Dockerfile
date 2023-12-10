FROM nginx:alpine
# Remove default configuration
# RUN rm /etc/nginx/nginx.conf
# RUN rm /etc/nginx/conf.d/default.conf

COPY build/kloenk.html /usr/share/nginx/html
COPY build/kloenk.js /usr/share/nginx/html
COPY build/kloenk.wasm /usr/share/nginx/html

# COPY build/resources/web/nginx.conf /etc/nginx/nginx.conf
COPY build/resources/web/nginx.conf /etc/nginx/conf.d/default.conf
# CMD ["nginx", "-c", "/data/conf/nginx.conf"]


# $ docker run -p 80:80 -d hydrogax/kloenk:newest