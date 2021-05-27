# pre-oatpp-staticfileserver
This is a simple static file server for oatpp in order to correctly distribute files with their according content type.

## Usage
Add the following to your oatpp app : 
```cpp
auto router = components.httpRouter.getObject();
oatpppre::StaticFilesHandler::mountAtRoute(router, "/files/*", "."); // Add the static file handle
```

See full example in [examples/staticfileserver.cpp](./examples/staticfileserver.cpp)

### Add it to your project
In `.nxxm/deps` :
```json
{
  "cpp-pre/oatpppre-staticfileserver" : {}
}
```

## Compiling
```sh
nxxm . -t linux-cxx17
```

## Disclaimer
This project is made by [tipi.build](http://tipi.build) and works in conjunction with oatpp but isn't related by any means to the oatpp authors.

## Contact
Maintainer : damien@tipi.build