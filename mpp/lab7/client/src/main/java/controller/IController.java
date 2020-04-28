package controller;

public interface IController {
    default void onWindowShow() {}
    default void onWindowHide() {}

    String getStageTitle();
    String getFXMLFilePath();
    void stop();
}
