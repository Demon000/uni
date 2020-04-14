package server;

import service.IService;

import java.io.IOException;

public interface IServer {
    void start(IService service, int port) throws IOException;
    void stop() throws IOException;
}
