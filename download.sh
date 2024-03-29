#!/bin/sh

docker run --restart unless-stopped --name=blueocean --group-add $(stat -c '%g' /var/run/docker.sock) -p 8888:8080 -d -v jenkins-data:/var/jenkins_home -v /var/run/docker.sock:/var/run/docker.sock jenkins/jenkins:latest
