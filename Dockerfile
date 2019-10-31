FROM amd64/ubuntu:xenial

RUN apt-get update && apt-get install -y \
	gcc \
	clang \
	libc6-dev-i386 \
	git \
	make \
	man \
	vim \
	strace

RUN git clone https://github.com/vsteffen/ft_strace /root/ft_strace

WORKDIR /root/ft_strace
