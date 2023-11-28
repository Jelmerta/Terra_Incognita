docker pull hydrogax/kloenk
docker rm -f kloenk
docker run -d -p 80:80 --name kloenk hydrogax/kloenk