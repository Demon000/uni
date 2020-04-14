package message;

public enum MessageType {
    LOGIN_REQUEST,
    LOGIN_REQUEST_ERROR,
    LOGIN_RESPONSE,

    PARTICIPANT_SCORES_REQUEST,
    PARTICIPANT_SCORES_REQUEST_ERROR,
    PARTICIPANT_SCORES_RESPONSE,

    RANKING_SCORES_REQUEST,
    RANKING_SCORES_REQUEST_ERROR,
    RANKING_SCORES_RESPONSE,

    SET_SCORE_REQUEST,
    SET_SCORE_REQUEST_ERROR,
    SET_SCORE_RESPONSE,
    SET_SCORE_BROADCAST,
}
