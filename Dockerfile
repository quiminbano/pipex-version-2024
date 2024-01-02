FROM bash:5.2.21-alpine3.19

RUN apk update && \
	echo "y" | apk add --no-cache alpine-sdk && \
	echo "y" | apk add --no-cache zsh && \
	echo "y" | apk add --no-cache valgrind && \
	mkdir pipex

WORKDIR /pipex

COPY . .

COPY script.sh .

RUN chmod +x script.sh

CMD ["./script.sh"]
