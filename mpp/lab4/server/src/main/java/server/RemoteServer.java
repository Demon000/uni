package server;

import service.IService;

import java.io.IOException;
import java.rmi.AlreadyBoundException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class RemoteServer implements IServer {
    static Registry registry;
    private IService service;

    @Override
    public void start(IService service, int port) throws IOException {
        registry = LocateRegistry.createRegistry(port);

        this.service = (IService) UnicastRemoteObject.exportObject(service, port);

        try {
            registry.bind(IService.class.getSimpleName(), this.service);
        } catch (AlreadyBoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void stop() throws IOException {
        UnicastRemoteObject.unexportObject(service, true);
    }
}
