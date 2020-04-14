package service;

import domain.Score;

public interface IServiceObserver {
    void onSetScore(Score score);
}
