FROM ubuntu:22.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install required packages
RUN apt-get update && \
	apt-get install -y \
	software-properties-common && \
	add-apt-repository universe && \
	apt-get update && \
	apt-get install -y \
	valgrind \
	make \
	gcc \
	g++ \
	bash \
	curl \
	python3 \
	nano && \
	apt-get clean \
	apt-get git

WORKDIR /app

COPY ../ /app

# Customize bash prompt
RUN echo 'PS1="\[\033[34m\]webcontainer: \w# \[\033[0m\]"' >> /etc/bash.bashrc

CMD ["bash"]