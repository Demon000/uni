package service;

public interface IObserver {
    default void onEvent(String name, Object object) {}
}
