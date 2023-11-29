#!/bin/sh
# During Droplet creation, we could add this script to a file, such that it can be re-used from the server, instead of calling the code remotely.
docker pull hydrogax/kloenk
docker rm -f kloenk
docker run -d -p 80:80 --name kloenk hydrogax/kloenk