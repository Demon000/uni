package service;

import domain.Score;

public interface IServiceObserver {
    default void onSetScore(Score score) {}
    default void onLoginStatusChange(boolean loggedIn) {}
    default void onConnectionStatusChange(ServiceConnectionStatus status) {}
}
