package service;

public interface ICanStart {
    void start() throws CanStartError;
    void stop() throws CanStartError;
}
