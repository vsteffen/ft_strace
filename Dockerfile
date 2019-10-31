FROM amd64/ubuntu:xenial

RUN apt-get update && apt-get install -y \
	gcc \
	clang \
	git \
	make \
	man \
	vim \
	strace

RUN git clone https://github.com/vsteffen/ft_strace /root/ft_strace

WORKDIR /root/ft_strace
