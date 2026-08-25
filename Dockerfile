FROM alpine:3.22 AS build
RUN apk add --no-cache build-base
WORKDIR /src
COPY src/main.c ./main.c
RUN gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -O2 -static -s -o /out/sky-word-reducer main.c

FROM scratch
COPY --from=build /out/sky-word-reducer /sky-word-reducer
USER 65532:65532
ENTRYPOINT ["/sky-word-reducer"]
