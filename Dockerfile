FROM emscripten/emsdk AS build
COPY /src /src
WORKDIR /build
WORKDIR /src/source
RUN em++ -lembind main.cpp point.cpp calculator.cpp -o /build/main.js -s WASM=1 -I../include

FROM nginx:latest as run
COPY index.html /usr/share/nginx/html
COPY --from=build /build /usr/share/nginx/html/build
EXPOSE 8080
CMD ["nginx", "-g", "daemon off;"]